#include <gtest/gtest.h>
#include <string>
#include <list>
#include <vector>
#include <memory>
#include <functional>
#include <iterator>
#include <fstream>
#include <iostream>
#include "utility.h"

#define TESTWRITETOFILE
//  Haven't found a good method to test writeToFile yet
#ifdef TESTWRITETOFILE
#define DEBUG
#define private public
#endif

#include "Storage.hpp"

#ifdef TESTWRITETOFILE
#undef private
#endif

using std::string;
using std::list;
using std::vector;
using std::shared_ptr;
using std::function;

using namespace utility;

class StorageTest: public ::testing::Test {
    //  Use static variables to hold the configuration for the entire StorageTest case
    //  After each test, TearDown() method will be invoked automatically and set the the storage to default
protected:
    static void TearDownTestCase() {
        recFiles();
    }
    virtual void SetUp() {
        storage = Storage::getInstance();
        simUserList = {user1, user2, user3};
        simMeetingList = {meeting1, meeting2};
    }
    virtual void TearDown() {
        storage->deleteUser([](const User &) {return true;});
        storage->deleteMeeting([](const Meeting &) {return true;});
        storage->createUser(user1);
        storage->createUser(user2);
        storage->createUser(user3);
        storage->createMeeting(meeting1);
        storage->createMeeting(meeting2);
    }

    static bool getAllUser(const User &user) {
        return true;
    }
    static bool getAllMeeting(const Meeting &meeting) {
        return true;
    }
    //  sim*List are taken as a reference to the list in storage
    list<User> simUserList;
    list<Meeting> simMeetingList;
    shared_ptr<Storage> storage;
    //  user1-user3 and meeting1, meeting2 are default configuration for the test(written in users.csv)
    static const User user1, user2, user3, user4;
    static const Meeting meeting1, meeting2, meeting3;
};

const User StorageTest::user1("Lara Croft", "TombRaidar", "lara@email.com", "13800000000");
const User StorageTest::user2("Geralt of Rivia", "TheWithcer", "geralt@email.com", "13700000000");
const User StorageTest::user3("Naked Snake", "MetalGearSolid", "snake@email.com", "13600000000");
const User StorageTest::user4("Trevor", "GrandTheftAutoV", "Trevor@email.com", "13500000000");
const Meeting StorageTest::meeting1("Naked Snake", vector<string>({"Lara Croft"}),
                                    Date::stringToDate("2016-07-08/11:10"),
                                    Date::stringToDate("2016-07-08/12:05"),
                                    "I wanna Quite");
const Meeting StorageTest::meeting2("Geralt of Rivia", vector<string>({"Naked Snake", "Lara Croft"}),
                                    Date::stringToDate("2016-07-10/15:00"),
                                    Date::stringToDate("2016-07-10/18:00"),
                                    "Want a few rounds of Gwent?");
const Meeting StorageTest::meeting3("Lara Croft", vector<string>({"Geralt of Rivia"}),
                                    Date::stringToDate("2016-07-11/17:21"),
                                    Date::stringToDate("2016-07-11/19:00"),
                                    "???");

/*
 *  Test singleton
 */
TEST_F(StorageTest, Singleton) {
    EXPECT_EQ(storage.get(), Storage::getInstance().get());
}

/*
 *  Test the initialization of a storage(read from file)
 */
TEST_F(StorageTest, Initialization) {
    list<User> userList = storage->queryUser(getAllUser);
    list<Meeting> meetingList = storage->queryMeeting(getAllMeeting);
    utility::testUserList(simUserList, userList);
    utility::testMeetingList(simMeetingList, meetingList);
}

/*
 *  Test operations on m_userList
 */
TEST_F(StorageTest, UserOperation) {
    //  Create user
    storage->createUser(user4);
    simUserList.push_back(user4);
    list<User> userList = storage->queryUser(getAllUser);
    utility::testUserList(simUserList, userList);
    //  Update user
    string snakeName = "Venom Snake", snakePassword = "MetalGearSolidV";
    auto filter = [&](const User &user) {
        return judgeUserEqual(user, user4) || judgeUserEqual(user, user3);
    };
    auto switcher = [&](User &user) {
        if (judgeUserEqual(user, user3)) {
            user.setName(snakeName);
            user.setPassword(snakePassword);
        }
        else if (judgeUserEqual(user, user4)) {
            user.setName("Trevor Philips");
        }
    };
    int updateNum = storage->updateUser(filter, switcher);
    for (auto &user : simUserList) {
        switcher(user);
    }
    EXPECT_EQ(2, updateNum);
    userList = storage->queryUser(getAllUser);
    utility::testUserList(simUserList, userList);
    //  Delete user
    storage->deleteUser([&](const User &user) {
            if (user.getName() == "Lara Croft" || user.getName() == "Trevor Philips") {
                return true;
            }
            return false;
        });
    userList = storage->queryUser(getAllUser);
    simUserList.pop_back();
    simUserList.erase(simUserList.begin()++);
    utility::testUserList(simUserList, userList);
}

/*
 *  Test operations on m_meetingList
 */
TEST_F(StorageTest, MeetingOperation) {
    //  Create meeting
    storage->createMeeting(meeting3);
    simMeetingList.push_back(meeting3);
    list<Meeting> meetingList = storage->queryMeeting(getAllMeeting);
    utility::testMeetingList(simMeetingList, meetingList);
    //  Update meeting
    auto filter = [&](const Meeting &meeting) {
        return judgeMeetingEqual(meeting, meeting2) || judgeMeetingEqual(meeting, meeting3);
    };
    auto switcher = [&](Meeting &meeting) {
        if (judgeMeetingEqual(meeting, meeting2)) {
            meeting.setStartDate(Date::stringToDate("2016-07-09/12:00"));
            meeting.setEndDate(Date::stringToDate("2016-07-09/15:00"));
        }
        else if (judgeMeetingEqual(meeting, meeting3)) {
            meeting.setTitle("?????");
        }
    };
    int updateNum = storage->updateMeeting(filter, switcher);
    for (auto &meeting : simMeetingList) {
        if (filter(meeting)) {
            switcher(meeting);
        }
    }
    EXPECT_EQ(2, updateNum);
    meetingList = storage->queryMeeting(getAllMeeting);
    utility::testMeetingList(simMeetingList, meetingList);
    //  Delete meeting
    storage->deleteMeeting([&](const Meeting &meeting) {
            if (meeting.getTitle() == "?????" ||
                meeting.getTitle() == meeting1.getTitle()) {
                return true;
            }
            return false;
        });
    simMeetingList.pop_front();
    simMeetingList.pop_back();
    meetingList = storage->queryMeeting(getAllMeeting);
    utility::testMeetingList(simMeetingList, meetingList);
}

#ifdef TESTWRITETOFILE

class StoragePrivateTest : public StorageTest {
public:
    virtual void TearDown() {
        recFiles();
    }
};

/*
 *  If no data files to read, then create empty lists
 */
TEST_F(StoragePrivateTest, NoFileToRead) {
    storage->m_instance.reset();
    ASSERT_EQ(1, storage.use_count());
    storage.reset();
    std::remove(userPath);
    std::remove(meetingPath);
    storage = Storage::getInstance();
    EXPECT_TRUE(storage->queryUser(getAllUser).empty());
    EXPECT_TRUE(storage->queryMeeting(getAllMeeting).empty());
    storage->m_instance.reset();
    storage.reset();
}

/*
 *  Test destrutor and if the files are written correctly
 */
TEST_F(StoragePrivateTest, WriteToFile) {
    storage->createUser(user4);
    storage->deleteMeeting([&](const Meeting &meeting) {
            return meeting.getTitle() == meeting1.getTitle();
        });
    storage->m_instance.reset();
    storage.reset();

    std::fstream userStandardfs, userTestfs;
    userStandardfs.open(cmpUserPath, std::fstream::in);
    userTestfs.open(userPath, std::fstream::in);
    string userStandard, userTest;
    while (userStandardfs || userTestfs) {
        std::getline(userStandardfs, userStandard);
        std::getline(userTestfs, userTest);
        ASSERT_EQ(userStandard, userTest);
    }

    std::fstream meetingStandardfs, meetingTestfs;
    meetingStandardfs.open(cmpMeetingPath, std::fstream::in);
    meetingTestfs.open(meetingPath, std::fstream::in);
    string meetingStandard, meetingTest;
    while (meetingStandardfs || meetingTestfs) {
        std::getline(meetingStandardfs, meetingStandard);
        std::getline(meetingTestfs, meetingTest);
        ASSERT_EQ(meetingStandard, meetingTest);
    }

    userStandardfs.close();
    userTestfs.close();
    meetingStandardfs.close();
    meetingTestfs.close();
}

#endif  //  TESTWRITETOFILE
