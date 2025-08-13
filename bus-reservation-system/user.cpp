#include "user.h"

User::User(const std::string& uname, const std::string& pword, Role r)
    : username(uname), password(pword), role(r) {}

User::Role User::getRole() const {
    return role;
}

bool User::validatePassword(const std::string& pword) const {
    return password == pword;
}