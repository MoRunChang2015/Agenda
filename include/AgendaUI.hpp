#ifndef AGENDAUI_H
#define AGENDAUI_H

#include "AgendaService.h"
#include <iostream>
#include <string>

class AgendaUI {
public:
  AgendaUI();
  void OperationLoop(void);

private:
  // task functions
  void startAgenda(void);
  std::string getOperation();
  bool executeOperation(std::string t_operation);
  void userLogIn(void);
  void userRegister(void);
  void quitAgenda(void);
  void userLogOut(void);
  void deleteUser(void);
  void listAllUsers(void);
  void createMeeting(void);
  void listAllMeetings(void);
  void listAllSponsorMeetings(void);
  void listAllParticipateMeetings(void);
  void queryMeetingByTitle(void);
  void queryMeetingByTimeInterval(void);
  void deleteMeetingByTitle(void);
  void deleteAllMeetings(void);
  void printMeetings(std::list<Meeting> t_meetings);
  // dates
  std::string m_userName;
  std::string m_userPassword;
  AgendaService m_agendaService;
};

#endif
