#include <gtest/gtest.h>
#include <string>
#include "Date.hpp"

using std::string;

/*
 *  Test defaut constructor
 */
TEST(DateTest, DefaultConstructor) {
    Date date;
    EXPECT_EQ(0, date.getYear());
    EXPECT_EQ(0, date.getMonth());
    EXPECT_EQ(0, date.getDay());
    EXPECT_EQ(0, date.getHour());
    EXPECT_EQ(0, date.getMinute());
}

/*
 *  Test constructor that parse int to Date
 */
TEST(DateTest, IntConstructor) {
    Date date(2016, 7, 6, 12, 22);
    EXPECT_EQ(2016, date.getYear());
    EXPECT_EQ(7, date.getMonth());
    EXPECT_EQ(6, date.getDay());
    EXPECT_EQ(12, date.getHour());
    EXPECT_EQ(22, date.getMinute());
}

/*
 *  Test constructor that parse string to Date
 */
TEST(DateTest, StrConstructor) {
    string validStr("2016-07-06/12:43");
    Date testDate(validStr);
    Date blankDate;
    //  A valid case
    EXPECT_EQ(2016, testDate.getYear());
    EXPECT_EQ(7, testDate.getMonth());
    EXPECT_EQ(6, testDate.getDay());
    EXPECT_EQ(12, testDate.getHour());
    EXPECT_EQ(43, testDate.getMinute());
    //  Some invalid cases in which date or time don't take enough digits
    EXPECT_EQ(blankDate, Date("16-07-06/12:43"));
    EXPECT_EQ(blankDate, Date("2016-7-06/12:43"));
    EXPECT_EQ(blankDate, Date("2016-07-6/12:43"));
    EXPECT_EQ(blankDate, Date("2016-07-06/2:43"));
    EXPECT_EQ(blankDate, Date("2016-07-06/12:3"));
    //  Some invalid cases with wrong connecting symbols
    string testChar(" `~-_+=!@#$%^&*()[]{}\\|:;\'\",.<>/?");
    for (int i = 0; i < testChar.size(); ++i) {
        string invalidStr;
        if (testChar[i] != '-') {
            invalidStr = validStr;
            invalidStr[4] = testChar[i];
            EXPECT_EQ(blankDate, (invalidStr));
        }
        if (testChar[i] != '/') {
            invalidStr = validStr;
            invalidStr[10] = testChar[i];
            EXPECT_EQ(blankDate, (invalidStr));
        }
        if (testChar[i] != ':') {
            invalidStr = validStr;
            invalidStr[13] = testChar[i];
            EXPECT_EQ(blankDate, (invalidStr));
        }
    }
}

/*
 *  Test Date::stringToDate() method
 *  Just the same as the strConstructor
 */
TEST(DateTest, StrToDate) {
    string validStr("2016-07-06/12:43");
    Date testDate(Date::stringToDate(validStr));
    Date blankDate;
    EXPECT_EQ(testDate.getYear(), 2016);
    EXPECT_EQ(testDate.getMonth(), 7);
    EXPECT_EQ(testDate.getDay(), 6);
    EXPECT_EQ(testDate.getHour(), 12);
    EXPECT_EQ(testDate.getMinute(), 43);

    EXPECT_EQ(Date::stringToDate("16-07-06/12:43"), blankDate);
    EXPECT_EQ(Date::stringToDate("2016-7-06/12:43"), blankDate);
    EXPECT_EQ(Date::stringToDate("2016-07-6/12:43"), blankDate);
    EXPECT_EQ(Date::stringToDate("2016-07-06/2:43"), blankDate);
    EXPECT_EQ(Date::stringToDate("2016-07-06/12:3"), blankDate);
    EXPECT_EQ(Date::stringToDate("2.16-07-06/12:30"), blankDate);

    string testChar(" `~-_+=!@#$%^&*()[]{}\\|:;\'\",.<>/?");
    for (int i = 0; i < testChar.size(); ++i) {
        string invalidStr;
        if (testChar[i] != '-') {
            invalidStr = validStr;
            invalidStr[4] = testChar[i];
            EXPECT_EQ(Date::stringToDate(invalidStr), blankDate);
        }

        if (testChar[i] != '/') {
            invalidStr = validStr;
            invalidStr[10] = testChar[i];
            EXPECT_EQ(Date::stringToDate(invalidStr), blankDate);
        }

        if (testChar[i] != ':') {
            invalidStr = validStr;
            invalidStr[13] = testChar[i];
            EXPECT_EQ(Date::stringToDate(invalidStr), blankDate);
        }
    }
}

/*
 *  Test set functions
 */
TEST(DateTest, SetFunctions) {
    Date date;
    date.setYear(2014);
    date.setMonth(8);
    date.setDay(15);
    date.setHour(13);
    date.setMinute(0);
    EXPECT_EQ(2014, date.getYear());
    EXPECT_EQ(8, date.getMonth());
    EXPECT_EQ(15, date.getDay());
    EXPECT_EQ(13, date.getHour());
    EXPECT_EQ(0, date.getMinute());
}

/*
 *  Test Date::isValid() method
 */
TEST(DateTest, ValidationCheck) {
    int year = 2016, month = 7, day = 6, hour = 14, minute = 50;
    Date date(year, month, day, hour, minute);
    //  A valid case
    EXPECT_TRUE(Date::isValid(date));
    // Hour boundary test
    for (int i = -5; i < 30; ++i) {
        date.setHour(i);
        if (i < 0 || i >= 24) {
            EXPECT_FALSE(Date::isValid(date));
        } else {
            EXPECT_TRUE(Date::isValid(date));
        }
    }
    date.setHour(hour);
    //  Minute boundary test
    for (int i = -5; i < 5; i++) {
        date.setMinute(i);
        if (i < 0) {
            EXPECT_FALSE(Date::isValid(date));
        } else {
            EXPECT_TRUE(Date::isValid(date));
        }
    }
    for (int i = 55; i < 65; i++) {
        date.setMinute(i);
        if (i < 60) {
            EXPECT_TRUE(Date::isValid(date));
        } else {
            EXPECT_FALSE(Date::isValid(date));
        }
    }
    date.setMinute(minute);
    //  Year boundary test
    for (int i = 995; i < 1005; ++i) {
        date.setYear(i);
        if (i < 1000) {
            EXPECT_FALSE(Date::isValid(date));
        } else {
            EXPECT_TRUE(Date::isValid(date));
        }
    }
    for (int i = 9995; i < 10005; ++i) {
        date.setYear(i);
        if (i < 10000) {
            EXPECT_TRUE(Date::isValid(date));
        } else {
            EXPECT_FALSE(Date::isValid(date));
        }
    }
    date.setYear(year);

    //  Month boudary test
    for (int i = -5; i < 15; i++) {
        date.setMonth(i);
        if (i > 0 && i < 13) {
            EXPECT_TRUE(Date::isValid(date));
        } else {
            EXPECT_FALSE(Date::isValid(date));
        }
    }
    date.setMonth(month);

    //  Day boudary test
    int month31[] = {1, 3, 5, 7, 8, 10, 12};
    //  Not in leap year
    date.setYear(2015);
    for (int i = 1; i < 13; ++i) {
        date.setMonth(i);
        // Lower boundary test
        for (int j = -5; j < 5; ++j) {
            date.setDay(j);
            if (j < 1) {
                EXPECT_FALSE(Date::isValid(date));
            } else {
                EXPECT_TRUE(Date::isValid(date));
            }
        }
        //  Upper boundary test
        //  Feburary
        if (i == 2) {
            for (int j = 25; j < 35; ++j) {
                date.setDay(j);
                if (j <= 28) {
                    EXPECT_TRUE(Date::isValid(date));
                } else {
                    EXPECT_FALSE(Date::isValid(date));
                }
            }
        } else {
            bool month31Flag = false;
            for (int j = 0; j < sizeof(month31) / sizeof(int); j++) {
                if (month31[j] == i) {
                    month31Flag = true;
                    break;
                }
            }
            //  Monthes with 31 days
            if (month31Flag) {
                for (int j = 25; j < 35; ++j) {
                    date.setDay(j);
                    if (j <= 31) {
                        EXPECT_TRUE(Date::isValid(date));
                    } else {
                        EXPECT_FALSE(Date::isValid(date));
                    }
                }
                //  Monthes with 30 days
            } else {
                for (int j = 25; j < 35; ++j) {
                    date.setDay(j);
                    if (j <= 30) {
                        EXPECT_TRUE(Date::isValid(date));
                    } else {
                        EXPECT_FALSE(Date::isValid(date));
                    }
                }
            }
        }
    }

    //  In leap year
    int leapYears[] = {2000, 2004, 1600};
    int commonYears[] = {1500, 1700, 1800, 2001};
    date = Date(0, 2, 0, 12, 12);
    for (int i = 0; i < 3; ++i) {
        date.setYear(leapYears[i]);
        for (int j = 25; j < 35; ++j) {
            date.setDay(j);
            if (j <= 29) {
                EXPECT_TRUE(Date::isValid(date));
            } else {
                EXPECT_FALSE(Date::isValid(date));
            }
        }
    }
    for (int i = 0; i < 4; ++i) {
        date.setYear(commonYears[i]);
        for (int j = 25; j < 35; ++j) {
            date.setDay(j);
            if (j <= 28) {
                EXPECT_TRUE(Date::isValid(date));
            } else {
                EXPECT_FALSE(Date::isValid(date));
            }
        }
    }
}

/*
 *  Test Date::dateToString() method
 */
TEST(DateTest, DateToStr) {
    Date date1(2016, 7, 6, 17, 19);
    EXPECT_STREQ("2016-07-06/17:19", Date::dateToString(date1).c_str());
    Date date2(1001, 12, 5, 0, 1);
    EXPECT_STREQ("1001-12-05/00:01", Date::dateToString(date2).c_str());
    Date date3;
    EXPECT_STREQ("0000-00-00/00:00", Date::dateToString(date3).c_str());
    Date date4(1800, 2, 29, 12, 12);
    EXPECT_STREQ("0000-00-00/00:00", Date::dateToString(date4).c_str());
}


/*
 *  Test operators
 */
TEST(DateTest, OperatorCheck) {
    string dateStr("1111-11-11/11:11");
    Date date(2016, 7, 7, 10, 01);
    //  Assign
    Date date1 = date;
    ASSERT_EQ(Date::dateToString(date), Date::dateToString(date1));
    //  Equal
    EXPECT_TRUE(date == date1);
    EXPECT_TRUE(date >= date1);
    EXPECT_TRUE(date <= date1);
    EXPECT_FALSE(date < date1);
    EXPECT_FALSE(date > date1);
    //  Greater or less than
    date = Date::stringToDate(dateStr);
    for (int i = 0; i < dateStr.size(); ++i) {
        if (i != 4 && i != 5 && i != 7 & i != 10 && i != 13) {
            string dateStrL = dateStr;
            dateStrL[i] = '2';
            date1 = Date::stringToDate(dateStrL);
            EXPECT_TRUE(date < date1);
            EXPECT_TRUE(date <= date1);
            EXPECT_TRUE(date1 > date);
            EXPECT_TRUE(date1 >= date);
        }
    }
}
