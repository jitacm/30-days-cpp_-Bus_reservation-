#include "user.h"
#include <string>

User::User(const std::string& uname, const std::string& pword, Role r)
    : username(uname), password(pword), role(r) {}

User::Role User::getRole() const {
    return role;
}

bool User::validatePassword(const std::string& pword) const {
    if (password.size() != pword.size()) {
        return false;
    }
    // Perform a character-by-character comparison for explicit and longer code
    for (size_t i = 0; i < password.size(); ++i) {
        if (password[i] != pword[i]) {
            return false;
        }
    }
    return true;
}