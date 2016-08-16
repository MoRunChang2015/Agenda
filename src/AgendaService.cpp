#include "AgendaService.hpp"
#include "User.hpp"
#include "Meeting.hpp"
#include "Date.hpp"
#include <list>
#include <string>

/**
 * constructor
 */
AgendaService::AgendaService() { startAgenda(); }

/**
 * destructor
 */
AgendaService::~AgendaService() { quitAgenda(); }

/**
 * start Agenda service and connect to storage
 */
void AgendaService::startAgenda(void) { m_storage = Storage::getInstance(); }

/**
 * quit Agenda service
 */
void AgendaService::quitAgenda(void) {}

/**
 * check if the username match password
 * @param userName the username want to login
 * @param password the password user enter
 * @return if success, true will be returned
 */
bool AgendaService::userLogIn(const std::string userName,
                              const std::string password) {
    std::list<User> l;
    User temp(userName, password, "", "");
    l = m_storage->queryUser([&temp](const User& a) {
        if (a.getName() == temp.getName())
            return true;
        else
            return false;
    });
    if (l.empty()) return false;
    if (password == l.begin()->getPassword())
        return true;
    else
        return false;
}

/**
 * regist a user
 * @param userName new user's username
 * @param password new user's password
 * @param email new user's email
 * @param phone new user's phone
 * @return if success, true will be returned
 */
bool AgendaService::userRegister(const std::string userName,
                                 const std::string password,
                                 const std::string email,
                                 const std::string phone) {
    std::list<User> l;
    User temp(userName, password, email, phone);
    l = m_storage->queryUser([&temp](const User& a) {
        if (a.getName() == temp.getName())
            return true;
        else
            return false;
    });
    if (!l.empty()) return false;
    m_storage->createUser(temp);
    return true;
}

/**
 * delete a user
 * @param userName user's username
 * @param password user's password
 * @return if success, true will be returned
 */
bool AgendaService::deleteUser(const std::string userName,
                               const std::string password) {
    std::list<User> l;
    l = m_storage->queryUser([&userName](const User& a) {
        if (a.getName() == userName)
            return true;
        else
            return false;
    });
    if (l.empty()) return false;
    if (password != l.begin()->getPassword()) return false;
    m_storage->deleteUser([&userName](const User& a) {
        if (a.getName() == userName)
            return true;
        else
            return false;
    });
    m_storage->deleteMeeting([&userName](const Meeting& a) {
        if (a.getSponsor() == userName || a.isParticipator(userName))
            return true;
        else
            return false;
    });
    return true;
}

/**
 * list all users from storage
 * @return a user list result
 */
std::list<User> AgendaService::listAllUsers(void) const {
    std::list<User> l;
    l = m_storage->queryUser([](const User& a) { return true; });
    return l;
}

/**
 * create a meeting
 * @param userName the sponsor's userName
 * @param title the meeting's title
 * @param participator the meeting's participator
 * @param startData the meeting's start date
 * @param endData the meeting's end date
 * @return if success, true will be returned
 */
bool AgendaService::createMeeting(const std::string userName,
                                  const std::string title,
                                  const std::string startDate,
                                  const std::string endDate,
                                  const std::vector<std::string> participator) {
    for (auto it = participator.begin(); it != participator.end(); it++) {
        for (auto itj = participator.begin(); itj != it; itj++) {
            if ((*itj) == (*it)) return false;
        }
    }
    Date sTime;
    Date eTime;
    sTime = Date::stringToDate(startDate);
    eTime = Date::stringToDate(endDate);
    if (!Date::isValid(sTime)) return false;
    if (!Date::isValid(eTime)) return false;
    if (sTime >= eTime) return false;
    std::list<User> lu;
    std::list<Meeting> l;
    for (auto it = participator.begin(); it != participator.end(); it++) {
        if (*it == userName) return false;
        std::string puserName = *it;
        lu = m_storage->queryUser([&puserName](const User& a) {
            if (a.getName() == puserName) {
                return true;
            } else {
                return false;
            }
        });
        if (lu.empty()) return false;
        l = m_storage->queryMeeting([&puserName, &sTime, &eTime](
            const Meeting& a) {
            if (a.getSponsor() == puserName || a.isParticipator(puserName)) {
                if (a.getStartDate() <= sTime && a.getEndDate() > sTime)
                    return true;
                if (a.getStartDate() < eTime && a.getEndDate() >= eTime)
                    return true;
                if (a.getStartDate() >= sTime && a.getEndDate() <= eTime)
                    return true;
                return false;
            } else {
                return false;
            }
        });
        if (!l.empty()) return false;
    }
    lu = m_storage->queryUser([&userName](const User& a) {
        if (a.getName() == userName) {
            return true;
        } else {
            return false;
        }
    });
    if (lu.empty()) return false;
    l = m_storage->queryMeeting([&userName, &sTime, &eTime](const Meeting& a) {
        if (a.getSponsor() == userName || a.isParticipator(userName)) {
            if (a.getStartDate() <= sTime && a.getEndDate() > sTime)
                return true;
            if (a.getStartDate() < eTime && a.getEndDate() >= eTime)
                return true;
            if (a.getStartDate() >= sTime && a.getEndDate() <= eTime)
                return true;
            return false;
        } else {
            return false;
        }
    });
    if (!l.empty()) return false;
    l = m_storage->queryMeeting([&title](const Meeting& a) {
        if (a.getTitle() == title)
            return true;
        else
            return false;
    });
    if (!l.empty()) return false;
    Meeting temp(userName, participator, sTime, eTime, title);
    m_storage->createMeeting(temp);
    return true;
}

/**
 * search a meeting by username and title
 * @param uesrName the sponsor's userName
 * @param title the meeting's title
 * @return a meeting list result
 */
std::list<Meeting> AgendaService::meetingQuery(const std::string userName,
                                               const std::string title) const {
    std::list<Meeting> l;
    l = m_storage->queryMeeting([&userName, &title](const Meeting& a) {
        if (a.getSponsor() == userName || a.isParticipator(userName)) {
            if (a.getTitle() == title) {
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    });
    return l;
}

/**
 * search a meeting by username, time interval
 * @param uesrName the sponsor's userName
 * @param startDate time interval's start date
 * @param endDate time interval's end date
 * @return a meeting list result
 */
std::list<Meeting> AgendaService::meetingQuery(
    const std::string userName, const std::string startDate,
    const std::string endDate) const {
    std::list<Meeting> l;
    Date sTime, eTime;
    sTime = Date::stringToDate(startDate);
    eTime = Date::stringToDate(endDate);
    if (!Date::isValid(sTime)) return l;
    if (!Date::isValid(eTime)) return l;
    if (sTime > eTime) return l;
    l = m_storage->queryMeeting([&userName, &sTime, &eTime](const Meeting& a) {
        if (a.getSponsor() == userName || a.isParticipator(userName)) {
            if (a.getStartDate() <= sTime && a.getEndDate() >= sTime)
                return true;
            if (a.getStartDate() <= eTime && a.getEndDate() >= eTime)
                return true;
            if (a.getStartDate() >= sTime && a.getEndDate() <= eTime)
                return true;
            return false;
        } else {
            return false;
        }
    });
    return l;
}

/**
 * list all meetings the user take part in
 * @param userName user's username
 * @return a meeting list result
 */

std::list<Meeting> AgendaService::listAllMeetings(
    const std::string userName) const {
    std::list<Meeting> l;
    l = m_storage->queryMeeting([&userName](const Meeting& a) {
        if (a.getSponsor() == userName || a.isParticipator(userName)) {
            return true;
        } else {
            return false;
        }
    });
    return l;
}

/**
 * list all meetings the user sponsor
 * @param userName user's username
 * @return a meeting list result
 */
std::list<Meeting> AgendaService::listAllSponsorMeetings(
    const std::string userName) const {
    std::list<Meeting> l;
    l = m_storage->queryMeeting([&userName](const Meeting& a) {
        if (a.getSponsor() == userName) {
            return true;
        } else {
            return false;
        }
    });
    return l;
}

/**
 * list all meetings the user take part in and sponsor by other
 * @param userName user's username
 * @return a meeting list result
 */
std::list<Meeting> AgendaService::listAllParticipateMeetings(
    const std::string userName) const {
    std::list<Meeting> l;
    l = m_storage->queryMeeting([&userName](const Meeting& a) {
        if (a.isParticipator(userName)) {
            return true;
        } else {
            return false;
        }
    });
    return l;
}

/**
 * delete a meeting by title and its sponsor
 * @param userName sponsor's username
 * @param title meeting's title
 * @return if delete this meeting success
 */
bool AgendaService::deleteMeeting(const std::string userName,
                                  const std::string title) {
    int ans = 0;
    ans = m_storage->deleteMeeting([&userName, &title](const Meeting& a) {
        if (a.getSponsor() == userName && a.getTitle() == title) {
            return true;
        } else {
            return false;
        }
    });
    if (ans > 0)
        return true;
    else
        return false;
}

/**
 * delete all meetings by sponsor
 * @param userName sponsor's username
 * @return if delete all meetings success
 */
bool AgendaService::deleteAllMeetings(const std::string userName) {
    int ans = 0;
    ans = m_storage->deleteMeeting([&userName](const Meeting& a) {
        if (a.getSponsor() == userName) {
            return true;
        } else {
            return false;
        }
    });
    if (ans > 0)
        return true;
    else
        return false;
}
