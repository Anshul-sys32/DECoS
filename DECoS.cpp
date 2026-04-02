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

queue<string> accessQueue;
stack<string> adminUndo;

void registerEvidence() {
    Evidence e;
    cout << "Enter Evidence ID: ";
    cin >> e.evidenceID;
    cin.ignore();

    cout << "Enter Evidence Description: ";
    getline(cin, e.description);

    e.hashValue = simpleHash(e.description);
    e.custody.addRecord("Evidence Registered", "Admin");

    evidenceTable[e.evidenceID] = e;
    adminUndo.push(e.evidenceID);

    cout << "Evidence registered successfully.\n";
}

int main() {
    int choice;

    do {
        cout << "\n--- Digital Evidence Chain of Custody System ---\n";
        cout << "1. Register Evidence\n";
        cout << "2. Request Evidence Access\n";
        cout << "3. Process Access Request\n";
        cout << "4. Verify Evidence Integrity\n";
        cout << "5. View Chain of Custody\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: registerEvidence(); break;
            case 2: requestAccess(); break;
            case 3: processAccess(); break;
            case 4: verifyIntegrity(); break;
            case 5: viewCustody(); break;
            case 0: cout << "Exiting system...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}
