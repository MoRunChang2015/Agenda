#include "Date.hpp"
#include <sstream>
/**
* @brief default constructor
*/
Date::Date() : m_year(0), m_month(0), m_day(0), m_hour(0), m_minute(0) {}

/**
* @brief constructor with arguments
*/
Date::Date(int t_year, int t_month, int t_day, int t_hour, int t_minute)
    : m_year(t_year),
      m_month(t_month),
      m_day(t_day),
      m_hour(t_hour),
      m_minute(t_minute) {}

/**
* @brief  constructor with a string
*/
Date::Date(std::string dateString) { (*this) = stringToDate(dateString); }
/**
* @brief return the year of a Date
* @return   a integer indicate the year of a date
*/
int Date::getYear(void) const { return m_year; }

/**
* @brief set the year of a date
* @param a integer indicate the new year of a date
*/
void Date::setYear(const int t_year) { m_year = t_year; }

/**
* @brief return the month of a Date
* @return   a integer indicate the month of a date
*/
int Date::getMonth(void) const { return m_month; }

/**
* @brief set the month of a date
* @param a integer indicate the new month of a date
*/
void Date::setMonth(const int t_month) { m_month = t_month; }

/**
* @brief return the day of a Date
* @return   a integer indicate the day of a date
*/
int Date::getDay(void) const { return m_day; }

/**
* @brief set the day of a date
* @param a integer indicate the new day of a date
*/
void Date::setDay(const int t_day) { m_day = t_day; }

/**
* @brief return the hour of a Date
* @return   a integer indicate the hour of a date
*/
int Date::getHour(void) const { return m_hour; }

/**
* @brief set the hour of a date
* @param a integer indicate the new hour of a date
*/
void Date::setHour(const int t_hour) { m_hour = t_hour; }

/**
* @brief return the minute of a Date
* @return   a integer indicate the minute of a date
*/
int Date::getMinute(void) const { return m_minute; }

/**
* @brief set the minute of a date
* @param a integer indicate the new minute of a date
*/
void Date::setMinute(const int t_minute) { m_minute = t_minute; }

/**
*   @brief check whether the date is valid or not
*   @return the bool indicate valid or not
*/
bool Date::isValid(const Date t_date) {
    int current_year = t_date.getYear();
    int current_month = t_date.getMonth();
    int current_day = t_date.getDay();
    if (current_year < 1000 || current_year > 9999 || current_month < 1 ||
        current_month > 12 || current_day < 1 || t_date.getHour() < 0 ||
        t_date.getHour() >= 24 || t_date.getMinute() < 0 ||
        t_date.getMinute() >= 60) {
        return false;
    }

    if (current_month == 1 || current_month == 3 || current_month == 5 ||
        current_month == 7 || current_month == 8 || current_month == 10 ||
        current_month == 12) {
        if (current_day > 31) {
            return false;
        }
    } else if (current_month == 4 || current_month == 6 || current_month == 9 ||
               current_month == 11) {
        if (current_day > 30) {
            return false;
        }
    } else {
        //若年份为闰年，则2月29天
        if ((current_year % 4 == 0 && current_year % 100 != 0) ||
            (current_year % 400 == 0)) {
            if (current_day > 29) {
                return false;
            }
        } else {
            if (current_day > 28) {
                return false;
            }
        }
    }
    return true;
}

/**
* @brief convert string to int
*/
int string2Int(std::string s) {
    int result;
    std::stringstream ss;
    ss << s;
    ss >> result;
    return result;
}

/**
* @brief convert a string to date, if the format is not correct return
* 0000-00-00/00:00
* @return a date
*/
Date Date::stringToDate(const std::string t_dateString) {
    Date resultDate;
    //检查字符串的格式是否正确．
    if (t_dateString.length() != 16) {
        return resultDate;
    }
    for (int count = 0; count < t_dateString.length(); count++) {
        switch (count) {
            case 4:
                if (t_dateString[4] != '-') {
                    return resultDate;
                }
                break;
            case 7:
                if (t_dateString[7] != '-') {
                    return resultDate;
                }
                break;
            case 10:
                if (t_dateString[10] != '/') {
                    return resultDate;
                }
                break;
            case 13:
                if (t_dateString[13] != ':') {
                    return resultDate;
                }
                break;
            default:
                if (t_dateString[count] < '0' || t_dateString[count] > '9') {
                    return resultDate;
                }
        }
    }

    //若字符串格式没问题
    resultDate.setYear(string2Int(t_dateString.substr(0, 4)));
    resultDate.setMonth(string2Int(t_dateString.substr(5, 2)));
    resultDate.setDay(string2Int(t_dateString.substr(8, 2)));
    resultDate.setHour(string2Int(t_dateString.substr(11, 2)));
    resultDate.setMinute(string2Int(t_dateString.substr(14, 2)));
    return resultDate;
}

/**
*   @brief convert the date to string, if result length is 1, add padding 0
*/
std::string int2String(int a) {
    std::string result;
    std::stringstream ss;
    ss << a;
    ss >> result;
    if (result.length() == 1) {
        result = "0" + result;
    }
    return result;
}

/**
* @brief convert a date to string, if the format is not correct return
* 0000-00-00/00:00
*/
std::string Date::dateToString(Date t_date) {
    std::string dateString = "";
    //若date的格式错误，则返回初始时间串0000-00-00/00:00
    if (!isValid(t_date)) {
        dateString = "0000-00-00/00:00";
        return dateString;
    }
    dateString =
        int2String(t_date.getYear()) + "-" + int2String(t_date.getMonth()) +
        "-" + int2String(t_date.getDay()) + "/" + int2String(t_date.getHour()) +
        ":" + int2String(t_date.getMinute());
    return dateString;
}

/**
*  @brief overload the assign operator
*/
Date &Date::operator=(const Date &t_date) {
    this->setYear(t_date.getYear());
    this->setMonth(t_date.getMonth());
    this->setDay(t_date.getDay());
    this->setHour(t_date.getHour());
    this->setMinute(t_date.getMinute());
    return (*this);
}

/**
* @brief check whether the CurrentDate is equal to the t_date
*/
bool Date::operator==(const Date &t_date) const {
    return (t_date.getYear() == this->m_year &&
            t_date.getMonth() == this->m_month &&
            t_date.getDay() == this->m_day &&
            t_date.getHour() == this->m_hour &&
            t_date.getMinute() == this->m_minute);
}

/**
* @brief check whether the CurrentDate is  greater than the t_date
*/
bool Date::operator>(const Date &t_date) const {
    // if (m_year > t_date.getYear()) return true;
    // if (m_year < t_date.getYear()) return false;
    // if (m_month > t_date.getMonth()) return true;
    // if (m_month < t_date.getMonth()) return false;
    // if (m_day > t_date.getDay()) return true;
    // if (m_day < t_date.getDay()) return false;
    // if (m_hour > t_date.getHour()) return true;
    // if (m_hour < t_date.getHour()) return false;
    // if (m_minute > t_date.getMinute()) return true;
    // if (m_minute < t_date.getMinute()) return false;
    // return false;
    return dateToString(*this) > dateToString(t_date);
}

/**
* @brief check whether the CurrentDate is  less than the t_date
*/
bool Date::operator<(const Date &t_date) const {
    return !((*this) > t_date || (*this) == t_date);
}

/**
* @brief check whether the CurrentDate is  greater or equal than the
* t_date
*/
bool Date::operator>=(const Date &t_date) const {
    return ((*this) == t_date || (*this) > t_date);
}

/**
* @brief check whether the CurrentDate is  less than or equal to the
* t_date
*/
bool Date::operator<=(const Date &t_date) const {
  return ((*this) < t_date || (*this) == t_date);
}
