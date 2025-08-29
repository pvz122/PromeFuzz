#include "processor.hh"

// ==============================
//  Struct definitions
// ==============================

struct CallingInfo {
    string callerName;
    string callerDeclLoc;
    string calleeName;
    string calleeDeclLoc;

    friend void to_json(json &j, const CallingInfo &ci) {
        j = json{{"callerName", ci.callerName},
                 {"callerDeclLoc", ci.callerDeclLoc},
                 {"calleeName", ci.calleeName},
                 {"calleeDeclLoc", ci.calleeDeclLoc}};
    }
};

// ==============================
// Global variables to store the information
// ==============================
map<string, CallingInfo> callingInfoMap;

string filePath;