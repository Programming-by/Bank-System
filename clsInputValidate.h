#pragma once

#include <iostream>
#include "clsDate.h"

using namespace std;

class clsInputValidate
{

public:

	static bool IsNumberBetween(short Number, short From, short To) {

		if (Number >= From && Number <= To)
			return true;
		else
			return false;
	}

	static bool IsNumberBetween(int Number, int From, int To) {

		if (Number >= From && Number <= To)
			return true;
		else
			return false;
	}

	static bool IsNumberBetween(float Number, float From, float To) {

		if (Number >= From && Number <= To)
			return true;
		else
			return false;
	}

	static bool IsNumberBetween(double Number, double From, double To) {
		if (Number >= From && Number <= To)
			return true;
		else
			return false;
	}
	static bool IsDateBetween(clsDate Date, clsDate From, clsDate To) {

		//Date>=From && Date<=To
		if ((clsDate::IsDate1AfterDate2(Date, From) || clsDate::IsDate1EqualDate2(Date, From))
			&&
			(clsDate::IsDate1BeforeDate2(Date, To) || clsDate::IsDate1EqualDate2(Date, To))
			)
		{
			return true;
		}

		//Date>=To && Date<=From

		if ((clsDate::IsDate1AfterDate2(Date, To) || clsDate::IsDate1EqualDate2(Date, To))
			&&
			(clsDate::IsDate1BeforeDate2(Date, From) || clsDate::IsDate1EqualDate2(Date, From))
			)
		{
			return true;
		}

		return false;

	}

	static int ReadIntNumber(string ErrorMessage = "Invalid Number,Enter again:\n") {
		int Number = 0;

		while (!(cin >> Number)) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << ErrorMessage;
		}

		return Number;
	}
	static int ReadIntNumberBetween(int From, int To, string ErrorMessage = "\nNumber is not within range, please enter again\n") {

		int Number = ReadIntNumber();
		while (!IsNumberBetween(Number, From, To)) {
			cout << ErrorMessage;
			cin >> Number;
		}
		return Number;

	}


		static float ReadFloatNumber(string ErrorMessage = "Invalid Number,Enter again:\n") {
			float Number = 0;

			while (!(cin >> Number)) {
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cout << ErrorMessage;
			}

			return Number;
		}



	static double ReadDblNumber(string ErrorMessage = "Invalid Number,Enter again:\n") {
		double Number = 0;

		while (!(cin >> Number)) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}

	static double ReadDblNumberBetween(double From, double To, string ErrorMessage = "\nNumber is not within range, please enter again\n") {

		double Number = ReadDblNumber();
		while (!IsNumberBetween(Number, From, To)) {
			cout << ErrorMessage;
			cin >> Number;
		}
		return Number;

	}

	static bool IsValideDate(clsDate Date) {

		return clsDate::IsValidDate(Date);
	}


	static string ReadString() {

		string S1 = "";

		getline(cin >> ws , S1);

		return S1;

	}


};

