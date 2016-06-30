#include "User.h"

User::User() : name(""), {}
User::User(std::string userName, std::string userPassword,
           std::string userEmail, std::string userPhone);
std::string User::getName() const;
void User::setName(std::string name);
std::string User::getPassword() const;
void User::setPassword(std::string password);
std::string User::getEmail() const;
void User::setEmail(std::string email);
std::string User::getPhone() const;
void User::setPhone(std::string phone);
