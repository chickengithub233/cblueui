#ifndef CBLUEUI_DATEINFO_UNTILS_BLXDY_INC_H_
#define CBLUEUI_DATEINFO_UNTILS_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "core/CCoreBasePro.h"

struct time_stamp
{
	int tm_usec;  // microsecond seconds after the seconds
	int tm_sec;   // seconds after the minute - [0, 60] including leap second
	int tm_min;   // minutes after the hour - [0, 59]
	int tm_hour;  // hours since midnight - [0, 23]
	int tm_mday;  // day of the month - [1, 31]
	int tm_mon;   // months since January - [1, 12]
	int tm_year;  // years since 1900
	int tm_wday;  // days since Sunday - [0, 6]
	int tm_yday;  // days since January 1 - [0, 365]
	int tm_isdst; // daylight savings time flag
};

UI_EXP void get_current_time_stamp(time_stamp* tm);

struct LunarDate
{
	int32_t lunarYear;
	int32_t lunarMonth;
	int32_t lunarDay;
	int32_t solarYear;
	int32_t solarMonth;
	int32_t solarDay;
	int32_t weekNumber;
	int32_t termIndex;
	bool isToday, isLeap;
};

/**
 * @brief 日期类，包含中国农历历法1900到2099年
 *
 */
class UI_EXP DateInfo
{
  public:
	DateInfo(int year = 1901, int month = 1, int day = 1);
	DateInfo(const DateInfo& d);

	BOOL IsLeapYear() const;
	void Zero();
	BOOL IsZero() const;

	int WeekFirstDay(int year, int month); ///< 计算当前月的第一天是星期几
	int DayOfTheWeek();                    ///< 获得周几

	DateInfo operator+(int day); ///< 日期加天数
	DateInfo operator-(int day); ///< 日期减天数

	bool operator==(const DateInfo& d);
	bool operator!=(const DateInfo& d);
	bool operator<=(const DateInfo& d);
	bool operator>=(const DateInfo& d);

	bool operator<(const DateInfo& d);
	bool operator>(const DateInfo& d);
	DateInfo& operator=(const DateInfo& d);

	void PrintfLunarDate(char* buffer, int buffersize) const; ///< 农历日期

	void PrintfLunarYear(char* buffer, int buffersize) const; ///< 农历生肖年份
	int MonthDayCounts() const;                               ///< 计算当年月的天数


  public:
	int m_year;       // 年
	int m_month;      // 月
	int m_dayOfMonth; // 日
};



#endif
