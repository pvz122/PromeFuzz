#include "clang-common.hh"
#include "json.hpp"

using json = nlohmann::json;

// Apply a custom category to all command-line options so that they are the
// only ones displayed.
static llvm::cl::OptionCategory MyToolCategory("my-tool options");

static cl::opt<std::string>
    argOutFile("o", cl::desc("Output file that stores the process results."),
               cl::Required, cl::cat(MyToolCategory));

// declare the function here to use it in the struct definition
template <typename T> bool IsInVec(const std::vector<T> &vec, const T &key);
std::string GetAbsPath(SourceManager &SM, SourceLocation loc);

// ==============================
//  Helper functions
// ==============================

// @brief: Whether a var is in vector
template <typename T> bool IsInVec(const std::vector<T> &vec, const T &key) {
    return std::find(vec.begin(), vec.end(), key) != vec.end();
}

// @brief: Whether a key is in map
template <typename T> bool IsInMap(const std::map<string, T> &map, string key) {
    return map.find(key) != map.end();
}

// @brief: Get the absolute path of the file location
//
// @param sourceManager: SourceManager
// @param loc: SourceLocation
// @return: string
std::string GetAbsPath(SourceManager &sourceManager, SourceLocation loc) {
    string ret;
    // a fileID is a unique identifier for a file location, a fileEntry is the
    // file object
    auto fileID = sourceManager.getFileID(loc);
    const clang::FileEntry *fileEntry = nullptr;
    // the fileID may be a real file or a macro expansion
    auto sLocEntry = sourceManager.getSLocEntry(fileID);
    if (sLocEntry.isFile()) {
        // if its a real file, get the file entry directly
        fileEntry = sourceManager.getFileEntryForID(fileID);
    } else if (sLocEntry.isExpansion()) {
        // if its a macro expansion, use the expansion location to get the file
        // because the macro fileID can not get the real file entry. It's like:
        // CJSON_PUBLIC(cJSON*) cJSON_AddObjectToObject(cJSON * const object
        // ^
        loc = sourceManager.getExpansionLoc(loc);
        fileEntry =
            sourceManager.getFileEntryForID(sourceManager.getFileID(loc));
    }

    if (fileEntry) {
        llvm::StringRef absolutePath = fileEntry->tryGetRealPathName();
        std::pair<FileID, unsigned> locationInfo =
            sourceManager.getDecomposedLoc(loc);
        unsigned line = sourceManager.getLineNumber(locationInfo.first,
                                                    locationInfo.second);
        unsigned column = sourceManager.getColumnNumber(locationInfo.first,
                                                        locationInfo.second);
        ret = absolutePath.str() + ":" + to_string(line) + ":" +
              to_string(column);
    } else {
        ret = loc.printToString(sourceManager);
    }
    return ret;
}

// @brief: Get the heldby namespace and class name of the Decl
//
// @param D: the Decl object
// @param namespaceName: the reference of the string to store the namespace name
// @param className: the reference of the string to store the class name
void GetNamespaceAndClass(const Decl *D, std::string &namespaceName,
                          std::string &className) {
    namespaceName = "";
    className = "";
    const DeclContext *DC = D->getDeclContext();
    while (DC) {
        const NamespaceDecl *ND = dyn_cast<NamespaceDecl>(DC);
        const CXXRecordDecl *RD = dyn_cast<CXXRecordDecl>(DC);
        if (ND) {
            if (namespaceName.empty())
                namespaceName = ND->getNameAsString();
            else
                namespaceName = ND->getNameAsString() + "::" + namespaceName;
        } else if ((className.empty()) && (RD)) {
            className = RD->getQualifiedNameAsString();
        }
        DC = DC->getParent();
    }
}

// Create a vector of matchers and their corresponding MatchFinders
struct Matcher {
    MatchFinder finder;
    MatchFinder::MatchCallback *callback;
    DeclarationMatcher matcher;
};

// @brief: match the AST
void matchAST(ClangTool &Tool, vector<Matcher> matchers) {
    vector<unique_ptr<ASTUnit>> ASTs;
    Tool.buildASTs(ASTs);

    // Register all matchers
    for (auto &m : matchers) {
        m.finder.addMatcher(m.matcher, m.callback);
    }

    // Iterate over ASTs and apply matchers
    for (auto &ast : ASTs) {
        print_policy = PrintingPolicy(ast->getLangOpts());
        print_policy.Bool = 1;
        for (auto &m : matchers) {
            m.finder.matchAST(ast->getASTContext());
        }
    }

    // Clean up dynamically allocated callbacks
    for (auto &m : matchers) {
        delete m.callback;
    }
}