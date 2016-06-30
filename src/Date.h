#ifndef DATE_H
#define DATE_H

#include <initializer_list>
#include <string>

class Date {
public:
  Date();
  Date(int t_year, int t_month, int t_day, int t_hour, int t_minute);
  int getYear(void) const;
  void setYear(const int t_year);
  int getMonth(void) const;
  void setMonth(const int t_month);
  int getDay(void) const;
  void setDay(const int t_day);
  int getHour(void) const;
  void setHour(const int t_hour);
  int getMinute(void) const;
  void setMinute(const int t_minute);
  static bool isValid(const Date t_date);
  static Date stringToDate(const std::string t_dateString);
  static std::string dateToString(Date t_date);
  Date &operator=(const Date &t_date);
  bool operator==(const Date &t_date) const;
  bool operator>(const Date &t_date) const;
  bool operator<(const Date &t_date) const;
  bool operator>=(const Date &t_date) const;
  bool operator<=(const Date &t_date) const;

private:
  int m_year;
  int m_month;
  int m_day;
  int m_hour;
  int m_minute;
};

#endif
