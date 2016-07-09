#include <gtest/gtest.h>
#include <string>
#include <list>
#include <memory>
#include <functional>
#include <iterator>
#include "Storage.hpp"

using std::string;
using std::list;
using std::shared_ptr;
using std::function;

bool judgeUserEqual(const User &user1, const User &user2) {
    if (user1.getName() == user2.getName() &&
        user1.getPassword() == user2.getPassword() &&
        user1.getEmail() == user2.getEmail() &&
        user1.getPhone() == user2.getPhone()) {
        return true;
    }
    return false;
}

bool findUser(list<User> &list, const User &user) {
    for (auto it = list.begin(); it != list.end(); ++it) {
        if (judgeUserEqual(*it, user)) {
            return true;
        }
    }
    return false;
}

function<bool(const User &)> getAllUser = [](const User &user) {
    return true;
};

function<bool(const Meeting &)> getAllMeeting = [](const Meeting &meeting) {
    return true;
};

User user1("Lara","TombRaidar","lara@email.com","13800000000");
User user2("Geralt","Withcer","geralt@email.com","13700000000");
User user3("BigBoss","MetalGearSolid","snake@email.com","13600000000");
User user4("Trevor", "GrandTheftAutoV", "Trevor@email.com", "13500000000");

/*
 *  Test singleton
 */
TEST(StorageTest, SingletonTest) {
    EXPECT_EQ(Storage::getInstance().get(), Storage::getInstance().get());
}

/*
 *  Test operations on m_userList
 */
TEST(StorageTest, UserTest) {
    shared_ptr<Storage> storage(Storage::getInstance());
    //  Initialization
    list<User> userList = storage->queryUser(getAllUser);
    EXPECT_EQ(3, userList.size());
    EXPECT_TRUE(findUser(userList, user1));
    EXPECT_TRUE(findUser(userList, user2));
    EXPECT_TRUE(findUser(userList, user3));
    //  Create user
    storage->createUser(user4);
    userList = storage->queryUser(getAllUser);
    EXPECT_EQ(4, userList.size());
    EXPECT_TRUE(findUser(userList, user4));
    //  Update user
    int updateNum = storage->updateUser([](const User &user) {
            return judgeUserEqual(user, user4);
        },
        [](User &user) {
            user.setName("Trevor Philips");
        });
    EXPECT_EQ(1, updateNum);
    userList = storage->queryUser(getAllUser);
    EXPECT_EQ(4, userList.size());
    EXPECT_TRUE([](const list<User> &list) {
            for (auto it = list.begin(); it != list.end(); ++it) {
                if (it->getName() == "Trevor Philips") {
                    return true;
                }
            }
            return false;
        }(userList));
    //  Delete user
    storage->deleteUser([](const User &user) {
            return user.getName() == "Trevor Philips";
        });
    userList = storage->queryUser(getAllUser);
    EXPECT_EQ(3, userList.size());
    EXPECT_FALSE([](const list<User> &list) {
            for (auto it = list.begin(); it != list.end(); ++it) {
                if (it->getName() == "Trevor Philips") {
                    return true;
                }
            }
            return false;
        }(userList));
}


TEST(StorageTest, MassiveUserTest) {
    
}
