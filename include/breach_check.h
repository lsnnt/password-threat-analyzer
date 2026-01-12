#ifndef BREACH_CHECK_H
#define BREACH_CHECK_H

#include <string>
#include <vector>

using namespace std;

struct BreachResult {
    bool found;            // true if password exists in breach list
    string breachReason;    // example: "Appears in breached password list"
};

// Check if the password exists in a wordlist file
BreachResult checkPasswordInBreach(const string& password, const string& wordlistPath);

#endif
