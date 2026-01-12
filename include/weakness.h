#ifndef WEAKNESS_H
#define WEAKNESS_H

#include <string>
#include <vector>
#include "entropy.h"
#include "breach_check.h"

using namespace std;

struct WeaknessOutcome {
    string primaryReason;
    vector<string> secondaryReasons;

    bool dictionaryBased = false;
    bool patterned = false;
    long long guessRank = -1; 
};

WeaknessOutcome analyzePasswordWeakness(
    const string& password,
    const EntropyOutcome& entropy,
    const BreachResult& breach,
    const string& wordlistPath
);

#endif


//Still pretty new to C/C++ so I had to take the help of AI to write these headers.