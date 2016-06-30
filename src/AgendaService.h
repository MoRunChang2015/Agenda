#ifndef AGENDASERVICE_H
#define AGENDASERVICE_H

#include "Storage.h"
#include <list>
#include <string>

class AgendaService {
public:
  AgendaService();
  ~AgendaService();
  bool userLogIn(const std::string userName, const std::string password);
  bool userRegister(const std::string userName, const std::string password,
                    const std::string email, const std::string phone);
  bool deleteUser(const std::string userName, const std::string password);
  // a user can only delete itself
  std::list<User> listAllUsers(void) const;

  bool createMeeting(const std::string userName, const std::string title,
                     const std::string participator,
                     const std::string startDate, const std::string endDate);
  std::list<Meeting> meetingQuery(const std::string userName,
                                  const std::string title) const;
  std::list<Meeting> meetingQuery(const std::string userName,
                                  const std::string startDate,
                                  const std::string endDate) const;
  std::list<Meeting> listAllMeetings(const std::string userName) const;
  std::list<Meeting> listAllSponsorMeetings(const std::string userName) const;
  std::list<Meeting>
  listAllParticipateMeetings(const std::string userName) const;
  bool deleteMeeting(const std::string userName, const std::string title);
  bool deleteAllMeetings(const std::string userName);

  void startAgenda(void);
  void quitAgenda(void);

private:
  std::unique_ptr<Storage> m_storage;
};

#endif
