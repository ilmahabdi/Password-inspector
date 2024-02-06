#include <iostream>
#include <fstream>
#include <cstring> // Include for strlen
using namespace std;

int main() {
    const int MAX_PASSWORDS = 15;
    string breachedPasswords[MAX_PASSWORDS];
    int numBreachedPasswords = 0;

    ifstream passwordFile("breached_passwords.txt");

    if (passwordFile.is_open()) {
        while (numBreachedPasswords < MAX_PASSWORDS && passwordFile >> breachedPasswords[numBreachedPasswords]) {
            numBreachedPasswords++;
        }
        passwordFile.close();
    } else {
        cerr << "Unable to open the file.";
        return 1;
    }

    // Get user input
    cout << "Enter your password: ";
    char userPassword[100]; // Assuming a maximum password length of 100 characters
    cin >> userPassword;

    size_t n = strlen(userPassword);
    bool hasSpecialCharacter = false;

    for (size_t i = 0; i < n; ++i) {
        // Check if the character is a special character
        if (userPassword[i] == '!' || userPassword[i] == '@' || userPassword[i] == '#' || userPassword[i] == '$' || userPassword[i] == '%') {
            hasSpecialCharacter = true;
            break;
        }
    }

    if (n < 10 || !hasSpecialCharacter) {
        cout << "You need a stronger password with at least 10 characters and a special character." << endl;
    }

    // Check if the entered password is in the breached list
    bool passwordBreached = false;
    for (int i = 0; i < numBreachedPasswords; i++) {
        if (userPassword == breachedPasswords[i]) {
            passwordBreached = true;
            break;
        }
    }

    if (passwordBreached) {
        cout << "Your password has been breached. Please choose a stronger one." << endl;
    } else {
        cout << "Your password appears to be secure." << endl;
    }

    return 0;
}
