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

/*
 *  Test basic Set and Get functions
 */
TEST(UserTest, SetAndGetFunctions) {
    defaultUser.setName(name);
    defaultUser.setPassword(password);
    defaultUser.setEmail(email);
    defaultUser.setPhone(phone);
    EXPECT_STREQ(name.c_str(), defaultUser.getName().c_str());
    EXPECT_STREQ(password.c_str(), defaultUser.getPassword().c_str());
    EXPECT_STREQ(email.c_str(), defaultUser.getEmail().c_str());
    EXPECT_STREQ(phone.c_str(), defaultUser.getPhone().c_str());
}

/*
 *  Test copy constructor
 */
TEST(UserTest, CopyConstructor) {
    EXPECT_STREQ(anotherUser.getName().c_str(), strUser.getName().c_str());
    EXPECT_STREQ(anotherUser.getPhone().c_str(), strUser.getPhone().c_str());
    EXPECT_STREQ(anotherUser.getEmail().c_str(), strUser.getEmail().c_str());
    EXPECT_STREQ(anotherUser.getPassword().c_str(), strUser.getPassword().c_str());
}

