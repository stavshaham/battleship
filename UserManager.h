// Declares the manager responsible for loading, saving, and authenticating users.
#ifndef BATTLESHIP_USERMANAGER_H
#define BATTLESHIP_USERMANAGER_H

#include "User.h"

#include <string>
#include <vector>

using namespace std;

// Maintains the collection of registered users and its storage file.
class UserManager {
private:
    vector<User> users;
    string fileName;

public:
    // Creates a user manager using the specified account file.
    UserManager(const string& fileName = "users.txt");

    // Loads all registered users from the account file.
    void loadUsers();

    // Saves all registered users to the account file.
    void saveUsers() const;

    // Validates and registers a new user.
    void registerUser(const string& username, const string& password);

    // Authenticates a user and returns the matching account.
    User& login(const string& username, const string& password);
};

#endif