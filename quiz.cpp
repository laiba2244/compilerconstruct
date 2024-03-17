#include <iostream>
using namespace std;

int count = 0;
string expr;

bool G();
bool U();
bool D();

int main() {
    char choice;
    do {
        cout << "Enter the string: ";
        cin >> expr;
        count = 0; // Reset count for each input string
        bool accepted = G();
        if (accepted && count == expr.length()) {
            cout << "Accepted " << endl;
        } else {
            cout << "Rejected" << endl;
        }
        cout << "Do you want to continue (y/n)? ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');
    return 0;
}

bool G() {
    
    if (U()) {
        G(); // Recursive call for UG
        return true;
    }
    return true; // null production
}

bool U() {
  
    if (expr[count] == 'u') {
        count++;
        if (D()) {
            return true;
        }
        return true; // null production
    }
    return false;
}

bool D() {
    
    if (expr[count] == 'd') {
        count++;
        if (D()) {
            return true;
        }
        return true; // null production
    }
    return false;
}