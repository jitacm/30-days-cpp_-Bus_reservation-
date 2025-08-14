#ifndef USER_H
#define USER_H

#include <string>

class User {
public:
    enum Role { ADMIN, CUSTOMER };

private:
    std::string username;
    std::string password;
    Role role;

public:
    User(const std::string& uname, const std::string& pword, Role r);
    Role getRole() const;
    bool validatePassword(const std::string& pword) const;
};

#endif