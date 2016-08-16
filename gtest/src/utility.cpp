#include <gtest/gtest.h>
#include "utility.h"

using namespace std;

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
    vector<string> users{R"("Lara Croft","TombRaidar","lara@email.com","13800000000")",
            R"("Geralt of Rivia","TheWithcer","geralt@email.com","13700000000")",
            R"("Naked Snake","MetalGearSolid","snake@email.com","13600000000")"};
    vector<string> meetings{R"("Naked Snake","Lara Croft","2016-07-08/11:10","2016-07-08/12:05","I wanna Quite")",
            R"("Geralt of Rivia","Naked Snake&Lara Croft","2016-07-10/15:00","2016-07-10/18:00","Want a few rounds of Gwent?")"};
    fstream f(userPath, fstream::out|fstream::trunc);
    for (string &record: users) {
        f << record << endl;
    }
    f.close();
    f.clear();
    f.open(meetingPath, fstream::out|fstream::trunc);
    for (string &record: meetings) {
        f << record << endl;
    }
}
