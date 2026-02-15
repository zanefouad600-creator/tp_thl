#ifndef GRAMMAR_ANALYZER_H
#define GRAMMAR_ANALYZER_H

#include <iostream>
#include <vector>
#include <string>
#include <set>

using namespace std;

struct Production {
    string left;
    string right;
};

class GrammarAnalyzer {
private:
    vector<Production> grammar;
    set<char> terminals;
    set<char> nonTerminals;

public:

    void addRule(string line) {
        size_t pos = line.find("->");
        if (pos != string::npos) {
            string leftSide = line.substr(0, pos);
            string rightSide = line.substr(pos + 2);

            grammar.push_back({leftSide, rightSide});

            for (char c : leftSide) if (isupper(c)) nonTerminals.insert(c);
            for (char c : rightSide) {
                if (isupper(c)) nonTerminals.insert(c);
                else if (islower(c)) terminals.insert(c);
            }
            cout << "  [Added]: " << leftSide << " -> " << rightSide << endl;
        } else {
            cout << "  [Error]: Invalid format! Use '->'" << endl;
        }
    }


    void displaySymbols() {
        cout << "\n--- Grammar Symbols ---" << endl;
        cout << "Non-Terminals (Vn): ";
        for (char c : nonTerminals) cout << c << " ";
        cout << "\nTerminals (Vt): ";
        for (char c : terminals) cout << c << " ";
        cout << endl;
    }
};

#endif