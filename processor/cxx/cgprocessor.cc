#include "cgprocessor.hh"

// @brief: match the call expressions in the AST
class AFGenMatchFunc : public MatchFinder::MatchCallback {
  public:
    virtual void run(const MatchFinder::MatchResult &Result) {
        SourceManager &srcMgr = Result.Context->getSourceManager();

        // get the caller function and callee function decl node
        if (auto const *callerFuncDecl =
                Result.Nodes.getNodeAs<clang::FunctionDecl>(
                    "currentFunction")) {
            if (auto callExpr =
                    Result.Nodes.getNodeAs<clang::CallExpr>("calleeFunction")) {
                if (auto calleeFuncDecl = callExpr->getDirectCallee()) {

                    // do some filtering
                    if (!callerFuncDecl->getBody()) {
                        return;
                    }
                    string callerFuncLoc =
                        GetAbsPath(srcMgr, callerFuncDecl->getLocation());
                    string calleeDeclLoc = GetAbsPath(
                        srcMgr, calleeFuncDecl->getFirstDecl()->getLocation());
                    if (IsSystemVar(callerFuncLoc) ||
                        IsSystemVar(calleeDeclLoc)) {
                        return;
                    }
                    if (split(callerFuncLoc, ":")[0] != filePath) {
                        // we want the caller in the processed file
                        return;
                    }

                    // store the calling information
                    CallingInfo callingInfo;
                    callingInfo.callerName =
                        callerFuncDecl->getQualifiedNameAsString();
                    callingInfo.callerDeclLoc = GetAbsPath(
                        srcMgr, callerFuncDecl->getFirstDecl()->getLocation());
                    callingInfo.calleeName =
                        calleeFuncDecl->getQualifiedNameAsString();
                    callingInfo.calleeDeclLoc = calleeDeclLoc;

                    string callingLoc = GetAbsPath(srcMgr, callExpr->getExprLoc());
                    callingInfoMap[callingLoc] = callingInfo;
                }
            }
        }
    }
};

// @brief: store the result to the output file
void saveResults(void) {
    ofstream foutput;
    foutput.open(argOutFile);
    nlohmann::json recordJson = callingInfoMap;
    foutput << recordJson.dump(2);
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
    const auto &sourcePathList = OptionsParser.getSourcePathList();
    if (!sourcePathList.empty()) {
        filePath = sourcePathList.back();
    } else {
        std::cout << "No source code given." << std::endl;
        exit(-1);
    }

    // make the target file path absolute
    filePath =
        std::filesystem::absolute(std::filesystem::path(filePath)).string();

    DeclarationMatcher functionsWithCalls =
        functionDecl(unless(isExpansionInSystemHeader()),
                     forEachDescendant(callExpr().bind("calleeFunction")))
            .bind("currentFunction");
    vector<Matcher> matchers = {
        {MatchFinder(), new AFGenMatchFunc(), functionsWithCalls}};

    // match the AST
    matchAST(Tool, matchers);
    // save the results
    saveResults();
    return 0;
}