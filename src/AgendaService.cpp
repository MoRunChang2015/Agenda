#include "../include/AgendaService.hpp"
#include "../include/User.hpp"
#include "../include/Meeting.hpp"
#include "../include/Date.hpp"
#include <iostream>
#include <list>
#include <string>


AgendaService :: AgendaService() {
    startAgenda();
}


AgendaService :: ~AgendaService() {
    quitAgenda();
}


void AgendaService :: startAgenda(void) {
    m_storage = Storage :: getInstance();
}

void AgendaService :: quitAgenda(void) {

}

bool  AgendaService :: userLogIn(const std::string userName, const std::string password) {
    std :: list<User> l;
    User temp(userName , password , "" , "");
    l = m_storage -> queryUser([&temp](const User& a) {
        if (a.getName() == temp.getName())
            return true;
        else
            return false;
    });
    if (l.empty())
        return false;
    if (password == l.begin() -> getPassword())
        return true;
    else
        return false;
}

bool  AgendaService :: userRegister(const std::string userName, const std::string password,
                    const std::string email, const std::string phone) {
    std :: list<User> l;
    User temp(userName , password , email , phone);
    l = m_storage -> queryUser([&temp](const User& a) {
        if (a.getName() == temp.getName())
            return true;
        else
            return false;
    });
    if (!l.empty())
        return false;
    m_storage -> createUser(temp);
    return true;
}
bool AgendaService :: deleteUser(const std::string userName, const std::string password) {
    std :: list<User> l;
    l = m_storage -> queryUser([ &userName ](const User& a) {
        if (a.getName() == userName)
            return true;
        else
            return false;
    });
    if (l.empty())
        return false;
    if (password != l.begin() -> getPassword())
        return false;
    m_storage -> deleteUser([&userName](const User& a) {
        if (a.getName() == userName)
            return true;
        else
            return false;
    });
    m_storage -> deleteMeeting([&userName](const Meeting& a) {
        if (a.getSponsor() == userName ||
            a.getParticipator() == userName)
            return true;
        else
            return false;
    });
    return true;
}
    // a user can only delete itself
std::list<User> AgendaService :: listAllUsers(void) const {
    std :: list<User> l;
    l = m_storage -> queryUser([](const User& a) {
        return true;
    });
    return l;
}

bool AgendaService :: createMeeting(const std::string userName, const std::string title,
                   const std::string participator,
                   const std::string startDate, const std::string endDate) {
    if (userName == participator)
       return false;
    Date sTime;
    Date eTime;
    sTime = Date :: stringToDate(startDate);
    eTime = Date :: stringToDate(endDate);
    if (! Date :: isValid(sTime))
        return false;
    if (! Date :: isValid(eTime))
        return false;
    if (sTime >= eTime)
        return false;
    std :: list<User> lu;
    lu = m_storage -> queryUser([&userName] (const User& a) {
        if (a.getName() == userName) {
            return true;
        } else {
            return false;
        }
    });
    if (lu.empty())
        return false;
    lu = m_storage -> queryUser([&participator] (const User& a) {
        if (a.getName() == participator) {
            return true;
        } else {
            return false;
        }
    });
    if (lu.empty())
        return false;
    std :: list<Meeting> l;
    l = m_storage -> queryMeeting([&participator , &sTime , &eTime]
                                  (const Meeting& a) {
        if (a.getSponsor() == participator ||
             a.getParticipator() == participator) {
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
    if (!l.empty())
        return false;
    l = m_storage -> queryMeeting([&userName , &sTime , &eTime]
                                  (const Meeting& a) {
        if (a.getSponsor() == userName ||
             a.getParticipator() == userName) {
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
    if (!l.empty())
        return false;
    l = m_storage -> queryMeeting([&title] (const Meeting& a) {
        if (a.getTitle() == title)
            return true;
        else
            return false;
    });
    if (!l.empty())
         return false;
    Meeting temp(userName , participator , sTime , eTime , title);
    m_storage -> createMeeting(temp);
    return true;
}

std::list<Meeting> AgendaService :: meetingQuery(const std::string userName,
                                                 const std::string title) const {
    std :: list<Meeting> l;
    l = m_storage -> queryMeeting([&userName , &title](const Meeting& a) {
        if (a.getSponsor() == userName || a.getParticipator() == userName) {
            if (a.getTitle() == title) {
                return true;
            } else {
                return false;
            }
        }  else {
            return false;
        }
    });
    return l;    
}

std::list<Meeting> AgendaService :: meetingQuery(const std::string userName, 
                    const std::string startDate , const std::string endDate) const {
    std :: list<Meeting> l;
    Date sTime , eTime;
    sTime = Date :: stringToDate(startDate);
    eTime = Date :: stringToDate(endDate);
    if (!Date :: isValid(sTime))
        return l;
    if (!Date :: isValid(eTime))
        return l;
    l = m_storage -> queryMeeting([&userName , &sTime , &eTime]
                                             (const Meeting& a) {
        if (a.getSponsor() == userName ||
            a.getParticipator() == userName) {
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

std::list<Meeting> AgendaService :: listAllMeetings(const std::string userName) const {
    std :: list<Meeting> l;
    l = m_storage -> queryMeeting([&userName](const Meeting& a) {
        if (a.getSponsor() == userName ||
            a.getParticipator() == userName) {
            return true;
        } else {
            return false;
        }
    });
    return l;
}

std::list<Meeting> AgendaService :: listAllSponsorMeetings(const std::string userName) const {
    std :: list<Meeting> l;
    l = m_storage -> queryMeeting([&userName](const Meeting& a) {
        if (a.getSponsor() == userName) {
            return true;
        } else {
            return false;
        }
    });
    return l;
}

std::list<Meeting> AgendaService :: listAllParticipateMeetings(const std::string userName) const {
    std :: list<Meeting> l;
    l = m_storage -> queryMeeting([&userName](const Meeting& a) {
        if (a.getParticipator() == userName) {
            return true;
        } else {
            return false;
        }
    });
    return l;
}

bool AgendaService :: deleteMeeting(const std::string userName, const std::string title) {
    int ans = 0;
    ans = m_storage -> deleteMeeting([&userName , &title](const Meeting& a) {
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

bool AgendaService :: deleteAllMeetings(const std::string userName) {
    int ans = 0;
    ans = m_storage -> deleteMeeting([&userName](const Meeting& a) {
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

