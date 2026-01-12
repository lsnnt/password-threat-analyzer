#include "breach_check.h"
#include <fstream>
#include <iostream>
using namespace std;

BreachResult checkPasswordInBreach(const string& password, const string& wordlistPath) {
    ifstream file(wordlistPath);
    if (!file.is_open()) {
        cerr << "Warning: could not open wordlist file: " << wordlistPath << endl;
        return {false, ""};
    }

    string line;
    while (getline(file, line)) {
        if (line == password) {
            file.close();
            return {true, "Appears in breached password list."};
        }
    }

    file.close();
    return {false, ""};
}
