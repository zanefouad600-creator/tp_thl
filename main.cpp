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
        }
    }

    int checkGrammarType() {
        if (grammar.empty()) return -1;
        int currentType = 3;

        for (const auto& p : grammar) {
            if (p.left.length() > p.right.length()) return 0;

            if (p.left.length() > 1 && currentType > 1) currentType = 1;

            if (currentType >= 2) {
                if (p.left.length() != 1 || !isupper(p.left[0])) {
                    currentType = 1;
                }
            }

            if (currentType == 3) {
                bool isRegular = false;
                if (p.right.length() == 1 && islower(p.right[0])) isRegular = true;
                if (p.right.length() == 2 && islower(p.right[0]) && isupper(p.right[1])) isRegular = true;
                if (p.right == "e") isRegular = true;
                if (!isRegular) currentType = 2;
            }
        }
        return currentType;
    }

    void printSummary() {
        if (grammar.empty()) return;

        cout << "\n--- Analysis Results ---" << endl;
        cout << "Non-Terminals: ";
        for (char c : nonTerminals) cout << c << " ";
        cout << "\nTerminals: ";
        for (char c : terminals) cout << c << " ";

        int type = checkGrammarType();
        cout << "\nGrammar Type: Type " << type << " (";
        if (type == 3) cout << "Regular";
        else if (type == 2) cout << "Context-Free";
        else if (type == 1) cout << "Context-Sensitive";
        else cout << "Unrestricted";
        cout << ")" << endl;
    }
};

int main() {
    GrammarAnalyzer myGrammar;
    string input;

    cout << "Enter rules (e.g., S->aB). Type 'exit' to see the type." << endl;

    while (true) {
        cout << "> ";
        cin >> input;
        if (input == "exit") break;
        myGrammar.addRule(input);
    }

    myGrammar.printSummary();
    return 0;
}