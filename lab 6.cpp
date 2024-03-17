#include <iostream>
#include <string>
#include <cctype>

using namespace std;

// Function prototypes
bool S(string input);
bool V(string input);
bool A(string input);
bool I(string input);
bool C(string input);
bool E(string input);
bool relop(string input);
bool type(string input);

// Global variables
int pos = 0;

int main() {
    string input;
    cout << "Enter an expression: ";
    getline(cin, input);
    if (S(input)) {
        cout << "Accepted" << endl;
    } else {
        cout << "Rejected" << endl;
    }
    return 0;
}

bool S(string input) {
    return V(input) || A(input) || I(input);
}

bool V(string input) {
    string keywords[] = {"int", "float", "double", "char", "boolean"};
    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); ++i) {
        string keyword = keywords[i];
        if (input.substr(pos, keyword.length()) == keyword) {
            pos += keyword.length();
            if (input[pos] == ' ') {
                pos++;
                while (input[pos] != ';') {
                    if (!isalpha(input[pos]) && !isdigit(input[pos])) {
                        return false;
                    }
                    pos++;
                }
                pos++;
                return true;
            }
        }
    }
    return false;
}

bool A(string input) {
    if (isalpha(input[pos])) {
        pos++;
        if (input[pos] == '=') {
            pos++;
            return E(input);
        }
    }
    return false;
}

bool I(string input) {
    if (input.substr(pos, 2) == "if") {
        pos += 2;
        if (input[pos] == '(') {
            pos++;
            if (C(input)) {
                if (input[pos] == ')') {
                    pos++;
                    if (input[pos] == '{') {
                        pos++;
                        while (S(input.substr(pos))) {
                            if (input[pos] == '}') {
                                pos++;
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool C(string input) {
    if (E(input)) {
        if (relop(input)) {
            return E(input);
        }
    }
    return false;
}

bool E(string input) {
    if (isalpha(input[pos])) {
        pos++;
        return true;
    } else if (isdigit(input[pos])) {
        pos++;
        return true;
    } else if (input[pos] == '(') {
        pos++;
        if (E(input)) {
            if (input[pos] == '+' || input[pos] == '-') {
                pos++;
                if (E(input)) {
                    if (input[pos] == ')') {
                        pos++;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool relop(string input) {
    string relops[] = {"==", "!=", "<", ">", "<=", ">="};
    for (int i = 0; i < sizeof(relops) / sizeof(relops[0]); ++i) {
        string relop = relops[i];
        if (input.substr(pos, relop.length()) == relop) {
            pos += relop.length();
            return true;
        }
    }
    return false;
}