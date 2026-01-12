#include "entropy.h"
#include <cmath>
#include <cctype>
using namespace std;

EntropyOutcome analyzePasswordEntropy(const string& password) {
    bool hasSymbol = false;
    bool hasLower = false;
    bool hasUpper = false;
    bool hasDigit = false;
   
    for (char c : password) {
        if (islower(static_cast<unsigned char>(c)))
            hasLower = true;
        else if (isupper(static_cast<unsigned char>(c)))
            hasUpper = true;
        else if (isdigit(static_cast<unsigned char>(c)))
            hasDigit = true;
        else
            hasSymbol = true;
    }

    int charsetSize = 0;
    if (hasLower)  charsetSize += 26; //letters in the English alphabet.
    if (hasUpper)  charsetSize += 26;  //same thing but in upper cases.
    if (hasDigit)  charsetSize += 10;  //numbers from 0 to 9.
    if (hasSymbol) charsetSize += 32;  //according to a Google search there are apparently 32 common symbols in the printable range, which is the reason why I added 32.

    int length = password.length();
    double entropy = 0.0;

    if (length > 0 && charsetSize > 0) {
        entropy = length * log2(charsetSize);
    }

    // This password entropy method basically sees how many bits the password is using and based on how big it is it'll determine whether the password is easier or harder to crack.

    string strength;
    if (entropy < 40)
        strength = "WEAK";
    else if (entropy < 60)
        strength = "MEDIUM";
    else
        strength = "STRONG";

    EntropyOutcome result;
    result.length = length;
    result.charsetSize = charsetSize;
    result.entropy = entropy;
    result.strength = strength;

    return result;
}
