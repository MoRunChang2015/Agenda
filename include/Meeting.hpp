#ifndef MEETING_H
#define MEETING_H

#include "Date.hpp"

class Meeting {
public:
  /**
  * @brief default constructor
  */
  Meeting() = default;

  /**
  *   @brief constructor with argument
  */
  Meeting(std::string t_sponsor, std::string t_participator, Date t_startTime,
          Date t_endTime, std::string t_title);

  /**
  * @brief copy constructor of left value
  */
  Meeting(const Meeting &t_meeting);

  /**
  *   @brief get the meeting's sponsor
  *   @return a string indicate sponsor
  */
  std::string getSponsor(void) const;

  /**
  * @brief set the sponsor of a meeting
  * @param  the new sponsor string
  */
  void setSponsor(const std::string t_sponsor);

  /**
  * @brief  get the participator of a meeting
  * @return return a string indicate participator
  */
  std::string getParticipator(void) const;

  /**
  *   @brief set the new participator of a meeting
  *   @param the new participator string
  */
  void setParticipator(const std::string t_participator);

  /**
  * @brief get the startDate of a meeting
  * @return return a string indicate startDate
  */
  Date getStartDate(void) const;

  /**
  * @brief  set the startDate of a meeting
  * @param  the new startdate of a meeting
  */
  void setStartDate(const Date t_startTime);

  /**
  * @brief get the endDate of a meeting
  * @return a date indicate the endDate
  */
  Date getEndDate(void) const;

  /**
  * @brief  set the endDate of a meeting
  * @param  the new enddate of a meeting
  */
  void setEndDate(const Date t_endTime);

  /**
  * @brief get the title of a meeting
  * @return a date title the endDate
  */
  std::string getTitle(void) const;

  /**
  * @brief  set the title of a meeting
  * @param  the new title of a meeting
  */
  void setTitle(const std::string t_title);
private:
  std::string m_sponsor;
  std::string m_participator;
  Date m_startDate;
  Date m_endDate;
  std::string m_title;
};

#endif
