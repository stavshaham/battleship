// Declares a registered Battleship user account.
#ifndef BATTLESHIP_USER_H
#define BATTLESHIP_USER_H

#include <string>

using namespace std;

// Stores a username and the hashed password associated with it.
class User {
private:
    string username;
    size_t passwordHash;

public:
    // Creates a user with a username and an existing password hash.
    User(const string& username, size_t passwordHash);

    // Returns the user's username.
    const string& getUsername() const;

    // Checks whether a password matches the stored password hash.
    bool verifyPassword(const string& password) const;

    // Produces a hash value for a password.
    static size_t hashPassword(const string& password);

    // Returns the stored password hash.
    size_t getPasswordHash() const;
};

#endif