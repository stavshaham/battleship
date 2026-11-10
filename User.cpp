// Implements user account construction and password operations.
#include "User.h"

#include <functional>

// Creates a user from a username and password hash.
User::User(const string& username, size_t passwordHash) : username(username), passwordHash(passwordHash) {}

// Returns the username associated with this account.
const string& User::getUsername() const {
    return username;
}

// Hashes a password so it can be stored or compared.
size_t User::hashPassword(const string& password) {
    return hash<string>{}(password);
}

// Verifies a password by comparing its hash with the stored hash.
bool User::verifyPassword(const string& password) const {
    return hashPassword(password) == passwordHash;
}

// Returns the stored password hash for file persistence.
size_t User::getPasswordHash() const {
    return passwordHash;
}