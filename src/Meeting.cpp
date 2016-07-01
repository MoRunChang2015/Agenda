#include "Meeting.hpp"
#include "Date.hpp"
#include "User.hpp"
/**
*   @brief constructor with argument
*/
Meeting::Meeting(std::string t_sponsor, std::string t_participator,
                 Date t_startDate, Date t_endDate, std::string t_title)
    : m_sponsor(t_sponsor), m_participator(t_participator),
      m_startDate(t_startDate), m_endDate(t_endDate), m_title(t_title) {}

/**
* @brief copy constructor of left value
*/
Meeting::Meeting(const Meeting &t_meeting)
    : m_sponsor(t_meeting.getSponsor()),
      m_participator(t_meeting.getParticipator()),
      m_startDate(t_meeting.getStartDate()), m_endDate(t_meeting.getEndDate()),
      m_title(t_meeting.getTitle()) {}

/**
*   @brief get the meeting's sponsor
*   @return a string indicate sponsor
*/
std::string Meeting::getSponsor(void) const { return m_sponsor; }

/**
* @brief set the sponsor of a meeting
* @param  the new sponsor string
*/
void Meeting::setSponsor(const std::string t_sponsor) { m_sponsor = t_sponsor; }

/**
* @brief  get the participator of a meeting
* @return return a string indicate participator
*/
std::string Meeting::getParticipator(void) const { return m_participator; }

/**
*   @brief set the new participator of a meeting
*   @param the new participator string
*/
void Meeting::setParticipator(const std::string t_participator) {
  m_participator = t_participator;
}

/**
* @brief get the startDate of a meeting
* @return return a string indicate startDate
*/
Date Meeting::getStartDate(void) const { return m_startDate; }

/**
* @brief  set the startDate of a meeting
* @param  the new startdate of a meeting
*/
void Meeting::setStartDate(const Date t_startTime) {
  m_startDate = t_startTime;
}

/**
* @brief get the endDate of a meeting
* @return a date indicate the endDate
*/
Date Meeting::getEndDate(void) const { return m_endDate; }

/**
* @brief  set the endDate of a meeting
* @param  the new enddate of a meeting
*/
void Meeting::setEndDate(const Date t_endTime) { m_endDate = t_endTime; }

/**
* @brief get the title of a meeting
* @return a date title the endDate
*/
std::string Meeting::getTitle(void) const { return m_title; }

/**
* @brief  set the title of a meeting
* @param  the new title of a meeting
*/
void Meeting::setTitle(const std::string t_title) { m_title = t_title; }
