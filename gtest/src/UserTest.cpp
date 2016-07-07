#include <gtest/gtest.h>
#include <string>
#include "User.hpp"

using std::string;

string name = "Name";
string password = "PaSsW0Rd";
string email = "email@email.com";
string phone = "13800000000";
User defaultUser;
User strUser(name, password, email, phone);
User anotherUser(strUser);

TEST(UserTest, SetAndGetFunctions) {
    defaultUser.setName(name);
    defaultUser.setPassword(password);
    defaultUser.setEmail(email);
    defaultUser.setPhone(phone);
    EXPECT_STREQ(defaultUser.getName().c_str(), name.c_str());
    EXPECT_STREQ(defaultUser.getPassword().c_str(), password.c_str());
    EXPECT_STREQ(defaultUser.getEmail().c_str(), email.c_str());
    EXPECT_STREQ(defaultUser.getPhone().c_str(), phone.c_str());
}

TEST(UserTest, CopyConstructor) {
    EXPECT_STREQ(strUser.getName().c_str(), anotherUser.getName().c_str());
    EXPECT_STREQ(strUser.getPhone().c_str(), anotherUser.getPhone().c_str());
    EXPECT_STREQ(strUser.getEmail().c_str(), anotherUser.getEmail().c_str());
    EXPECT_STREQ(strUser.getPassword().c_str(), anotherUser.getPassword().c_str());
}

