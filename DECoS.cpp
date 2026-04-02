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

struct CustodyNode {
    string action;
    string user;
    string timestamp;
    CustodyNode* next;

    CustodyNode(string a, string u, string t) {
        action = a;
        user = u;
        timestamp = t;
        next = NULL;
    }
};

class CustodyChain {
    CustodyNode* head;
    CustodyNode* tail;

public:
    CustodyChain() {
        head = tail = NULL;
    }

    void addRecord(string action, string user) {
        time_t now = time(0);
        string ts = ctime(&now);
        CustodyNode* node = new CustodyNode(action, user, ts);

        if (!head) {
            head = tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }

    void display() {
        CustodyNode* temp = head;
        while (temp) {
            cout << "Action: " << temp->action
                 << " | User: " << temp->user
                 << " | Time: " << temp->timestamp;
            temp = temp->next;
        }
    }
};
