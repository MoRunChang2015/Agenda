#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <list>
#include "Meeting.hpp"
#include "User.hpp"

using std::string;
using std::vector;
using std::list;

string sponsor("Sponsor");
vector<string> participator = {"Par_A", "Par_B"};
Date startDate("2016-7-7/15:30"), endDate("2016-7-8/00:01");
string title("Title");
Meeting meeting;


bool findParticipator(vector<string> &list, const string &userName) {
    for (auto it = list.begin(); it != list.end(); ++it) {
        if (*it == userName) {
            list.erase(it);
            return true;
        }
    }
    return false;
}

/*
 *  Test basic Set and Get functions
 */
TEST(MeetingTest, SetAndGetFunctions) {
    // Set functions
    meeting.setSponsor(sponsor);
    meeting.setParticipator(participator);
    meeting.setStartDate(startDate);
    meeting.setEndDate(endDate);
    meeting.setTitle(title);
    //  Get functions
    EXPECT_STREQ(sponsor.c_str(), meeting.getSponsor().c_str());
    vector<string> parVec = meeting.getParticipator();
    EXPECT_EQ(participator.size(), parVec.size());
    for (auto it = participator.begin(); it != participator.end(); ++it) {
        //  The order of stored participators is not concerned
        EXPECT_TRUE(findParticipator(parVec, *it));
    }

    EXPECT_STREQ(Date::dateToString(startDate).c_str(),
                 Date::dateToString(meeting.getStartDate()).c_str());
    EXPECT_STREQ(Date::dateToString(endDate).c_str(),
                 Date::dateToString(meeting.getEndDate()).c_str());
    EXPECT_STREQ(title.c_str(), meeting.getTitle().c_str());
}

/*
 *  Test constructors
 */
TEST(MeetingTest, Constructors) {
    //  Constructor with arguments
    Meeting meetingA(sponsor, participator, startDate, endDate, title);
    EXPECT_STREQ(sponsor.c_str(), meetingA.getSponsor().c_str());
    vector<string> parVec = meetingA.getParticipator();
    EXPECT_EQ(participator.size(), parVec.size());
    for (auto it = participator.begin(); it != participator.end(); ++it) {
        EXPECT_TRUE(findParticipator(parVec, *it));
    }
    EXPECT_STREQ(Date::dateToString(startDate).c_str(),
                 Date::dateToString(meetingA.getStartDate()).c_str());
    EXPECT_STREQ(Date::dateToString(endDate).c_str(),
                 Date::dateToString(meetingA.getEndDate()).c_str());
    EXPECT_STREQ(title.c_str(), meetingA.getTitle().c_str());
    //  Copy constructor
    Meeting meetingB(meeting);
    EXPECT_STREQ(sponsor.c_str(), meetingB.getSponsor().c_str());
    parVec = meetingB.getParticipator();
    EXPECT_EQ(participator.size(), parVec.size());
    for (auto it = participator.begin(); it != participator.end(); ++it) {
        EXPECT_TRUE(findParticipator(parVec, *it));
    }
    EXPECT_STREQ(Date::dateToString(startDate).c_str(),
                 Date::dateToString(meetingB.getStartDate()).c_str());
    EXPECT_STREQ(Date::dateToString(endDate).c_str(),
                 Date::dateToString(meetingB.getEndDate()).c_str());
    EXPECT_STREQ(title.c_str(), meetingB.getTitle().c_str());
}

/*
 *  Test if a user participates in the meeting
 */
TEST(MeetingTest, IsParticipatorCheck) {
    EXPECT_TRUE(meeting.isParticipator("Par_A"));
    EXPECT_TRUE(meeting.isParticipator("Par_B"));
    EXPECT_FALSE(meeting.isParticipator("Par_C"));
}
