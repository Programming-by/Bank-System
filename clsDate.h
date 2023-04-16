#pragma once

#pragma warning(disable : 4996)


#include <iostream>
#include<string>
#include "clsString.h"
using namespace std;
class clsDate
{

private:

	short _Day = 1;
	short _Month = 1;
	short _Year = 1900;


public:

	clsDate() {
		time_t t = time(0);
		tm* now = localtime(&t);
		_Day = now->tm_mday;
		_Month = now->tm_mon + 1;
		_Year = now->tm_year + 1900;
	}

	clsDate(string sDate) {


		vector <string> vDate;

		vDate = clsString::Split(sDate, "/");

		_Day = stoi(vDate[0]);
		_Month = stoi(vDate[1]);
		_Year = stoi(vDate[2]);


	}

	clsDate(short Day, short Month, short Year) {

		_Day = Day;
		_Month = Month;
		_Year = Year;
	}

	clsDate(short NumberOfDays, short Year) {

		clsDate Date;

		Date = GetDateFromDayOrderInYear(NumberOfDays, Year);

		_Day = Date.Day;
		_Month = Date.Month;
		_Year = Date.Year;


	}

	void SetDay(short Day) {
		_Day = Day;
	}

	short GetDay() {
		return _Day;
	}

	__declspec(property(get = GetDay, put = SetDay)) short Day;

	void SetMonth(short Month) {
		_Month = Month;
	}

	short GetMonth() {
		return _Month;
	}

	__declspec(property(get = GetMonth, put = SetMonth)) short Month;


	void SetYear(short Year) {
		_Year = Year;
	}

	short GetYear() {
		return _Year;
	}

	__declspec(property(get = GetYear, put = SetYear)) short Year;


	void Print() {
		cout << DateToString() << endl;
	}


	static bool IsLeapYear(short Year) {

		return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
	}

	bool IsLeapYear() {
		return IsLeapYear(_Year);
	}


	static short NumberOfDaysInAYear(short Year) {

		return IsLeapYear(Year) ? 366 : 365;

	}

	short NumberOfDaysInAYear() {

		return NumberOfDaysInAYear(_Year);

	}

	static short NumberOfDaysInAMonth(short Month, short Year) {
		if (Month < 1 || Month>12)
			return  0;
		int days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
		return (Month == 2) ? (IsLeapYear(Year) ? 29 : 28) : days[Month - 1];
	}

	short NumberOfDaysInAMonth() {
		return NumberOfDaysInAMonth(_Month, _Year);
	}

	static short NumberOfHoursInAMonth(short Month, short Year) {
		return NumberOfDaysInAMonth(Month, Year) * 24;
	}

	short NumberOfHoursInAMonth() {
		return NumberOfDaysInAMonth(_Month, _Year) * 24;
	}


	static int NumberOfMinutesInAMonth(short Month, short Year) {
		return NumberOfHoursInAMonth(Month, Year) * 60;
	}

	int NumberOfMinutesInAMonth() {
		return NumberOfHoursInAMonth(_Month, _Year) * 60;
	}


	static int NumberOfSecondsInAMonth(short Month, short Year) {
		return NumberOfMinutesInAMonth(Month, Year) * 60;
	}


	int NumberOfSecondsInAMonth() {
		return NumberOfMinutesInAMonth(_Month, _Year) * 60;
	}

	static short NumberOfDaysFromBeginingOfYear(short Day, short Month, short Year) {
		//calculate days from begining of year to current day
		//31 + 29 + ...
		//calculate numbers from month 1 to month 8 and then add rest days in month 9 
		//20/9/2022
		short TotalDays = 0;

		for (int i = 1; i <= Month - 1; i++)
		{
			TotalDays += NumberOfDaysInAMonth(i, Year);
		}
		TotalDays += Day;
		
		return TotalDays;
	}

	short NumberOfDaysFromBeginingOfYear() {
		return NumberOfDaysFromBeginingOfYear(_Day, _Month, _Year);
	}

	clsDate GetDateFromDayOrderInYear(short DaysOrderInYear, short Year) {
		clsDate Date;

		short RemainingDays = DaysOrderInYear;

		short MonthDays = 0;

		_Year = Year;
		_Month = 1;

		while (true) {
			MonthDays = NumberOfDaysInAMonth(_Month, Year);
			if (RemainingDays > MonthDays) {
				RemainingDays -= MonthDays;
				_Month++;
			}
			else {
				_Day = RemainingDays;
				break;
			}
		}

		return Date;
	}

	static clsDate AddOneDay(short Days, clsDate Date) {


		short RemainingDays = Days + NumberOfDaysFromBeginingOfYear(Date.Day, Date.Month, Date.Year);
		short MonthDays = 0;
		Date.Month = 1;

		while (true) {

			MonthDays = NumberOfDaysInAMonth(Date.Month, Date.Year);

			if (RemainingDays > MonthDays) {
				RemainingDays -= MonthDays;
				Date.Month++;

				if (Date.Month > 12) {
					Date.Month = 1;
					Date.Year++;
				}


			}
			else {
				Date.Day = RemainingDays;
				break;
			}
		}

		return Date;


	}

	void AddOneDay(short Days) {
		clsDate Date;
		Date = AddOneDay(Days, *this);
	}



	static clsDate GetSystemDate() {
		time_t t = time(0); // get time now
		tm* now = localtime(&t);
		short Day, Month, Year;
		Day = now->tm_mday;
		Month = now->tm_mon + 1;
		Year = now->tm_year + 1900;


		return clsDate(Day, Month, Year);
	}


	static string GetSystemDateTimeString() {

		time_t t = time(0); // get time now
		tm* now = localtime(&t);
		short Day, Month, Year,Hour,Minute,Second;
		Day = now->tm_mday;
		Month = now->tm_mon + 1;
		Year = now->tm_year + 1900;
		Hour = now->tm_hour;
		Minute = now->tm_min;
		Second = now->tm_sec;


		return to_string(Day) + "/" + to_string(Month) + "/" + to_string(Year) + " - " + to_string(Hour) + ":" + to_string(Minute) + ":" + to_string(Second);

	}


	static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2) {

		return Date1.Year < Date2.Year ? true : (Date1.Year == Date2.Year) ? Date1.Month < Date2.Month ? true : (Date1.Month == Date2.Month) ? Date1.Day < Date2.Day : false : false;

	}


	static bool IsDate1EqualDate2(clsDate Date1, clsDate Date2) {

		return  (Date1.Year == Date2.Year) ? ((Date1.Month == Date2.Month) ? ((Date1.Day == Date2.Day) ? true : false) : false) : false;

	}


	static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2) {

		return (!IsDate1BeforeDate2(Date1, Date2)) && (!IsDate1EqualDate2(Date1, Date2));


	}



	enum enCompareResult { Before = -1, Equal = 0, After = 1 };

	static short CompareDates(clsDate Date1, clsDate Date2) {


		return IsDate1AfterDate2(Date1, Date2) ? enCompareResult::After : IsDate1BeforeDate2(Date1, Date2) ? enCompareResult::Before : enCompareResult::Equal;

	}


	short CompareDates(clsDate Date2) {
		return CompareDates(*this, Date2);

	}

	static string NumberToText(int Number) {

		if (Number == 0) {
			return "";
		}

		if (Number >= 1 && Number <= 19) {
			string arr[] = { "" , "One","Two","Three","Four","Five","Six","Seven",
					"Eight","Nine","Ten","Eleven","Twelve","Thirteen","Fourteen",
						"Fifteen","Sixteen","Seventeen","Eighteen","Nineteen"
			};

			return arr[Number] + "";

		}

		if (Number >= 20 && Number <= 99) {
			string arr[] = { "" , "","Twenty","Thirty","Forty","Fifty","Sixty","Seventy",
					"Eighty","Ninty"
			};

			return arr[Number / 10] + "" + NumberToText(Number % 10);

		}

		if (Number >= 100 && Number <= 199) {

			return "One Hundred " + NumberToText(Number % 100);

		}

		if (Number >= 200 && Number <= 999) {

			return  NumberToText(Number / 100) + " Hundreds " + NumberToText(Number % 100);


		}


		if (Number >= 1000 && Number <= 1999) {

			return "One Thousand " + NumberToText(Number % 1000);


		}

		if (Number >= 2000 && Number <= 9999) {

			return  NumberToText(Number / 1000) + " Thousand " + NumberToText(Number % 1000);

		}

		if (Number >= 1000000 && Number <= 1999999)
		{
			return "One Million " + NumberToText(Number % 1000000);
		}
		if (Number >= 2000000 && Number <= 999999999)
		{
			return NumberToText(Number / 1000000) + "Millions " +
				NumberToText(Number % 1000000);
		}
		if (Number >= 1000000000 && Number <= 1999999999)
		{
			return "One Billion " + NumberToText(Number %
				1000000000);
		}
	}


	static bool IsLastDayInMonth(clsDate Date) {
		return (NumberOfDaysInAMonth(Date.Month, Date.Year) == Date.Day);
	}

	bool IsLastDayInMonth() {
		return IsLastDayInMonth(*this);
	}

	static bool IsLastMonthInYear(short Month) {
		return (Month == 12);
	}

	bool IsLastMonthInYear() {
		return IsLastMonthInYear(_Month);
	}

	static clsDate IncreaseDateByOneDay(clsDate Date) {


		if (IsLastDayInMonth(Date)) {

			if (IsLastMonthInYear(Date.Month)) {

				Date.Day = 1;
				Date.Month = 1;
				Date.Year++;
			}
			else {
				Date.Day = 1;
				Date.Month++;
			}
		}
		else {
			Date.Day++;
		}

		return Date;
	}

	clsDate IncreaseDateByOneDay() {
		return IncreaseDateByOneDay(*this);
	}


	static clsDate IncreaseDateByXDays(short Days, clsDate Date) {


		for (short i = 1; i <= Days; i++)
		{
			Date = IncreaseDateByOneDay(Date);
		}
		return Date;
	}

	clsDate IncreaseDateByXDays(short Days) {

		return IncreaseDateByXDays(Days, *this);
	}


	static clsDate IncreaseDateByOneWeek(clsDate& Date) {


		for (short i = 1; i <= 7; i++)
		{
			Date = IncreaseDateByOneDay(Date);
		}
		return Date;
	}

	void  IncreaseDateByOneWeek() {
		IncreaseDateByOneWeek(*this);
	}


	static clsDate IncreaseDateByXWeeks(short Weeks, clsDate Date) {

		for (short i = 1; i <= Weeks; i++)
		{
			Date = IncreaseDateByOneWeek(Date);
		}
		return Date;

	}

	clsDate IncreaseDateByXWeeks(short Weeks) {
		return IncreaseDateByXWeeks(Weeks, *this);
	}


	static clsDate IncreaseDateByOneMonth(clsDate Date) {

		if (IsLastMonthInYear(Date.Month)) {
			Date.Month = 1;
			Date.Year++;
		}
		else {
			Date.Month++;
		}
		//	31/1/2022 ++ => 31/2/2022 and month 2 has only 28 or 29 days
		short NumberOfDaysInCurrenrMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);

		if (Date.Day > NumberOfDaysInCurrenrMonth) {
			Date.Day = NumberOfDaysInCurrenrMonth;
		}


		return Date;
	}

	clsDate IncreaseDateByOneMonth() {

		return IncreaseDateByOneMonth(*this);

	}


	static clsDate IncreaseDateByXMonths(short Months, clsDate Date) {

		for (short i = 1; i <= Months; i++)
		{
			Date = IncreaseDateByOneMonth(Date);
		}
		return Date;
	}

	clsDate IncreaseDateByXMonths(short Months) {
		return IncreaseDateByXMonths(Months, *this);
	}

	static clsDate IncreaseDateByOneYear(clsDate Date) {

		Date.Year++;

		return Date;
	}

	clsDate IncreaseDateByOneYear() {
		return IncreaseDateByOneYear(*this);
	}

	static clsDate IncreaseDateByXYears(short Years, clsDate Date) {

		for (short i = 1; i <= Years; i++)
		{
			Date = IncreaseDateByOneYear(Date);
		}
		return Date;
	}

	clsDate IncreaseDateByXYears(short Years) {

		return IncreaseDateByXYears(Year, *this);
	}

	static clsDate IncreaseDateByXYearsFaster(short Years, clsDate Date) {

		Date.Year += Years;
		return Date;
	}

	clsDate IncreaseDateByXYearsFaster(short Years) {
		return IncreaseDateByXYearsFaster(Year, *this);
	}

	static clsDate IncreaseDateByOneDecade(clsDate Date) {


		Date.Year += 10;

		return Date;
	}

	clsDate IncreaseDateByOneDecade() {
		return IncreaseDateByOneDecade(*this);
	}


	static clsDate IncreaseDateByXDecades(short Decades, clsDate Date) {


		for (short i = 1; i <= Decades * 10; i++)
		{
			Date = IncreaseDateByOneYear(Date);
		}

		return Date;
	}

	clsDate IncreaseDateByXDecades(short Decades) {

		return IncreaseDateByXDecades(Decades, *this);
	}


	static clsDate IncreaseDateByXDecadesFaster(short Decades, clsDate Date) {

		Date.Year += Decades * 10;

		return Date;
	}

	clsDate IncreaseDateByXDecadesFaster(short Decades) {
		return IncreaseDateByXDecadesFaster(Decades, *this);
	}

	static clsDate IncreaseDateByOneCentury(clsDate Date) {

		const short Century = 100;

		Date.Year += Century;

		return Date;
	}

	clsDate IncreaseDateByOneCentury() {
		return IncreaseDateByOneCentury(*this);
	}



	static clsDate IncreaseDateByOneMillennium(clsDate Date) {

		Date.Year += 1000;

		return Date;
	}

	clsDate IncreaseDateByOneMillennium() {
		return IncreaseDateByOneMillennium(*this);
	}


	static short DayOfWeekOrder(short Day, short Month, short Year) {

		short a, m, y;

		a = (14 - Month) / 12;

		y = Year - a;

		m = Month + (12 * a) - 2;

		return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
	}

	short DayOfWeekOrder() {

		return DayOfWeekOrder(_Day, _Month, _Year);
	}

	static string DayShortName(short DayOfWeekOrder) {

		string arrDayNames[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };

		return arrDayNames[DayOfWeekOrder];

	}

	string DayShortName() {
		return DayShortName(_Day);
	}


	static string MonthShortName(short MonthNumber) {

		string arrMonthNames[] = { "Jan","Feb","March","Apr","May","June","July", "Aug" , "Sep" , "Oct" , "Nov" , "Dec" };

		return arrMonthNames[MonthNumber - 1];

	}

	string MonthShortName() {
		return MonthShortName(_Month);
	}


	static void PrintMonthCalender(short Month, short Year) {

		int NumberOfDays;
		int current = DayOfWeekOrder(1, Month, Year);
		NumberOfDays = NumberOfDaysInAMonth(Month, Year);
		printf("\n  _______________%s_______________\n\n",
			MonthShortName(Month).c_str());
		printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");
		int i;
		for (i = 0; i < current; i++)
			printf("     ");
		for (int j = 1; j <= NumberOfDays; j++)
		{
			printf("%5d", j);

			if (++i == 7) {
				i = 0;
				printf("\n");
			}

		}

		printf("\n  _________________________________\n");
	}

	void PrintMonthCalender() {
		PrintMonthCalender(_Month, _Year);
	}

	static void PrintYearCalender(short Year) {

		printf("\n _________________________________\n\n");
		printf(" Calendar - %d\n", Year);
		printf(" _________________________________\n");
		for (int i = 1; i <= 12; i++)
		{
			PrintMonthCalender(i, Year);

		}
	}


	void PrintYearCalender() {
		PrintYearCalender(_Year);
	}

	static bool IsValidDate(clsDate Date) {

		if (Date.Day < 1 || Date.Day > 31) {
			return false;
		}

		if (Date.Month < 1 || Date.Month > 12) {
			return false;
		}


		if (Date.Month == 2)
		{
			if (IsLeapYear(Date.Year))
			{
				if (Date.Day > 29) {
					return false;
				}
			}
			else {
				if (Date.Day > 28) {
					return false;
				}
			}
		}

		short DaysInMonth = NumberOfDaysInAMonth(Date.Month,
			Date.Year);
		if (Date.Day > DaysInMonth)
			return false;
		return true;

	}

	bool IsValidDate() {

		return IsValidDate(*this);

	}


	static bool IsEndOfWeek(clsDate Date) {
		return DayOfWeekOrder(Date.Day, Date.Month, Date.Year) == 6;
	}

	bool IsEndOfWeek() {
		return IsEndOfWeek(*this);
	}

	static bool IsWeekend(clsDate Date) {

		short DayIndex = DayOfWeekOrder(Date.Day, Date.Month, Date.Year);
		return (DayIndex == 5 || DayIndex == 6);
	}

	bool IsWeekend() {

		return IsWeekend(*this);

	}

	static bool IsBusinessDay(clsDate Date) {
		return !IsWeekend(Date);
	}

	bool IsBusinessDay() {
		return IsBusinessDay(*this);
	}

	static short DaysUntilTheEndOfWeek(clsDate Date) {

		return  6 - DayOfWeekOrder(Date.Day, Date.Month, Date.Year);
	}

	short DaysUntilTheEndOfWeek() {

		return DaysUntilTheEndOfWeek(*this);
	}




	static short DaysUntilTheEndOfMonth(clsDate Date) {
		/*short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);
		NumberOfDaysInCurrentMonth -= Date.Day;
		return NumberOfDaysInCurrentMonth;*/

		clsDate EndOfMonthDate;

		EndOfMonthDate.Day = NumberOfDaysInAMonth(Date.Month, Date.Year);

		EndOfMonthDate.Month = Date.Month;
		EndOfMonthDate.Year = Date.Year;

		return GetDifferenceInDays(Date, EndOfMonthDate, true);


	}

	short DaysUntilTheEndOfMonth() {
		return DaysUntilTheEndOfMonth(*this);
	}



	static short DaysUntilTheEndOfYear(clsDate Date) {
		clsDate EndOfMonthDate;

		EndOfMonthDate.Day = 31;
		EndOfMonthDate.Month = 12;
		EndOfMonthDate.Year = Date.Year;

		return GetDifferenceInDays(Date, EndOfMonthDate, true);


	}

	short DaysUntilTheEndOfYear() {

		return DaysUntilTheEndOfYear(*this);

	}



	static short CalculateVacationDays(clsDate Date1, clsDate Date2) {

		return CalculateBusinessDays(Date1, Date2);

	}


	static short CalculateBusinessDays(clsDate DateFrom, clsDate DateTo) {
		short Days = 0;

		while (IsDate1BeforeDate2(DateFrom, DateTo)) {

			if (IsBusinessDay(DateFrom)) {
				Days++;
				DateFrom = IncreaseDateByOneDay(DateFrom);
			}

		}
		return Days;
	}



	static	clsDate CalculateVacationReturnDate(clsDate DateFrom, short VacationDays)
	{
		short WeekendCounter = 0;

		for (short i = 1; i <= VacationDays; i++)
		{
			if (IsWeekend(DateFrom)) {
				WeekendCounter++;
			}

			DateFrom = IncreaseDateByOneDay(DateFrom);
		}

		for (short i = 1; i <= WeekendCounter; i++)
			DateFrom = IncreaseDateByOneDay(DateFrom);

		while (IsWeekend(DateFrom)) {
			DateFrom = IncreaseDateByOneDay(DateFrom);

		}
		return DateFrom;
	}

	clsDate CalculateVacationReturnDate(short VacationDays) {

		return CalculateVacationReturnDate(*this, VacationDays);

	}


	static clsDate DecreaseDateByOneDay(clsDate Date) {

		if (Date.Day == 1) {
			if (Date.Month == 1) {
				Date.Day = 31;
				Date.Month = 12;
				Date.Year--;
			}
			else {
				Date.Month--;
				Date.Day = NumberOfDaysInAMonth(Date.Month, Date.Year);
			}

		}
		else {
			Date.Day--;
		}

		return Date;
	}

	clsDate DecreaseDateByOneDay() {
		return DecreaseDateByOneDay(*this);
	}



	static clsDate DecreaseDateByXDays(short Days, clsDate Date) {


		for (short i = 1; i <= Days; i++)
		{
			Date = DecreaseDateByOneDay(Date);
		}
		return Date;
	}

	clsDate DecreaseDateByXDays(short Days) {

		return DecreaseDateByXDays(Days, *this);
	}



	static clsDate DecreaseDateByOneWeek(clsDate Date) {


		for (short i = 1; i <= 7; i++)
		{
			Date = DecreaseDateByOneDay(Date);
		}
		return Date;
	}

	clsDate DecreaseDateByOneWeek() {
		return DecreaseDateByOneWeek(*this);
	}

	static clsDate DecreaseDateByXWeeks(short Weeks, clsDate Date) {

		for (short i = 1; i <= Weeks; i++)
		{
			Date = DecreaseDateByOneWeek(Date);
		}
		return Date;

	}

	clsDate DecreaseDateByXWeeks(short Weeks) {

		return DecreaseDateByXWeeks(Weeks, *this);
	}


	static clsDate DecreaseDateByOneMonth(clsDate Date) {

		if (Date.Month == 1) {
			Date.Month = 12;
			Date.Year--;
		}
		else {
			Date.Month--;
		}
		/*
		31/3/2022 => 31/2/2022 wrong
		*/

		short NumberOfDaysInCurrenrMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);

		if (Date.Day > NumberOfDaysInCurrenrMonth) {
			Date.Day = NumberOfDaysInCurrenrMonth;
		}


		return Date;
	}

	clsDate DecreaseDateByOneMonth() {
		return DecreaseDateByOneMonth(*this);
	}



	static clsDate DecreaseDateByXMonths(short Months, clsDate Date) {

		for (short i = 1; i <= Months; i++)
		{
			Date = DecreaseDateByOneMonth(Date);
		}
		return Date;
	}

	clsDate DecreaseDateByXMonths(short Months) {
		return DecreaseDateByXMonths(Months, *this);
	}

	static clsDate DecreaseDateByOneYear(clsDate Date) {

		Date.Year--;

		return Date;
	}

	clsDate DecreaseDateByOneYear() {
		return DecreaseDateByOneYear(*this);
	}

	static clsDate DecreaseDateByXYears(short Years, clsDate Date) {

		for (short i = 1; i <= Years; i++)
		{
			Date = DecreaseDateByOneYear(Date);
		}
		return Date;
	}

	clsDate DecreaseDateByXYears(short Years) {

		return DecreaseDateByXYears(Years, *this);

	}


	static clsDate DecreaseDateByXYearsFaster(short Years, clsDate Date) {

		Date.Year -= Years;
		return Date;
	}


	clsDate DecreaseDateByXYearsFaster(short Years) {

		return DecreaseDateByXYearsFaster(Years, *this);
	}

	clsDate DecreaseDateByOneDecade(clsDate Date) {


		Date.Year -= 10;

		return Date;
	}

	clsDate DecreaseDateByOneDecade() {
		return DecreaseDateByOneDecade(*this);
	}


	static clsDate DecreaseDateByXDecades(short Decades, clsDate Date) {


		for (short i = 1; i <= Decades * 10; i++)
		{
			Date = DecreaseDateByOneYear(Date);
		}

		return Date;
	}

	clsDate DecreaseDateByXDecades(short Decades) {
		return DecreaseDateByXDecades(Decades, *this);
	}


	static clsDate DecreaseDateByXDecadesFaster(short Decades, clsDate Date) {

		Date.Year -= Decades * 10;

		return Date;
	}

	clsDate DecreaseDateByXDecadesFaster(short Decades) {
		return DecreaseDateByXDecadesFaster(Decades, *this);
	}


	clsDate DecreaseDateByOneCentury(clsDate Date) {

		Date.Year -= 100;

		return Date;
	}

	clsDate DecreaseDateByOneCentury() {

		return DecreaseDateByOneCentury(*this);
	}


	static clsDate DecreaseDateByOneMillennium(clsDate Date) {

		Date.Year -= 1000;

		return Date;
	}

	clsDate DecreaseDateByOneMillennium() {
		return DecreaseDateByOneMillennium(*this);
	}



	static void SwapDates(clsDate& Date1, clsDate& Date2) {

		clsDate TempDate;


		TempDate.Day = Date1.Day;
		TempDate.Month = Date1.Month;
		TempDate.Year = Date1.Year;

		Date1.Day = Date2.Day;
		Date1.Month = Date2.Month;
		Date1.Year = Date2.Year;


		Date2.Day = TempDate.Day;
		Date2.Month = TempDate.Month;
		Date2.Year = TempDate.Year;

	}

	static int GetDifferenceInDays(clsDate Date1, clsDate Date2, bool IncludeEndDay = false) {

		int Days = 0;
		short SwapFlagValue = 1;

		if (!IsDate1BeforeDate2(Date1, Date2)) {
			SwapDates(Date1, Date2);
			SwapFlagValue = -1;
		}


		while (IsDate1BeforeDate2(Date1, Date2)) {
			Days++;
			Date1 = IncreaseDateByOneDay(Date1);
		}

		return IncludeEndDay ? ++Days * SwapFlagValue : Days * SwapFlagValue;

	}

	int GetDifferenceInDays(clsDate Date1, bool IncludeEndDay = false) {

		return GetDifferenceInDays(Date1, *this, IncludeEndDay);
	}



	static string FormateDate(clsDate Date, string DateFormat = "dd/mm/yyyy") {

		string FormattedDateString = "";

		FormattedDateString = clsString::ReplaceString(DateFormat, "dd", to_string(Date.Day));
		FormattedDateString = clsString::ReplaceString(FormattedDateString, "mm", to_string(Date.Month));
		FormattedDateString = clsString::ReplaceString(FormattedDateString, "yyyy", to_string(Date.Year));

		return FormattedDateString;
	}

	string FormateDate(string DateFormat = "dd/mm/yyyy") {

		return FormateDate(*this, DateFormat);

	}
	//
	//
	//
	static clsDate StringToDate(string StringDate) {

		clsDate Date;
		vector <string> vDate;

		vDate = clsString::Split(StringDate, "/");

		Date.Day = stoi(vDate[0]);
		Date.Month = stoi(vDate[1]);
		Date.Year = stoi(vDate[2]);

		return Date;

	}

	static string DateToString(clsDate Date) {
		return to_string(Date.Day) + "/" + to_string(Date.Month) + "/" + to_string(Date.Year);

	}

	string DateToString() {
		return DateToString(*this);
	}


};


