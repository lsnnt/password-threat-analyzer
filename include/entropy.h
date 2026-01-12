#ifndef ENTROPY_H
#define ENTROPY_H

#include <string>

using namespace std;

struct EntropyOutcome {
    int length;
    int charsetSize;
    double entropy;
    string strength;
};

EntropyOutcome analyzePasswordEntropy(const string& password);

#endif



//Still pretty new to C/C++ so I had to take the help of AI to write these headers.