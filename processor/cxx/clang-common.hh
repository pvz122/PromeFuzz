#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/Decl.h"
#include "clang/AST/GlobalDecl.h"
#include "clang/AST/Mangle.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/AST/Stmt.h"
#include "clang/AST/StmtVisitor.h"
#include "clang/AST/Type.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/Basic/SourceManager.h"
#include "clang/Basic/TargetInfo.h"
#include "clang/Frontend/CompilerInstance.h" // clang includes
#include "clang/Frontend/FrontendActions.h"
#include "clang/Lex/Preprocessor.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Path.h"
#include "llvm/Support/Signals.h"

#include <fstream>
#include <iostream> // c++ includes
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>

#include <errno.h>
#include <fcntl.h>
#include <stdio.h> // c includes (for file locks)
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

using namespace clang;
using namespace clang::driver;
using namespace clang::tooling;
using namespace clang::ast_matchers;
using namespace llvm;
using namespace std;

PrintingPolicy print_policy(LangOptions{});

/*
    Whether var come from the system (i.e., /usr/include)
    @in:
        varLoc -> file location of the target
    @out:
        true/false
*/
bool IsSystemVar(string varLoc) {
    if ((varLoc.find("/usr/") == varLoc.npos || varLoc.find("/usr/") != 0) &&
        varLoc.find("lib/gcc/x86_64-linux-gnu/") == varLoc.npos &&
        varLoc.find("lib/clang/") == varLoc.npos &&
        varLoc.find("<Spelling=/usr/") == varLoc.npos &&
        varLoc.find("/Library/Developer/CommandLineTools/") == varLoc.npos &&
        varLoc.find("/opt/homebrew/") == varLoc.npos &&
        varLoc.find("<invalid loc>") == varLoc.npos) {
        return false;
    } else
        return true;
}

std::vector<std::string> split(std::string str, std::string pattern) {
    std::string::size_type pos;
    std::vector<std::string> result;
    str += pattern;
    unsigned int size = str.size();

    for (unsigned int i = 0; i < size; i++) {
        pos = str.find(pattern, i);
        if (pos < size) {
            std::string s = str.substr(i, pos - i);
            result.push_back(s);
            i = pos + pattern.size() - 1;
        }
    }
    return result;
}

std::string ConvertToString(Stmt *From) {
    if (!From)
        return "";
    // SourceRange range = From->getSourceRange();
    // SourceManager &SM = TheCompInst.getSourceManager();
    // llvm::StringRef ref =
    // Lexer::getSourceText(CharSourceRange::getCharRange(range), SM,
    // LangOptions()); return ref.str();

    std::string SStr;
    llvm::raw_string_ostream S(SStr);
    From->printPretty(S, 0, print_policy);
    return S.str();
}

// Remove all const/volatile/[]/&/* here
// FIXME: is there other situation?
const clang::Type *GetBaseType(clang::QualType Qt) {
    // Remove reference (&) and const/volatile qualifiers
    const clang::Type *T =
        Qt.getNonReferenceType().getUnqualifiedType().getTypePtrOrNull();

    while (T) {
        // Remove ParenType
        if (const clang::ParenType *ParenT =
                clang::dyn_cast<clang::ParenType>(T)) {
            T = ParenT->getInnerType().getTypePtrOrNull();
            continue;
        }
        // Strip pointer type
        if (T->isPointerType()) {
            T = T->getPointeeType().getTypePtrOrNull();
            continue;
        }
        // Strip array type
        if (T->isArrayType()) {
            if (const clang::ArrayType *ArrayT =
                    clang::dyn_cast<clang::ArrayType>(T)) {
                T = ArrayT->getElementType().getTypePtrOrNull();
                continue;
            }
        }
        break;
    }

    return T;
}

// Get base type string
string GetBaseTypeString(clang::QualType Qt) {
    const clang::Type *T = GetBaseType(Qt);
    if (T)
        return T->getCanonicalTypeInternal().getAsString();
    else
        return Qt.getAsString();
}

// Get the real type of the typedefed types (i.e. 'unsigned int' of
// 'typedefunsigned int uint')
string GetRealTypeString(QualType Qt) {
    return Qt.getCanonicalType().getAsString(print_policy);
}

// TODO: under what situation T is NULL?
bool AFGenIsBuiltin(QualType Qt) {
    const clang::Type *T = GetBaseType(Qt);
    if (auto rD = T->getAsCXXRecordDecl()) {
        std::string cxxName = rD->getQualifiedNameAsString();
        // TODO: Is there other basic type?
        if (cxxName == "std::basic_string" ||  // std::string
            cxxName == "std::basic_istream" || // std::(w)istream
            cxxName == "std::basic_ostream" || // std::(w)ostream
            cxxName == "std::basic_iostream" ||
            cxxName == "std::basic_istringstream" ||
            cxxName == "std::basic_ostringstream" ||
            cxxName == "std::basic_stringstream" ||
            cxxName == "std::basic_ifstream" ||
            cxxName == "std::basic_ofstream" || // std::(w)ofstream
            cxxName == "std::basic_fstream")
            return true;
    }
    if (T)
        return T->isBuiltinType();
    else
        return Qt->isBuiltinType();
}