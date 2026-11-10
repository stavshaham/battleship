// Implements user registration, persistence, and login operations.
#include "UserManager.h"
#include <fstream>
#include <stdexcept>

// Creates a manager that uses the specified file for user data.
UserManager::UserManager(const string& fileName) : fileName(fileName) {}

// Reads usernames and password hashes from the user file.
void UserManager::loadUsers() {
    ifstream inputFile(fileName);

    if (!inputFile) {
        // The file may not exist the first time the program runs.
        return;
    }

    users.clear();

    string username;
    size_t passwordHash;

    while (inputFile >> username >> passwordHash) {
        users.emplace_back(username, passwordHash);
    }

    if (!inputFile.eof()) {
        throw runtime_error("The user file contains invalid data.");
    }
}

// Writes every registered user's username and password hash to the file.
void UserManager::saveUsers() const {
    ofstream outputFile(fileName);

    if (!outputFile) {
        throw runtime_error("Could not save the user file.");
    }

    for (const User& user : users) {
        outputFile << user.getUsername() << ' ' << user.getPasswordHash() << endl;
    }
}

// Validates a new account, adds it, and saves the updated user list.
void UserManager::registerUser(const string& username, const string& password) {
    if (username.empty()) {
        throw runtime_error("Username cannot be empty.");
    }

    if (password.empty()) {
        throw runtime_error("Password cannot be empty.");
    }

    if (username.find(' ') != string::npos) {
        throw runtime_error("Username cannot contain spaces.");
    }

    for (const User& user : users) {
        if (user.getUsername() == username) {
            throw runtime_error("That username already exists.");
        }
    }

    size_t passwordHash = User::hashPassword(password);

    users.emplace_back(username, passwordHash);
    saveUsers();
}

// Finds a user and verifies the supplied password.
User& UserManager::login(const string& username, const string& password) {
    for (User& user : users) {
        if (user.getUsername() == username) {
            if (user.verifyPassword(password)) {
                return user;
            }

            throw runtime_error("Incorrect password.");
        }
    }

    throw runtime_error("Username not found.");
}