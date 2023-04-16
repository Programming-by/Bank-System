#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsMainScreen.h"
#include "Global.h"
class clsLoginScreen : protected clsScreen

{

private:

	static bool _Login() {

		string UserName, Password;

		bool LoginFailed = false;

		short FailedLoginCount = 0;

		do {
			if (LoginFailed) {
				FailedLoginCount++;
				cout << "\nInvlaid Username/Password!";
				cout << "\nYou have " << (3 - FailedLoginCount) << " Trial(s) to login.\n\n";
			} 

			if (FailedLoginCount == 3) {
				cout << "\nYour are Locked after 3 faild trials \n\n";
				return false;
			}


			cout << "Enter Username? ";
			cin >> UserName;
			cout << "Enter Password? ";
			cin >> Password;

			CurrentUser = clsUser::Find(UserName, Password);

			LoginFailed = CurrentUser.IsEmpty();

		} while (LoginFailed);

		CurrentUser.RegisterLogIn();
		clsMainScreen::ShowMainMenue();
		return true;
	}

public:

	static bool ShowLoginScreen() {

		system("cls");
		_DrawScreenHeader("\t  Login Screen");
	 return	_Login();
         
	}



};

