#include "attack_simulator.h"
#include <cmath>
#include <sstream>

using namespace std;

static string formatTime(double seconds) {
    if (seconds < 1)
        return "< 1 second";

    const double minute = 60;
    const double hour   = 3600;
    const double day    = 86400;
    const double year   = 31536000;

    ostringstream out;

    if (seconds < minute)
        out << seconds << " seconds";
    else if (seconds < hour)
        out << seconds / minute << " minutes";
    else if (seconds < day)
        out << seconds / hour << " hours";
    else if (seconds < year)
        out << seconds / day << " days";
    else
        out << seconds / year << " years";

    return out.str();
}

vector<AttackResult> simulateAttacks(
    const EntropyOutcome& entropy,
    const WeaknessOutcome& weakness,
    const BreachResult& breach,
    HashType hashType
) {
    vector<AttackResult> results;

    double guesses = 0;

    // 1️⃣ Absolute failure cases
    if (breach.found) {
        guesses = 1;
    }
    else if (weakness.guessRank > 0) {
        guesses = weakness.guessRank;
    }
    else if (weakness.dictionaryBased) {
        guesses = 1e6; // extended rule-based dictionaries
    }
    else if (weakness.patterned) {
        guesses = 1e7; // masks + patterns
    }
    else {
        // True brute force: entropy finally matters
        guesses = pow(2.0, entropy.entropy);
    }

    // Realistic attacker rates
    double onlineRate = 100;   // credential stuffing / rate-limited APIs
    double gpuRate    = (hashType == FAST_HASH) ? 1e10 : 50;

    results.push_back({
        "Online attack (credential guessing)",
        formatTime(guesses / onlineRate)
    });

    results.push_back({
        "Offline attack (GPU cracking)",
        formatTime(guesses / gpuRate)
    });

    results.push_back({
        "Targeted attack (rules + wordlists)",
        formatTime(guesses / (gpuRate * 10))
    });

    return results;
}
