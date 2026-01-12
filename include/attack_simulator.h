#ifndef ATTACK_SIMULATOR_H
#define ATTACK_SIMULATOR_H

#include <string>
#include <vector>
#include "entropy.h"
#include "weakness.h"
#include "breach_check.h"

using namespace std;

enum HashType {
    FAST_HASH,
    SLOW_HASH
};

struct AttackResult {
    string attackType;
    string estimatedTime;
};

vector<AttackResult> simulateAttacks(
    const EntropyOutcome& entropy,
    const WeaknessOutcome& weakness,
    const BreachResult& breach,
    HashType hashType
);

#endif
