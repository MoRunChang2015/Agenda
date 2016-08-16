#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <list>
#include <fstream>
#include "Date.hpp"
#include "Meeting.hpp"
#include "User.hpp"

using std::list;
using std::string;

namespace utility {
    bool judgeUserEqual(const User &user1, const User &user2);
    bool judgeMeetingEqual(const Meeting &meeting1, const Meeting &meeting2);
    bool findUser(const list<User> &list, const User &user);
    bool findMeeting(const list<Meeting> &list, const Meeting &meeting);
    //  We do not care about the order of the users(meetings)
    //  Just to verify that both lists contain the same content
    bool testUserList(const list<User> &expectList, const list<User> &actualList);
    bool testMeetingList(const list<Meeting> &expectList,
                         const list<Meeting> &actualList);
    void recFiles();

    //  Path to csv
    const char *const userPath = "tmp/users.csv";
    const char *const meetingPath = "tmp/meetings.csv";
}

#endif /* UTILITY_H */
