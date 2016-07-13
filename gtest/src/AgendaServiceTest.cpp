#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <list>
#include "AgendaService.hpp"

using std::vector;
using std::string;
using std::list;

class AgendaServiceTest : public ::testing::Test {
protected:
    static void SetUpTestCase() {
        
    }
    void userListTest(const list<User> &expectList, const list<User> &actualList) {
        for (auto &user : expectList) {
            EXPECT_TRUE([](const User &user, const list<User> &list) {
                    for (auto &u : list) {
                        if (user.getName() == u.getName() &&
                            user.getPassword() == u.getPassword() &&
                            user.getEmail() == user.getEmail() &&
                            user.getPhone() == user.getPhone()) {
                            return true;
                        }
                    }
                    return false;
                }(user, actualList));
        }
    }
    void invalidMeetingIntervalTest(const string &startDate, const string &endDate) {
        EXPECT_FALSE(service.createMeeting(meeting3.getSponsor(),
                                           meeting3.getTitle(),
                                           startDate,
                                           endDate,
                                           meeting3.getParticipator()));
    }
    void validMeetingIntervalTest(const string &startDate, const string &endDate) {
        EXPECT_TRUE(service.createMeeting(meeting3.getSponsor(),
                                           meeting3.getTitle(),
                                           startDate,
                                           endDate,
                                           meeting3.getParticipator()));
    }
    AgendaService service;
    //  user1-user3 and meeting1, meeting2 are default configuration for the test
    //  (written in data/users.csv and data/meetings.csv)
    static const User user1, user2, user3, user4;
    static const Meeting meeting1, meeting2, meeting3, meeting4, meeting5, meeting6;
    static const Meeting meetingSamples[6];
};

const User AgendaServiceTest::user1("Lara Croft", "TombRaidar",
                                    "lara@email.com", "13800000000");
const User AgendaServiceTest::user2("Geralt of Rivia", "TheWithcer",
                                    "geralt@email.com", "13700000000");
const User AgendaServiceTest::user3("Naked Snake", "MetalGearSolid",
                                    "snake@email.com", "13600000000");
const User AgendaServiceTest::user4("Trevor", "GrandTheftAutoV",
                                    "Trevor@email.com", "13500000000");
const Meeting AgendaServiceTest::meeting1("Naked Snake",
                                          vector<string>({"Lara Croft"}),
                                          Date::stringToDate("2016-07-08/11:10"),
                                          Date::stringToDate("2016-07-08/12:05"),
                                          "I wanna Quite");
const Meeting AgendaServiceTest::meeting2("Geralt of Rivia",
                                          vector<string>({"Naked Snake", "Lara Croft"}),
                                          Date::stringToDate("2016-07-10/15:00"),
                                          Date::stringToDate("2016-07-10/18:00"),
                                          "Want a few rounds of Gwent?");
const Meeting AgendaServiceTest::meeting3("Lara Croft",
                                          vector<string>({"Trevor"}),
                                          Date::stringToDate("2017-07-11/17:21"),
                                          Date::stringToDate("2017-07-11/19:00"),
                                          "???");
const Meeting AgendaServiceTest::meeting4("Trevor",
                                          vector<string>({"Geralt of Rivia"}),
                                          Date::stringToDate("2018-07-11/17:21"),
                                          Date::stringToDate("2018-07-11/19:00"),
                                          "????");
const Meeting AgendaServiceTest::meeting5("Geralt of Rivia",
                                          vector<string>({"Naked Snake"}),
                                          Date::stringToDate("2019-07-11/17:21"),
                                          Date::stringToDate("2019-07-11/19:00"),
                                          "?????");
const Meeting AgendaServiceTest::meeting6("Geralt of Rivia",
                                          vector<string>({"Trevor"}),
                                          Date::stringToDate("2020-07-11/17:21"),
                                          Date::stringToDate("2020-07-11/19:00"),
                                          "??????");
const Meeting AgendaServiceTest::meetingSamples[6] = {meeting1, meeting2, meeting3, meeting4, meeting5, meeting6};
/*
 *  Test operations on user
 */
TEST_F(AgendaServiceTest, PureUserTest) {
    //  Login test
    EXPECT_TRUE(service.userLogIn(user1.getName(), user1.getPassword()));
    EXPECT_FALSE(service.userLogIn(user1.getName(), "password"));
    EXPECT_FALSE(service.userLogIn(user1.getName(), ""));
    EXPECT_FALSE(service.userLogIn("userName", "password"));
    EXPECT_FALSE(service.userLogIn("", ""));
    //  Register test
    EXPECT_FALSE(service.userRegister(user3.getName(), user4.getPassword(),
                                      user4.getEmail(), user4.getPhone()));
    EXPECT_TRUE(service.userRegister(user4.getName(), user4.getPassword(),
                                     user4.getEmail(), user4.getPhone()));
    //  Get all users
    auto userList = service.listAllUsers();
    userListTest(list<User>({user1, user2, user3, user4}), userList);
    //  Delete user
    EXPECT_FALSE(service.deleteUser("Trevor Philips", user4.getPassword()));
    EXPECT_FALSE(service.deleteUser(user4.getName(), user3.getPassword()));
    EXPECT_FALSE(service.deleteUser(user4.getName(), ""));
    EXPECT_TRUE(service.deleteUser(user4.getName(), user4.getPassword()));
    userList = service.listAllUsers();
    userListTest(list<User>({user1, user2, user3}), userList);
}

TEST_F(AgendaServiceTest, PureMeetingTest) {
    //  Create meeiting
    //  No such sponsor
    EXPECT_FALSE(service.createMeeting(user4.getName(),
                                       meeting3.getTitle(),
                                       Date::dateToString(meeting3.getStartDate()),
                                       Date::dateToString(meeting3.getEndDate()),
                                       meeting3.getParticipator()));
    //  Some participators are dupulicate
    EXPECT_FALSE(service.createMeeting(meeting3.getSponsor(),
                                       meeting3.getTitle(),
                                       Date::dateToString(meeting3.getEndDate()),
                                       Date::dateToString(meeting3.getStartDate()),
                                       vector<string>({meeting3.getSponsor(), meeting3.getSponsor()})));
    //  Participator list contains sponsor
    EXPECT_FALSE(service.createMeeting(meeting3.getSponsor(),
                                       meeting3.getTitle(),
                                       Date::dateToString(meeting3.getStartDate()),
                                       Date::dateToString(meeting3.getEndDate()),
                                       vector<string>({user1.getName(), meeting3.getSponsor()})));
    //  No such participator(s)
    EXPECT_FALSE(service.createMeeting(meeting3.getSponsor(),
                                       meeting3.getTitle(),
                                       Date::dateToString(meeting3.getStartDate()),
                                       Date::dateToString(meeting3.getEndDate()),
                                       vector<string>({meeting3.getParticipator().front(), "Trevor"})));
    //  Invalid start date string
    EXPECT_FALSE(service.createMeeting(meeting3.getSponsor(),
                                       meeting3.getTitle(),
                                       "2016-7-10/15:00",
                                       Date::dateToString(meeting3.getEndDate()),
                                       meeting3.getParticipator()));
    //  Invalid end date string
    EXPECT_FALSE(service.createMeeting(meeting3.getSponsor(),
                                       meeting3.getTitle(),
                                       Date::dateToString(meeting3.getStartDate()),
                                       "2016-07-11/19:0",
                                       meeting3.getParticipator()));
    //  Start date is later than end date
    EXPECT_FALSE(service.createMeeting(meeting3.getSponsor(),
                                       meeting3.getTitle(),
                                       Date::dateToString(meeting3.getEndDate()),
                                       Date::dateToString(meeting3.getStartDate()),
                                       vector<string>({meeting3.getSponsor()})));
    //  Start date is equal to end date
    EXPECT_FALSE(service.createMeeting(meeting3.getSponsor(),
                                       meeting3.getTitle(),
                                       Date::dateToString(meeting3.getStartDate()),
                                       Date::dateToString(meeting3.getStartDate()),
                                       vector<string>({meeting3.getSponsor()})));

    //  Needed in the following tests
    EXPECT_TRUE(service.userRegister(user4.getName(), user4.getPassword(),
                                     user4.getEmail(), user4.getPhone()));

    for (int i = 3; i <= 6; i++) {
        EXPECT_TRUE(service.createMeeting(meetingSamples[i].getSponsor(),
                                          meetingSamples[i].getTitle(),
                                          Date::dateToString(meetingSamples[i].getStartDate()),
                                          Date::dateToString(meetingSamples[i].getEndDate()),
                                          vector<string>({meetingSamples[i].getSponsor()})));
    }

    //  Sponsor already sponsor a meeting
    //  Sponsor is busy in "2016-07-10/15:00" --- "2016-07-10/18:00"
    //current meeting interval           |-----|
    //sponsor's meeting interval             |-----|
    invalidMeetingIntervalTest("2016-07-10/14:00", "2016-07-10/16:00");

    //current meeting interval               |---|
    //sponsor's meeting interval             |-----|
    invalidMeetingIntervalTest("2016-07-10/15:00", "2016-07-10/16:00");

    //current meeting interval                |---|
    //sponsor's meeting interval             |-----|
    invalidMeetingIntervalTest("2016-07-10/16:00", "2016-07-10/17:00");

    //current meeting interval                 |---|
    //sponsor's meeting interval             |-----|
    invalidMeetingIntervalTest("2016-07-10/16:00", "2016-07-10/18:00");

    //current meeting interval               |-----|
    //sponsor's meeting interval             |-----|
    invalidMeetingIntervalTest("2016-07-10/15:00", "2016-07-10/18:00");

    //current meeting interval                 |-----|
    //sponsor's meeting interval             |-----|
    invalidMeetingIntervalTest("2016-07-10/16:00", "2016-07-10/19:00");

    //current meeting interval              |-------|
    //sponsor's meeting interval             |-----|
    invalidMeetingIntervalTest("2016-07-10/14:00", "2016-07-10/19:00");

    //  Some boundary checks
    //current meeting interval         |-----|
    //sponsor's meeting interval             |-----|
    validMeetingIntervalTest("2016-07-10/14:00", "2016-07-10/15:00");
    EXPECT_TRUE(service.deleteMeeting(meeting3.getSponsor(),
                                      meeting3.getTitle()));
    //current meeting interval                     |-----|
    //sponsor's meeting interval             |-----|
    validMeetingIntervalTest("2016-07-10/18:00", "2016-07-10/19:00");
    EXPECT_TRUE(service.deleteMeeting(meeting3.getSponsor(),
                                      meeting3.getTitle()));


    EXPECT_TRUE(service.createMeeting(meeting3.getSponsor(),
                                      meeting3.getTitle(),
                                      Date::dateToString(meeting3.getStartDate()),
                                      Date::dateToString(meeting3.getEndDate()),
                                      meeting3.getParticipator()));

    EXPECT_TRUE(service.deleteMeeting(meeting3.getSponsor(),
                                      meeting3.getTitle()));
}
