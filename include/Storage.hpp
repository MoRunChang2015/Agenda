#ifndef AGENDA_STORAGE_H
#define AGENDA_STORAGE_H

#include "Meeting.hpp"
#include "User.hpp"
#include <functional>
#include <list>
#include <memory>
#include <string>

class Storage {
private:
  /**
  *   default constructor
  */
  Storage();

  /**
  *   disallow the copy constructor and assign operator
  */
  Storage(const Storage &) = delete;
  void operator=(const Storage &) = delete;

  // File IO
  bool readFromFile(const char *fpath);
  bool writeToFile(const char *fpath);

public:
  // singleton
  static std::unique_ptr<Storage> getInstance(void);
  ~Storage();
  // CRUD for User & Meeting
  // using C++11 Function Template and Lambda Expressions
  void createUser(const User &);
  std::list<User> queryUser(std::function<bool(const User &)> filter);
  // return found users
  int updateUser(std::function<bool(const User &)> filter,
                 std::function<void(User &)> switcher);
  // return the number of updated users
  int deleteUser(std::function<bool(const User &)> filter);
  // return the number of deleted users
  void createMeeting(const Meeting &);
  std::list<Meeting> queryMeeting(std::function<bool(const Meeting &)> filter);
  // return found meetings
  int updateMeeting(std::function<bool(const Meeting &)> filter,
                    std::function<void(Meeting &)> switcher);
  // return the number of updated meetings
  int deleteMeeting(std::function<bool(const Meeting &)> filter);
  // return the number of deleted meetings
  // File IO
  bool sync(void);

private:
  static std::unique_ptr<Storage> m_instance;
  std::list<User> m_userList;
  std::list<Meeting> m_meetingList;
};

#endif
