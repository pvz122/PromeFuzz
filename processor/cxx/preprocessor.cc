#include "preprocessor.hh"

class AFGenMatchFunc : public MatchFinder::MatchCallback {
  public:
    // @brief: find function declaration and definition
    virtual void run(const MatchFinder::MatchResult &Result) {
        SourceManager &srcMgr = Result.Context->getSourceManager();
        if (auto const *curFuncDecl =
                Result.Nodes.getNodeAs<clang::FunctionDecl>("functionDecl")) {
            if (!curFuncDecl->getBody()) {
                return;
            }
            string curFuncName = curFuncDecl->getQualifiedNameAsString();
            string curFunctionLoc =
                GetAbsPath(srcMgr, curFuncDecl->getLocation());
            string curFuncDefLoc =
                GetAbsPath(srcMgr, curFuncDecl->getDefinition()->getLocation());
            if (IsSystemVar(curFunctionLoc)) {
                return;
            }

            // if the function is already recorded, return
            if (IsInMap(mapFuncInfo, curFunctionLoc) &&
                mapFuncInfo[curFunctionLoc].name == curFuncName) {
                return;
            }

            if (split(curFunctionLoc, ":")[0] != split(curFuncDefLoc, ":")[0]) {
                // this means the function is declared in another file
                auto firstFuncDecl = curFuncDecl->getFirstDecl();
                mapFuncInfo[curFuncDefLoc].declLoc =
                    GetAbsPath(srcMgr, firstFuncDecl->getLocation());
                mapFuncInfo[curFuncDefLoc].declLocRange =
                    AFGenLocRange(firstFuncDecl->getSourceRange(), srcMgr);
                return;
            }

            // record the function's name
            mapFuncInfo[curFunctionLoc].name = curFuncName;

            // record the function's locRange
            mapFuncInfo[curFunctionLoc].locRange =
                AFGenLocRange(curFuncDecl->getSourceRange(), srcMgr);

            // record the return type.
            QualType returnType = curFuncDecl->getReturnType();
            mapFuncInfo[curFunctionLoc].ret = AFGenTypeInfo(returnType, srcMgr);

            // record the function's template
            clang::FunctionTemplateDecl *funcTemplDecl =
                curFuncDecl->getDescribedFunctionTemplate();
            if (funcTemplDecl) {
                mapFuncInfo[curFunctionLoc].templateParamNum =
                    funcTemplDecl->getTemplateParameters()->size();
            } else {
                mapFuncInfo[curFunctionLoc].templateParamNum = 0;
            }

            // record the function's namespace and class name
            GetNamespaceAndClass(curFuncDecl,
                                 mapFuncInfo[curFunctionLoc].heldbyNamespace,
                                 mapFuncInfo[curFunctionLoc].heldbyClass);

            // set param info
            for (auto ii = curFuncDecl->param_begin();
                 ii != curFuncDecl->param_end(); ++ii) {
                auto paramType = (*ii)->getType();

                auto ti =
                    AFGenParamInfo((*ii)->getNameAsString(), paramType, srcMgr);
                mapFuncInfo[curFunctionLoc].param.push_back(ti);
            }
        }
    }
};

// DEPRECATED: This function was intended to extract the call graph among
// functions within the library. However, this approach is inappropriate because
// the caller-callee relationships inside the library do not accurately
// represent API interaction patterns. Instead, we now prefer to analyze the
// actual consumer code of the APIs to precisely extract the call graphs and the
// relationships between APIs.

// class AFGenMatchCall : public MatchFinder::MatchCallback {
//   public:
//     // @brief: extract call graph
//     virtual void run(const MatchFinder::MatchResult &Result) {
//         SourceManager &srcMgr = Result.Context->getSourceManager();
//         if (auto const *curFuncDecl =
//                 Result.Nodes.getNodeAs<clang::FunctionDecl>("functionDecl"))
//                 {
//             string curFunctionLoc =
//                 GetAbsPath(srcMgr, curFuncDecl->getLocation());
//             if (IsSystemVar(curFunctionLoc)) {
//                 return;
//             }

//             // callees of the function
//             if (auto desFuncExpr =
//                     Result.Nodes.getNodeAs<clang::CallExpr>("calleeFunction"))
//                     {
//                 if (auto desFuncDecl = desFuncExpr->getDirectCallee()) {
//                     string firstDeclLoc = GetAbsPath(
//                         srcMgr, desFuncDecl->getFirstDecl()->getLocation());
//                     if (IsSystemVar(firstDeclLoc))
//                         return;
//                     if (!IsInVec(mapFuncInfo[curFunctionLoc].calleeFunction,
//                                  firstDeclLoc))
//                         mapFuncInfo[curFunctionLoc].calleeFunction.push_back(
//                             firstDeclLoc);
//                 }
//             }
//         }
//     }
// };

class AFGenMatchMeth : public MatchFinder::MatchCallback {
  public:
    // @brief: find class and its method
    virtual void run(const MatchFinder::MatchResult &Result) {
        SourceManager &srcMgr = Result.Context->getSourceManager();
        if (auto CXXRecord =
                Result.Nodes.getNodeAs<CXXRecordDecl>("classDecl")) {
            string record_loc = GetAbsPath(srcMgr, CXXRecord->getLocation());
            if (IsSystemVar(record_loc))
                return;

            // if the class is already recorded, return
            if (IsInMap(mapClassInfo, record_loc)) {
                return;
            }

            string record_name = CXXRecord->getQualifiedNameAsString();

            // if the class is not defined, we can't get the class info
            if (not CXXRecord->hasDefinition()) {
                std::cerr << "Warning: Class " << record_name
                          << " has no definition" << std::endl;
                return;
            }

            // set class info
            mapClassInfo[record_loc].locRange =
                AFGenLocRange(CXXRecord->getSourceRange(), srcMgr);
            mapClassInfo[record_loc].isAbstract = CXXRecord->isAbstract();
            mapClassInfo[record_loc].name = record_name;
            for (const clang::CXXBaseSpecifier &BaseSpecifier :
                 CXXRecord->bases()) {
                // This base iterator does not iterate over all the bases along
                // the inheritance chain. Instead, it only iterates over the
                // direct base classes.
                const auto *BaseClass =
                    BaseSpecifier.getType().getTypePtr()->getAsCXXRecordDecl();
                if (BaseClass != nullptr && BaseClass->isAbstract()) {
                    mapClassInfo[record_loc].baseABCs.push_back(
                        BaseClass->getQualifiedNameAsString());
                }
            }
            GetNamespaceAndClass(CXXRecord,
                                 mapClassInfo[record_loc].heldbyNamespace,
                                 mapClassInfo[record_loc].heldbyClass);

            for (const auto &CXXMethod : CXXRecord->methods()) {
                setMethodInfo(record_loc, &srcMgr, CXXMethod);
            }
            // Extract template methods
            // The template method is not in the methods() list, its wrapped
            // by a layer of FunctionTemplateDecl
            for (const auto &Decl : CXXRecord->decls()) {
                // Check if the declaration is a function template
                if (const auto *FuncTemplate =
                        dyn_cast<FunctionTemplateDecl>(Decl)) {
                    const auto *FuncDecl = FuncTemplate->getTemplatedDecl();
                    if (const CXXMethodDecl *CXXMethod =
                            dyn_cast<CXXMethodDecl>(FuncDecl)) {
                        setMethodInfo(record_loc, &srcMgr, CXXMethod);
                    }
                }
            }
        }
    }

    // @brief: set the method information
    void setMethodInfo(string record_loc, SourceManager *srcMgr,
                       const CXXMethodDecl *CXXMethod) {
        string method_loc = GetAbsPath(*srcMgr, CXXMethod->getLocation());
        mapClassInfo[record_loc].methods[method_loc].name =
            CXXMethod->getQualifiedNameAsString();
        mapClassInfo[record_loc].methods[method_loc].locRange =
            AFGenLocRange(CXXMethod->getSourceRange(), *srcMgr);
        mapClassInfo[record_loc].methods[method_loc].isPublic =
            CXXMethod->getAccess() == AS_public;
// XXX: only pure virtual methods can not be called
// and this function name has changed in LLVM 18.1, refer: https://github.com/llvm/llvm-project/commit/e90e43fb9cd1d305f7196cd526aa503374e0f616
#if LLVM_VERSION_MAJOR >= 18 && LLVM_VERSION_MINOR >= 1
        mapClassInfo[record_loc].methods[method_loc].isVirtual =
            CXXMethod->isPureVirtual();
#else
        mapClassInfo[record_loc].methods[method_loc].isVirtual =
            CXXMethod->isPure();
#endif
        mapClassInfo[record_loc].methods[method_loc].isOperator =
            CXXMethod->isOverloadedOperator();
        if (isa<CXXConstructorDecl>(CXXMethod)) {
            // this is a constructor
            mapClassInfo[record_loc].methods[method_loc].isConstructor = true;
        }
        if (isa<CXXDestructorDecl>(CXXMethod)) {
            // this is a destructor
            mapClassInfo[record_loc].methods[method_loc].isDestructor = true;
        }
    }
};

class AFGenMatchSt : public MatchFinder::MatchCallback {
  public:
    // @brief: find clang records (composite types)
    virtual void run(const MatchFinder::MatchResult &Result) {
        SourceManager &srcMgr = Result.Context->getSourceManager();
        if (auto const *recordDecl =
                Result.Nodes.getNodeAs<clang::RecordDecl>("recordDecl")) {
            const SourceLocation &recordSrcLoc = recordDecl->getLocation();
            string recordLoc = GetAbsPath(srcMgr, recordSrcLoc);
            if (IsSystemVar(recordLoc))
                return;

            // if the record is already recorded, return
            if (IsInMap(mapRecordInfo, recordLoc)) {
                return;
            }

            auto recordDef = recordDecl->getDefinition();
            if (!recordDef) {
                // if the record is not defined, we can't get the record info
                std::cerr << "Warning: Record " << recordDecl->getNameAsString()
                          << " has no definition" << std::endl;
                return;
            }
            if (split(recordLoc, ":")[0] !=
                split(GetAbsPath(srcMgr, recordDef->getLocation()), ":")[0]) {
                // this means this is not the definition of the record
                return;
            }

            // set record info
            string recordName;
            if (auto CXXClass = dyn_cast<CXXRecordDecl>(recordDecl)) {
                // if C++ record, `getQualifiedNameAsString` can work as type
                // name
                recordName = CXXClass->getQualifiedNameAsString();

                // set templateParamNum
                clang::ClassTemplateDecl *templDecl =
                    CXXClass->getDescribedClassTemplate();
                if (templDecl) {
                    mapRecordInfo[recordLoc].templateParamNum =
                        templDecl->getTemplateParameters()->size();
                } else {
                    mapRecordInfo[recordLoc].templateParamNum = 0;
                }
            } else {
                // if C record, we need to add `struct` or `union` prefix
                recordName = recordDecl->getNameAsString();
                if (recordName == "") {
                    recordName = "(anonymous)";
                } else if (recordDecl->isStruct()) {
                    recordName = "struct " + recordName;
                } else if (recordDecl->isUnion()) {
                    recordName = "union " + recordName;
                } else if (recordDecl->isEnum()) {
                    recordName = "enum " + recordName;
                }
            }
            mapRecordInfo[recordLoc].name = recordName;

            string recordKind;
            if (recordDecl->isStruct()) {
                recordKind = "struct";
            } else if (recordDecl->isUnion()) {
                recordKind = "union";
            } else if (recordDecl->isClass()) {
                recordKind = "class";
            } else if (recordDecl->isEnum()) {
                recordKind = "enum";
            } else {
                recordKind = "unknown";
            }
            mapRecordInfo[recordLoc].kind = recordKind;

            mapRecordInfo[recordLoc].locRange =
                AFGenLocRange(recordDecl->getSourceRange(), srcMgr);
            GetNamespaceAndClass(recordDecl,
                                 mapRecordInfo[recordLoc].heldbyNamespace,
                                 mapRecordInfo[recordLoc].heldbyClass);

            // record the members of the record
            for (const auto *fieldDecl : recordDecl->fields()) {
                string fieldLoc = GetAbsPath(srcMgr, fieldDecl->getLocation());
                if (IsSystemVar(fieldLoc))
                    continue;
                string fieldName = fieldDecl->getNameAsString();
                auto fieldLocRange =
                    AFGenLocRange(fieldDecl->getSourceRange(), srcMgr);
                auto fieldInfo =
                    AFGenMemberInfo(fieldName, fieldLocRange,
                                    fieldDecl->getAccess() == AS_public,
                                    fieldDecl->getType(), srcMgr);
                if (not IsInVec(mapRecordInfo[recordLoc].members, fieldInfo)) {
                    mapRecordInfo[recordLoc].members.push_back(fieldInfo);
                }
            }
        }
    }
};

class AFGenMatchEnum : public MatchFinder::MatchCallback {
  public:
    // @brief: find enum
    // XXX: Enum is not matched in the record, so we need to match it here.
    virtual void run(const MatchFinder::MatchResult &Result) {
        SourceManager &srcMgr = Result.Context->getSourceManager();
        if (auto enumDecl = Result.Nodes.getNodeAs<EnumDecl>("enumDecl")) {
            string enumLoc = GetAbsPath(srcMgr, enumDecl->getLocation());
            if (IsSystemVar(enumLoc))
                return;

            // if the enum is already recorded, return
            if (IsInMap(mapEnum, enumLoc)) {
                return;
            }

            EnumInfo enumInfo;
            if (Result.Context->getLangOpts().CPlusPlus) {
                // if C++, `getQualifiedNameAsString` can work as type name
                enumInfo.name = enumDecl->getQualifiedNameAsString();
            } else {
                // if C, we need to add `enum` prefix
                enumInfo.name = "enum " + enumDecl->getNameAsString();
            }
            enumInfo.locRange =
                AFGenLocRange(enumDecl->getSourceRange(), srcMgr);
            GetNamespaceAndClass(enumDecl, enumInfo.heldbyNamespace,
                                 enumInfo.heldbyClass);
            mapEnum[enumLoc] = enumInfo;
        }
    }
};

class AFGenMatchTypedefName : public MatchFinder::MatchCallback {
  public:
    // @brief: find typedef statements
    virtual void run(const MatchFinder::MatchResult &Result) {
        SourceManager &srcMgr = Result.Context->getSourceManager();
        if (auto const *typeDefDecl =
                Result.Nodes.getNodeAs<clang::TypedefNameDecl>("typeDefDecl")) {
            string typeDefLoc = GetAbsPath(srcMgr, typeDefDecl->getLocation());
            if (IsSystemVar(typeDefLoc)) {
                return;
            }

            // if the typedef is already recorded, return
            if (IsInMap(mapTypedef, typeDefLoc)) {
                return;
            }

            struct TypedefInfo typedefInfo;
            typedefInfo.underlyingType =
                AFGenTypeInfo(typeDefDecl->getUnderlyingType(), srcMgr);
            typedefInfo.name = typeDefDecl->getNameAsString();
            typedefInfo.locRange =
                AFGenLocRange(typeDefDecl->getSourceRange(), srcMgr);
            GetNamespaceAndClass(typeDefDecl, typedefInfo.heldbyNamespace,
                                 typedefInfo.heldbyClass);

            mapTypedef[typeDefLoc] = typedefInfo;
        }
    }
};

// @brief: output the result to the output file
void saveResults(void) {
    ofstream foutput;
    foutput.open(argOutFile);
    nlohmann::json jsonObj;

    // Composites
    if (mapRecordInfo.size() > 0) {
        nlohmann::json recordJson = mapRecordInfo;
        jsonObj["composites"] = recordJson;
    }

    // Functions
    if (mapFuncInfo.size() > 0) {
        nlohmann::json funcInfoJson = mapFuncInfo;
        jsonObj["functions"] = funcInfoJson;
    }

    // Enums
    if (mapEnum.size() > 0) {
        nlohmann::json enumJson = mapEnum;
        jsonObj["enums"] = enumJson;
    }

    // Classes
    if (mapClassInfo.size() > 0) {
        nlohmann::json classJson = mapClassInfo;
        jsonObj["classes"] = classJson;
    }

    // Typedefs
    if (mapTypedef.size() > 0) {
        nlohmann::json typedefJson = mapTypedef;
        jsonObj["typedefs"] = typedefJson;
    }

    foutput << jsonObj.dump(2);
    foutput.close();
}

// @brief: main function
int main(int argc, const char **argv) {
    // parse the command line arguments
    cl::HideUnrelatedOptions(MyToolCategory);
    auto ExpectedParser = CommonOptionsParser::create(
        argc, argv, MyToolCategory, llvm::cl::OneOrMore);
    if (!ExpectedParser) {
        // Fail gracefully for unsupported options.
        llvm::errs() << ExpectedParser.takeError();
        return 1;
    }
    CommonOptionsParser &OptionsParser = ExpectedParser.get();
    ClangTool Tool(OptionsParser.getCompilations(),
                   OptionsParser.getSourcePathList());

    vector<Matcher> matchers = {
        {MatchFinder(), new AFGenMatchFunc(),
         functionDecl().bind("functionDecl")},
        // {MatchFinder(), new AFGenMatchCall(),
        //  functionDecl(unless(isExpansionInSystemHeader()),
        //               forEachDescendant(callExpr().bind("calleeFunction")))
        //      .bind("functionDecl")},
        {MatchFinder(), new AFGenMatchSt(), recordDecl().bind("recordDecl")},
        {MatchFinder(), new AFGenMatchMeth(),
         cxxRecordDecl().bind("classDecl")},
        {MatchFinder(), new AFGenMatchEnum(), enumDecl().bind("enumDecl")},
        {MatchFinder(), new AFGenMatchTypedefName(),
         typedefNameDecl().bind("typeDefDecl")},
    };

    // match the AST
    matchAST(Tool, matchers);
    // save the results
    saveResults();
    return 0;
}
