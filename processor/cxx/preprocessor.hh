#include "processor.hh"
// ==============================
//  Struct definitions
// ==============================

// Struct to store the location range
typedef struct LocRange {
    string beginLoc;
    string endLoc;

    friend void to_json(json &j, const LocRange &lr) {
        if (lr.beginLoc.empty() || lr.endLoc.empty()) {
            j = json("");
        } else {
            j = json(lr.beginLoc + " -> " + lr.endLoc);
        }
    }

    // constructor to initialize the object
    LocRange(SourceRange range, SourceManager &sourceManager) {
        this->beginLoc = GetAbsPath(sourceManager, range.getBegin());
        this->endLoc = GetAbsPath(sourceManager, range.getEnd());
    }
    // basic constructor
    LocRange(string beginLoc, string endLoc)
        : beginLoc(beginLoc), endLoc(endLoc) {}
    // empty constructor
    LocRange() {}

    // Operator to compare two LocRange objects
    // Only used in the set container
    bool operator==(const LocRange &other) const {
        return beginLoc == other.beginLoc && endLoc == other.endLoc;
    }
    bool operator<(const LocRange &other) const {
        return beginLoc < other.beginLoc;
    }
} AFGenLocRange;

// Struct to store the function parameter type information
// TypeInfo is Already defined in Clang, so we use AFGenTypeInfo here
typedef struct TypeInfo {
  public:
    string type;
    string realType;
    string baseType;
    bool isBuiltin;
    bool isFuncPointer;
    bool isTemplateType = false;
    vector<TypeInfo> disassembledTemplateTypes;

    void disassembleTemplateType(clang::QualType t,
                                 SourceManager &sourceManager) {
        auto tp = GetBaseType(t)->getAs<TemplateSpecializationType>();
        if (tp) {
            isTemplateType = true;

            auto templateDecl = tp->getTemplateName().getAsTemplateDecl();
            // FIXME: Can not process type like:
            // const std::map<std::string, Value *> &
            if (templateDecl) {
                // get the template decl type
                // XXX: template decl is not a genuine type, we just treat it as
                // a type for convenience
                string templateDeclType = templateDecl->getNameAsString();
                string templateDeclRealType =
                    templateDecl->getQualifiedNameAsString();
                bool templateDeclIsBuiltin = IsSystemVar(
                    GetAbsPath(sourceManager, templateDecl->getLocation()));
                auto templateDeclTypeInfo =
                    TypeInfo(templateDeclType, templateDeclRealType,
                             templateDeclRealType, templateDeclIsBuiltin);
                if (not IsInVec(disassembledTemplateTypes,
                                templateDeclTypeInfo)) {
                    disassembledTemplateTypes.push_back(templateDeclTypeInfo);
                }
            }

            for (auto arg : tp->template_arguments()) {
                // recursively disassemble the template type
                if (arg.getKind() == clang::TemplateArgument::ArgKind::Type) {
                    disassembleTemplateType(arg.getAsType(), sourceManager);
                }
            }
        } else {
            auto tTypeInfo = TypeInfo(t, sourceManager, false);
            if (not IsInVec(disassembledTemplateTypes, tTypeInfo)) {
                disassembledTemplateTypes.push_back(tTypeInfo);
            }
        }
    }

    json typeToJson() const {
        json j = json{{"type", type},
                      {"realType", realType},
                      {"baseType", baseType},
                      {"isBuiltin", isBuiltin},
                      {"isFuncPointer", isFuncPointer},
                      {"isTemplateType", isTemplateType}};
        if (isTemplateType) {
            j.update(
                {{"disassembledTemplateTypes", disassembledTemplateTypes}});
        }
        return j;
    }

    friend void to_json(json &j, const TypeInfo &ti) { j = ti.typeToJson(); }

    // Equality operator to compare two TypeInfo objects
    bool operator==(const TypeInfo &other) const { return type == other.type; }

    // constructor to initialize the object
    TypeInfo(clang::QualType t, SourceManager &sourceManager,
             bool disassembleTemplate = true) {
        type = t.getAsString();
        realType = GetRealTypeString(t);
        baseType = GetBaseTypeString(t);
        isBuiltin = AFGenIsBuiltin(t);
        isFuncPointer = t->isFunctionPointerType();
        if (disassembleTemplate) {
            disassembleTemplateType(t, sourceManager);
        }
    }
    // basic constructor
    TypeInfo(string type, string realType, string baseType, bool isBuiltin)
        : type(type), realType(realType), baseType(baseType),
          isBuiltin(isBuiltin) {}
    // empty constructor
    TypeInfo() {}
} AFGenTypeInfo;

// Struct to store the function parameter information
typedef struct ParamInfo : public AFGenTypeInfo {
  public:
    string name; // a parameter has a name, but a type doesn't

    friend void to_json(json &j, const ParamInfo &pi) {
        j = json{{"name", pi.name}};
        j.update(pi.typeToJson());
    }

    // constructor to initialize the object
    ParamInfo(string varName, clang::QualType t, SourceManager &sourceManager)
        : AFGenTypeInfo(t, sourceManager) {
        name = varName;
    }
} AFGenParamInfo;

// Struct to store the composite member information
typedef struct MemberInfo : public AFGenTypeInfo {
    string name;
    AFGenLocRange locRange;
    bool isPublic;

    friend void to_json(json &j, const MemberInfo &ti) {
        j = json{{"name", ti.name},
                 {"locRange", ti.locRange},
                 {"isPublic", ti.isPublic}};
        j.update(ti.typeToJson());
    }

    // constructor to initialize the object
    MemberInfo(string varName, AFGenLocRange locRange, bool isPublic,
               clang::QualType t, SourceManager &sourceManager)
        : AFGenTypeInfo(t, sourceManager) {
        this->name = varName;
        this->locRange = locRange;
        this->isPublic = isPublic;
    }
} AFGenMemberInfo;

// Struct to store the function information
struct FuncInfo {
    string name;
    AFGenLocRange locRange;
    AFGenLocRange declLocRange;
    string declLoc;
    vector<AFGenParamInfo> param;
    AFGenTypeInfo ret;
    int templateParamNum = 0;
    string heldbyNamespace;
    string heldbyClass;

    friend void to_json(json &j, const FuncInfo &fi) {
        j = json{{"name", fi.name},
                 {"locRange", fi.locRange},
                 {"declLocRange", fi.declLocRange},
                 {"declLoc", fi.declLoc},
                 {"param", fi.param},
                 {"return", fi.ret},
                 {"templateParamNum", fi.templateParamNum},
                 {"heldbyNamespace", fi.heldbyNamespace},
                 {"heldbyClass", fi.heldbyClass}};
    }
};

// Struct to store the method information
struct MethodInfo {
    string name;
    AFGenLocRange locRange;
    bool isPublic;
    bool isVirtual;
    bool isOperator;
    bool isConstructor;
    bool isDestructor;

    friend void to_json(json &j, const MethodInfo &mi) {
        j = json{{"name", mi.name},
                 {"locRange", mi.locRange},
                 {"isPublic", mi.isPublic},
                 {"isVirtual", mi.isVirtual},
                 {"isOperator", mi.isOperator},
                 {"isConstructor", mi.isConstructor},
                 {"isDestructor", mi.isDestructor}};
    }
};

// Struct to store the class information
struct ClassInfo {
    string name;
    AFGenLocRange locRange;
    map<string, MethodInfo> methods;
    vector<string> baseABCs; // base abstract classes
    bool isAbstract;
    string heldbyNamespace;
    string heldbyClass;

    friend void to_json(json &j, const ClassInfo &ci) {
        j = json{{"name", ci.name},
                 {"locRange", ci.locRange},
                 {"methods", ci.methods},
                 {"baseABCs", ci.baseABCs},
                 {"isAbstract", ci.isAbstract},
                 {"heldbyNamespace", ci.heldbyNamespace},
                 {"heldbyClass", ci.heldbyClass}};
    }
};

// struct to store the typedef information
struct TypedefInfo {
    string name;
    AFGenTypeInfo underlyingType;
    AFGenLocRange locRange;
    string heldbyNamespace;
    string heldbyClass;

    friend void to_json(json &j, const TypedefInfo &ti) {
        j = json{{"name", ti.name},
                 {"underlyingType", ti.underlyingType},
                 {"locRange", ti.locRange},
                 {"heldbyNamespace", ti.heldbyNamespace},
                 {"heldbyClass", ti.heldbyClass}};
    }
};

// struct to store composite information
struct RecordInfo {
    string name;
    AFGenLocRange locRange;
    string kind; // class, struct, union, enum or unknown
    int templateParamNum = 0;
    vector<MemberInfo> members;
    string heldbyNamespace;
    string heldbyClass;

    friend void to_json(json &j, const RecordInfo &ri) {
        j = json{{"name", ri.name},
                 {"locRange", ri.locRange},
                 {"kind", ri.kind},
                 {"templateParamNum", ri.templateParamNum},
                 {"members", ri.members},
                 {"heldbyNamespace", ri.heldbyNamespace},
                 {"heldbyClass", ri.heldbyClass}};
    }
};

// struct to store the enum information
struct EnumInfo {
    string name;
    AFGenLocRange locRange;
    string heldbyNamespace;
    string heldbyClass;

    friend void to_json(json &j, const EnumInfo &ei) {
        j = json{{"name", ei.name},
                 {"locRange", ei.locRange},
                 {"heldbyNamespace", ei.heldbyNamespace},
                 {"heldbyClass", ei.heldbyClass}};
    }
};

// ==============================
// Global variables to store the information
// ==============================

map<string, ClassInfo> mapClassInfo;
map<string, FuncInfo> mapFuncInfo;
map<string, RecordInfo> mapRecordInfo;
map<string, EnumInfo> mapEnum;
map<string, TypedefInfo> mapTypedef;