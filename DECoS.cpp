#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#include <stack>
#include <ctime>
using namespace std;

// Simple hash function (DJB2)
string simpleHash(const string &data) {
    unsigned long hash = 5381;
    for (char c : data) {
        hash = ((hash << 5) + hash) + c;
    }
    return to_string(hash);
}

struct Evidence {
    string evidenceID;
    string description;
    string hashValue;
    CustodyChain custody;
};

unordered_map<string, Evidence> evidenceTable;
