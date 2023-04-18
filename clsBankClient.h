#pragma once 

#include <iostream>
#include <string>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include "Global.h"
using namespace std;


class clsBankClient : public clsPerson {


private:

	enum enMode {EmptyMode = 0 , UpdateMode = 1 , AddNewMode = 2 };

	enMode _Mode;

	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkedForDeleted = false;

	struct stTransferLogRecord;

	static stTransferLogRecord _ConvertTransferLogLineToRecord(string Line, string Seperator = "#//#") {

		stTransferLogRecord TransferLogRecord;

		vector <string> vTransferLog = clsString::Split(Line,Seperator);

		TransferLogRecord.DateTime = vTransferLog[0];
		TransferLogRecord.SourceAccountNumber = vTransferLog[1];
		TransferLogRecord.DestinationAccountNumber = vTransferLog[2];
		TransferLogRecord.Amount = stod(vTransferLog[3]);
		TransferLogRecord.srcBalanceAfter = vTransferLog[4];
		TransferLogRecord.destBalanceAfter = vTransferLog[5];
		TransferLogRecord.UserName = vTransferLog[6];

		return TransferLogRecord;

	}


	static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#") {

		vector <string> vClientData;

		vClientData = clsString::Split(Line, Seperator);


		return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2], vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));

	}

	static string _ConverClientObjectToLine(clsBankClient Client, string Seperator = "#//#") {


		string stClientRecord = "";

		stClientRecord += Client.FirstName + Seperator;
		stClientRecord += Client.LastName + Seperator;
		stClientRecord += Client.Email + Seperator;
		stClientRecord += Client.Phone + Seperator;
		stClientRecord += Client.AccountNumber() + Seperator;
		stClientRecord += Client.PinCode + Seperator;
		stClientRecord += to_string(Client.AccountBalance);

		return stClientRecord;

	}


	static vector <clsBankClient> _LoadClientsDataFromFile() {

		vector <clsBankClient> vClients;
		fstream MyFile;

		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open()) {

			string Line;


			while (getline(MyFile, Line)) {

                    
				clsBankClient Client = _ConvertLinetoClientObject(Line);

				vClients.push_back(Client);

			}

			MyFile.close();
		

		}

		return vClients;

	}


	static void _SaveCleintsDataToFile(vector <clsBankClient> vClients) {

		fstream MyFile;

		MyFile.open("Clients.txt", ios::out);


		if (MyFile.is_open()) {

			string DataLine;

			for (clsBankClient C : vClients) {

				if (C.MarkedForDeleted() == false) {

					DataLine = _ConverClientObjectToLine(C);

					MyFile << DataLine << endl;

				}
			}
		MyFile.close();
	   }

	}


	void _Update()
	{
		vector <clsBankClient> _vClients;
		_vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : _vClients)
		{
			if (C.AccountNumber() == AccountNumber())
			{
				C = *this;
				break;
			}

		}

		_SaveCleintsDataToFile(_vClients);

	}


	void _AddNew() {
		_AddDataLineToFile(_ConverClientObjectToLine(*this));
	}

	void _AddDataLineToFile(string stDataLine) {

		fstream MyFile;

		MyFile.open("Clients.txt", ios::out | ios::app);

		if (MyFile.is_open()) {

			MyFile << stDataLine << endl;
			MyFile.close();
		}
	}

public:

	struct stTransferLogRecord {

		string DateTime;
		string SourceAccountNumber;
		string DestinationAccountNumber;
		float Amount;
		string srcBalanceAfter;
		string destBalanceAfter;
		string UserName;

	};

	clsBankClient(enMode Mode , string FirstName, string LastName, string Email, string Phone , string AccountNumber , string PinCode , float AccountBalance)
		: clsPerson(FirstName, LastName, Email, Phone) 
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;;
	}


	bool IsEmpty() {

		return (_Mode == enMode::EmptyMode);
	}


	bool MarkedForDeleted() {
		return _MarkedForDeleted;
	}

	static clsBankClient _GetEmptyClientObject() {
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	string _PrepareTransferLogRecord(float Amount, clsBankClient DestinationClient, string UserName, string Seperator = "#//#") {
		string TransferLogRecord = "";

		TransferLogRecord += clsDate::GetSystemDateTimeString() + Seperator;
		TransferLogRecord += AccountNumber() + Seperator;
		TransferLogRecord += DestinationClient.AccountNumber() + Seperator;
		TransferLogRecord += to_string(Amount) + Seperator;
		TransferLogRecord += to_string(AccountBalance) + Seperator;
		TransferLogRecord += to_string(DestinationClient.AccountBalance) + Seperator;
		TransferLogRecord += UserName;


		return TransferLogRecord;


	}

	void _RegisterTransferLog(float Amount, clsBankClient DestinationClient, string UserName) {

		string stDataLine = _PrepareTransferLogRecord(Amount, DestinationClient, UserName);

		fstream MyFile;


		MyFile.open("TransferLog.txt", ios::out | ios::app);


		if (MyFile.is_open()) {


			MyFile << stDataLine << endl;

			MyFile.close();

		}

	}




	string AccountNumber() {
		return _AccountNumber;
	}


	void SetPinCode(string PinCode) {
		_PinCode = PinCode;
	}

	string GetPinCode() {
		return  _PinCode;
	}


	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

	void SetAccountBalance(float AccountBalance) {
		_AccountBalance = AccountBalance;
	}

	float GetAccountBalance() {
		return  _AccountBalance;
	}


	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;


	static clsBankClient Find(string AccountNumber) {

		fstream MyFile;


		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open()) {
			
			string Line;

			while (getline(MyFile, Line)) {

			clsBankClient Client = _ConvertLinetoClientObject(Line);

			if (Client.AccountNumber() == AccountNumber) {

				MyFile.close();
				return Client;

			}

			}

			MyFile.close();

		}
		return _GetEmptyClientObject();
	}

	static clsBankClient Find(string AccountNumber , string PinCode) {

		fstream MyFile;


		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open()) {

			string Line;

			while (getline(MyFile, Line)) {

				clsBankClient Client = _ConvertLinetoClientObject(Line);

				if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode) {

					MyFile.close();
					return Client;

				}

			}

			MyFile.close();

		}
		return _GetEmptyClientObject();
	}

  
	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2};

	enSaveResults Save()
	{

		switch (_Mode)
		{
		case enMode::EmptyMode:
		{
			if (IsEmpty()) {
				return enSaveResults::svFaildEmptyObject;
			}
		}

		case enMode::UpdateMode:
		{
			_Update();

			return enSaveResults::svSucceeded;

			break;
		}

		case enMode::AddNewMode:

			if (clsBankClient::IsClientExist(_AccountNumber)) {

				return enSaveResults::svFaildAccountNumberExists;
			}
			else {

				_AddNew();
				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;

			}


		}

		};

	static bool IsClientExist(string AccountNumber) {


		clsBankClient Client1 = clsBankClient::Find(AccountNumber);

		return !(Client1.IsEmpty());

	}

	
	bool Delete() {

		vector <clsBankClient> _vClients;

		_vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : _vClients) {

			if (C.AccountNumber() == _AccountNumber) {

				C._MarkedForDeleted = true;
				break;
			}

		}

		_SaveCleintsDataToFile(_vClients);


		*this = _GetEmptyClientObject();

		return true;


	}



	static clsBankClient GetAddNewClientObject(string AccountNumber) {

		return clsBankClient(enMode::AddNewMode,"", "", "", "", AccountNumber, "", 0);
	}


	static vector <clsBankClient> GetClientsList() {

		return _LoadClientsDataFromFile();
	}

	
	void Deposit(double Amount) {
		_AccountBalance += Amount;
		Save();
	}


	bool Withdraw(double Amount) {

		if (Amount > _AccountBalance) {
			return false;
		}
		else {
		_AccountBalance -= Amount;
		Save();
		}

	}


	bool Transfer(float Amount , clsBankClient &DestinationClient , string UserName) {

		if (Amount > AccountBalance) {
			return false;
		}

		Withdraw(Amount);
		DestinationClient.Deposit(Amount);
		_RegisterTransferLog(Amount, DestinationClient, UserName);

	}


	static vector <stTransferLogRecord> GetTransfersLogList() {
		vector <stTransferLogRecord> vTransferLogRecord;
		fstream MyFile;

		MyFile.open("TransferLog.txt", ios::in);

		if (MyFile.is_open()) {

			string Line;

			while (getline(MyFile, Line))
			{
				stTransferLogRecord TransferRecord = _ConvertTransferLogLineToRecord(Line);
				vTransferLogRecord.push_back(TransferRecord);

			}

			MyFile.close();

		}

		return vTransferLogRecord;

	}

	static double GetTotalBalances() {

		double TotalBalances = 0;

		vector <clsBankClient> vClients = _LoadClientsDataFromFile();


		for (clsBankClient& C : vClients) {


			TotalBalances += C.AccountBalance;

		}
   
		return TotalBalances;

	}


};
