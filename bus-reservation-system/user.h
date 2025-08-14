#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

class User {
public:
    enum Role { ADMIN, CUSTOMER };

    std::string username;
    Role role;

private:
    std::string password_hash;

public:
    User(const std::string& uname, const std::string& pword_hash, Role r);
    Role getRole() const;
    bool validatePassword(const std::string& pword) const;
    static std::string hashPassword(const std::string& pword);
    static void initializeUsers();
    static User* authenticate(const std::string& uname, const std::string& pword);
};

#endif