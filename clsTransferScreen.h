#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "Global.h"
class clsTransferScreen : clsScreen
{
private:
    
	  static string _ReadAccountNumber() {

		string AccountNumber;

		cout << "\nPlease Enter Account Number to Transfer From: ";

		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber)) {

			cout << "\nAccount number is not found, choose another one: ";

			AccountNumber = clsInputValidate::ReadString();
		}

		return AccountNumber;
	}

    
	 static float ReadAmount(clsBankClient SourceClient) {

		  float Amount;

		  cout << "\nEnter Transfer Amount? ";


		  Amount = clsInputValidate::ReadFloatNumber();

		  while (Amount > SourceClient.AccountBalance ) {

			  cout << "\nAmount Exceeds the available Balance, Enter another Amount ? ";

			  Amount = clsInputValidate::ReadFloatNumber();
		  }

		  return Amount;

	  }

	  static void _PrintClient(clsBankClient Client)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFull Name   : " << Client.FullName();
		cout << "\nAcc. Number : " << Client.AccountNumber();
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n___________________\n";

	}


public:

	static void ShowTransferScreen() {

		_DrawScreenHeader("\t Transfer Screen");

		clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumber());

		_PrintClient(SourceClient);

		clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber());

		_PrintClient(DestinationClient);

		float Amount;

		Amount = ReadAmount(SourceClient);

	  
		cout << "\nAre you sure you want to perform this operation? y/n? ";
		char Answer = 'n';

		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y') {

			if (SourceClient.Transfer(Amount , DestinationClient , CurrentUser.UserName)) {

				cout << "\nTransfer done successfully\n";

			}
			else {
				cout << "\nTransfer Failed \n";
			}

			_PrintClient(SourceClient);
			_PrintClient(DestinationClient);
		}

		}
		

};

