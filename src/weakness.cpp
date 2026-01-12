#include "weakness.h"
#include <algorithm>
#include <cctype>
#include <fstream>

using namespace std;

WeaknessOutcome analyzePasswordWeakness(
    const string& password,
    const EntropyOutcome& entropy,
    const BreachResult& breach,
    const string& wordlistPath
) {
    WeaknessOutcome result;

    string lower = password;
    transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

    // 1️⃣ Breach = absolute failure
    if (breach.found) {
        result.primaryReason = "Appears in known breach";
        result.dictionaryBased = true;
        return result;
    }

    // 2️⃣ Wordlist rank check (dominates entropy)
    if (!wordlistPath.empty()) {
        ifstream file(wordlistPath);
        string line;
        long long rank = 1;

        while (getline(file, line)) {
            if (line == password) {
                result.primaryReason = "Appears in common password list";
                result.dictionaryBased = true;
                result.guessRank = rank;
                return result;
            }
            rank++;
        }
    }

    // 3️⃣ Ultra-common passwords
    if (lower == "password" || lower == "admin" || lower == "qwerty") {
        result.primaryReason = "Top-tier dictionary password";
        result.dictionaryBased = true;
        result.guessRank = 1;
        return result;
    }

    // 4️⃣ Dictionary substrings (mutation-based)
    if (lower.find("password") != string::npos ||
        lower.find("admin") != string::npos) {

        result.dictionaryBased = true;
        result.secondaryReasons.push_back("Contains dictionary word");
    }

    // 5️⃣ Pattern detection
    for (size_t i = 1; i < password.size(); i++) {
        if (password[i] == password[i - 1]) {
            result.patterned = true;
            result.secondaryReasons.push_back("Repeated characters");
            break;
        }
    }

    // 6️⃣ Entropy ONLY if no dictionary signals exist
    if (!result.dictionaryBased && entropy.entropy < 40) {
        result.primaryReason = "Low entropy password";
    }

    // 7️⃣ Final classification
    if (result.primaryReason.empty()) {
        if (result.dictionaryBased)
            result.primaryReason = "Predictable password structure";
        else
            result.primaryReason = "No obvious weakness detected";
    }

    return result;
}
