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
    // This is the constructor for the User class.
    User(const std::string& uname, const std::string& pword, Role r);
    // This function returns the user's role.
    Role getRole() const;
    // This function checks if the provided password is correct.
    bool validatePassword(const std::string& pword) const;
};

#endif