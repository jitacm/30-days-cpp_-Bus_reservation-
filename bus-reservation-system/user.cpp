#include "user.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>

// A simple (non-cryptographic) hash function for demonstration
std::string User::hashPassword(const std::string& pword) {
    unsigned long hash = 5381;
    for (char c : pword) {
        hash = ((hash << 5) + hash) + static_cast<unsigned char>(c);
    }
    std::stringstream ss;
    ss << std::hex << hash;
    return ss.str();
}

std::vector<User> allUsers;

User::User(const std::string& uname, const std::string& pword_hash, Role r)
    : username(uname), password_hash(pword_hash), role(r) {}

User::Role User::getRole() const {
    return role;
}

bool User::validatePassword(const std::string& pword) const {
    return hashPassword(pword) == password_hash;
}

void User::initializeUsers() {
    std::ifstream in("users.txt");
    if (!in.is_open()) {
        std::cerr << "users.txt not found. Initializing with default admin user.\n";
        User defaultAdmin("admin", hashPassword("adminpass"), ADMIN);
        allUsers.push_back(defaultAdmin);
        
        std::ofstream out("users.txt");
        if (out.is_open()) {
            out << defaultAdmin.username << ":" << defaultAdmin.password_hash << ":" << (defaultAdmin.getRole() == ADMIN ? "admin" : "customer") << "\n";
            out.close();
            std::cout << "Default admin user 'admin' with password 'adminpass' created.\n";
        }
        return;
    }

    std::string line;
    while (std::getline(in, line)) {
        std::stringstream ss(line);
        std::string uname, pword_hash, role_str;
        std::getline(ss, uname, ':');
        std::getline(ss, pword_hash, ':');
        std::getline(ss, role_str);
        
        Role r = (role_str == "admin") ? ADMIN : CUSTOMER;
        allUsers.emplace_back(uname, pword_hash, r);
    }
    in.close();
    std::cout << allUsers.size() << " users loaded from users.txt.\n";
}

User* User::authenticate(const std::string& uname, const std::string& pword) {
    for (auto& user : allUsers) {
        if (user.username == uname && user.validatePassword(pword)) {
            return &user;
        }
    }
    return nullptr;
}