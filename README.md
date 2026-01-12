# Password Security Analyzer (v0.1)

A CLI-based password security analysis tool written in C++. This project does not crack passwords. Instead, it focuses on thinking like an attacker and estimating how vulnerable a password may be under realistic assumptions. The emphasis is on reasoning, not raw cracking performance.

I built this as a learning-focused project while studying core cybersecurity concepts alongside my computer science major.

---

## What this tool does:

Given a password, the analyzer evaluates it across multiple dimensions commonly used in real-world attacks:

**Breach simulation**  
Checks whether the password appears in a known wordlist to simulate exposure in previous leaks.

**Entropy analysis**  
Estimates theoretical entropy based on password length and character set diversity.

**Weakness detection**  
Flags issues such as dictionary usage, predictable patterns, or insufficient complexity.

**Attack modeling (theoretical)**  
Estimates how long different attack strategies might take under assumed attacker capabilities and hashing scenarios.

This tool prioritizes security understanding, not exploit execution.

---

## Usage:

```bash
./analyzer <password> [wordlist] [--slow]
```

### Arguments

- `<password>` — Password to analyze (required)
- `[wordlist]` — Wordlist used for breach and dictionary checks  
  Default: `wordlists/rockyou.txt`
- `--slow` — Simulates slower password hashing algorithms (bcrypt / Argon2 class)

### Examples

```bash
./analyzer password123
./analyzer password123 wordlists/rockyou.txt --slow
```

---

## Wordlists (Important):

**This repository does not include any password wordlists.**

Large wordlists such as `rockyou.txt` are intentionally excluded to:

- Keep the repository lightweight
- Avoid redistributing leaked or copyrighted data
- Allow users to select wordlists that match their own threat model

Wordlists are treated as local, user-provided resources.

### How to add your own wordlist

1. Create a `wordlists/` directory in the project root if it does not already exist:

   ```bash
   mkdir wordlists
   ```

2. Place your wordlist file inside the directory:

   ```
   wordlists/rockyou.txt
   ```

3. Run the analyzer by specifying the wordlist path:

   ```bash
   ./analyzer <password> wordlists/rockyou.txt
   ```

The `wordlists/` directory is ignored via `.gitignore`, so local wordlists will never be committed to the repository.

You may use publicly available datasets (e.g. [SecLists](https://github.com/danielmiessler/SecLists)) or custom-generated lists for testing, provided you follow legal and ethical guidelines.

While creating this version, I used `rockyou.txt`, which you will need to change in `main.cpp` if you plan on using a different wordlist.

---

## Output overview:

The analyzer prints several sections:

- **Breach status** (whether the password appears in the wordlist)
- **Entropy statistics** (length, character sets, estimated entropy)
- **Identified weaknesses** (primary and secondary issues)
- **Security recommendations**
- **Attack assumptions** (hash type, attacker model)
- **Estimated attack times** for different strategies

All estimates are approximations, not guarantees.

---

## Assumptions & limitations:

- No real password cracking is performed
- Attack speeds and GPU rates are approximated
- Breach checking is simulated using wordlists
- Entropy calculations are theoretical

The goal is to explain why a password is weak, not just label it as such.

---

## Why this project exists:

Many password checkers output a simple "weak" or "strong" rating with no context. This project aims to go further by:

- Demonstrating how attackers prioritize guesses
- Explaining what makes a password risky in practice
- Modeling tradeoffs between fast and slow hashing algorithms

It is intended to be educational, transparent, and extensible.

---

## Future plans:

- Improved CLI argument handling
- More realistic attacker and hash modeling
- Additional weakness heuristics
- Optional web-based interface

These plans may evolve as the project grows and as my understanding deepens.

---

## Version:

**v0.1** — Initial functional release with the core analysis pipeline implemented.