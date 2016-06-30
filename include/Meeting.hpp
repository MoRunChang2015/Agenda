#ifndef MEETING_H
#define MEETING_H

#include "Date.hpp"

class Meeting {
public:
  Meeting();
  Meeting(std::string t_sponsor, std::string t_participator, Date t_startTime,
          Date t_endTime, std::string t_title);
  Meeting(const Meeting &&t_meeting);
  Meeting(const Meeting & t_meeting);
  std::string getSponsor(void) const;
  void setSponsor(const std::string t_sponsor);
  std::string getParticipator(void) const;
  void setParticipator(const std::string t_participator);
  Date getStartDate(void) const;
  void setStartDate(const Date t_startTime);
  Date getEndDate(void) const;
  void setEndDate(const Date t_endTime);
  std::string getTitle(void) const;
  void setTitle(const std::string t_title);
private:
  std::string m_sponsor;
  std::string m_participator;
  Date m_startDate;
  Date m_endDate;
  std::string m_title;
};

#endif
