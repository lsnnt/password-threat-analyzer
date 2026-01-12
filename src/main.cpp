#include <iostream>
#include <string>

#include "entropy.h"
#include "weakness.h"
#include "attack_simulator.h"
#include "breach_check.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage:\n";
        cout << "  ./analyzer <password> [wordlist] [--slow]\n\n";
        cout << "Options:\n";
        cout << "  --slow    Simulate slow hashes (bcrypt / Argon2)\n";
        cout << "\nExample:\n";
        cout << "  ./analyzer password123 --slow\n";
        return 0;
    }

    // Required argument
    string password = argv[1];

    // Defaults
    string wordlist = "wordlists/rockyou.txt";
    HashType hashType = FAST_HASH;

    // Parse optional arguments
    for (int i = 2; i < argc; i++) {
        string arg = argv[i];

        if (arg == "--slow") {
            hashType = SLOW_HASH;
        }
        else if (arg == "--fast") {
            hashType = FAST_HASH;
        }
        else {
            wordlist = arg; // treat as wordlist path
        }
    }

    // 1️⃣ Breach check
    BreachResult breach = {false, ""};
    if (!wordlist.empty()) {
        breach = checkPasswordInBreach(password, wordlist);
    }

    cout << "[ BREACH CHECK ]\n";
    if (breach.found)
        cout << "Status : COMPROMISED (" << breach.breachReason << ")\n";
    else
        cout << "Status : Not found in known breaches\n";

    // 2️⃣ Entropy analysis
    EntropyOutcome entropy = analyzePasswordEntropy(password);

    cout << "\n[ ENTROPY ANALYSIS ]\n";
    cout << "Length            : " << entropy.length << "\n";
    cout << "Character Set Size: " << entropy.charsetSize << "\n";
    cout << "Entropy           : " << entropy.entropy << " bits\n";
    cout << "Strength          : " << entropy.strength << "\n";

    // 3️⃣ Weakness analysis
    WeaknessOutcome weakness = analyzePasswordWeakness(
        password,
        entropy,
        breach,
        wordlist
    );

    cout << "\n[ WEAKNESS ANALYSIS ]\n";
    cout << "Primary Reason    : " << weakness.primaryReason << "\n";
    if (!weakness.secondaryReasons.empty()) {
        cout << "Secondary Issues  : ";
        for (const auto& s : weakness.secondaryReasons)
            cout << s << " ";
        cout << "\n";
    }

    // 4️⃣ Recommendations
    cout << "\n[ RECOMMENDATION ]\n";

    bool needsFix = false;

    if (weakness.dictionaryBased) {
        cout << "- Avoid dictionary words and common passwords\n";
        needsFix = true;
    }

    if (weakness.patterned) {
        cout << "- Avoid repeated or predictable character patterns\n";
        needsFix = true;
    }

    if (entropy.entropy < 60) {
        cout << "- Increase password length to at least 12 characters\n";
        cout << "- Use uppercase, digits, and symbols\n";
        needsFix = true;
    }

    if (breach.found) {
        cout << "- Immediately change this password everywhere it was reused\n";
        needsFix = true;
    }

    if (!needsFix) {
        cout << "- No immediate changes required\n";
        cout << "- Consider using a password manager\n";
    }

    // 5️⃣ Attack assumptions
    cout << "\n[ ATTACK ASSUMPTIONS ]\n";
    cout << "Hash type        : ";
    if (hashType == FAST_HASH)
        cout << "FAST (MD5 / NTLM class)\n";
    else
        cout << "SLOW (bcrypt / Argon2 class)\n";

    cout << "Online rate      : 5 guesses/sec\n";

    if (hashType == FAST_HASH)
        cout << "GPU rate         : ~10^10 guesses/sec\n";
    else
        cout << "GPU rate         : ~50 guesses/sec\n";

    if (weakness.dictionaryBased)
        cout << "Wordlist focus   : Common passwords prioritized\n";
    else
        cout << "Wordlist focus   : Full keyspace\n";

    // 6️⃣ Attack simulation
    auto attacks = simulateAttacks(
        entropy,
        weakness,
        breach,
        hashType
    );

    cout << "\n[ ATTACK SIMULATION ]\n";
    for (const auto& a : attacks)
        cout << a.attackType << " : " << a.estimatedTime << "\n";

    return 0;
}
