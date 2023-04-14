#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsMainScreen.h"
#include "Global.h"
class clsLoginScreen : protected clsScreen

{

private:

	static void _Login() {

		string UserName, Password;

		bool LoginFailed = false;

		do {
			if (LoginFailed) {
				cout << "\nInvlaid Username/Password!\n\n";
			}

			cout << "Enter Username? ";
			cin >> UserName;
			cout << "Enter Password? ";
			cin >> Password;

			CurrentUser = clsUser::Find(UserName, Password);

			LoginFailed = CurrentUser.IsEmpty();

		} while (LoginFailed);

		clsMainScreen::ShowMainMenue();

	}

public:

	static void ShowLoginScreen() {

		system("cls");
		_DrawScreenHeader("\t  Login Screen");
		_Login();
         
	}



};

