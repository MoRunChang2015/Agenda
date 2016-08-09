#include <gtest/gtest.h>
#include "utility.h"

bool utility::judgeUserEqual(const User &user1, const User &user2) {
    if (user1.getName() == user2.getName() &&
        user1.getPassword() == user2.getPassword() &&
        user1.getEmail() == user2.getEmail() &&
        user1.getPhone() == user2.getPhone()) {
        return true;
    }
    return false;
}

bool utility::judgeMeetingEqual(const Meeting &meeting1, const Meeting &meeting2) {
    if (meeting1.getSponsor() == meeting2.getSponsor() &&
        meeting1.getStartDate() == meeting2.getStartDate() &&
        meeting1.getEndDate() == meeting2.getEndDate() &&
        meeting1.getTitle() == meeting2.getTitle()) {
        auto meetingList1 = meeting1.getParticipator();
        auto meetingList2 = meeting2.getParticipator();
        if (meetingList1.size() != meetingList2.size()) return false;
        for (auto &user1 : meetingList1) {
            bool currentResult = false;
            for (auto &user2 : meetingList2) {
                if (user1 == user2) {
                    currentResult = true;
                    break;
                }
            }
            if (currentResult == false) {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool utility::findUser(const list<User> &list, const User &user) {
    for (auto &_user : list) {
        if (judgeUserEqual(_user, user)) {
            return true;
        }
    }
    return false;
}

bool utility::findMeeting(const list<Meeting> &list, const Meeting &meeting) {
    for (auto &_meeting : list) {
        if (judgeMeetingEqual(_meeting, meeting)) {
            return true;
        }
    }
    return false;
}

bool utility::testUserList(const list<User> &expectList, const list<User> &actualList) {
    if (expectList.size() != actualList.size()) {
        return false;
    }
    for (auto &user : expectList) {
        bool flag = findUser(actualList, user);
        EXPECT_TRUE(flag) << "User: " << user.getName() << " is not found";
        if (!flag) return false;
    }
    return true;
}
bool utility::testMeetingList(const list<Meeting> &expectList,
                              const list<Meeting> &actualList) {
    if (expectList.size() != actualList.size()) {
        return false;
    }
    for (auto &meeting : expectList) {
        bool flag = findMeeting(actualList, meeting);
        EXPECT_TRUE(flag) << "Meeting: " <<  meeting.getTitle()
                          <<" sponsored by " << meeting.getSponsor()
                          << " is not found";
        if (!flag) return false;
    }
    return true;
}

void utility::recFiles() {
    std::fstream userStandardfs(stdUserPath, std::ios::in);
    std::fstream userTestfs(userPath, std::ios::out|std::ios::trunc);
    string record;
    while (std::getline(userStandardfs, record)) {
        userTestfs << record << "\n";
    }

    std::fstream meetingStandardfs(stdMeetingPath, std::ios::in);
    std::fstream meetingTestfs(meetingPath, std::ios::out|std::ios::trunc);
    while (std::getline(meetingStandardfs, record)) {
        meetingTestfs << record << "\n";
    }
    userStandardfs.close();
    userTestfs.close();
    meetingStandardfs.close();
    meetingTestfs.close();
}
