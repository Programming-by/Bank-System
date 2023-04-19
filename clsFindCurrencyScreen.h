#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsString.h"
class clsFindCurrencyScreen : protected clsScreen
{

private:


    static void _PrintCurrency(clsCurrency Currency) {

        cout << "\nCurrency Card:\n";
        cout << "_____________________________\n";
        cout << "\nCountry    : " << Currency.Country();
        cout << "\nCode       : " << Currency.CurrencyCode();
        cout << "\nName       : " << Currency.CurrencyName();
        cout << "\nRate(1$) = : " << Currency.Rate();

        cout << "\n_____________________________\n";

    }
    
    static void _ShowResults(clsCurrency Currency) {

        if (!Currency.IsEmpty()) {

            cout << "\n Currency Found :-) \n";

            _PrintCurrency(Currency);
        }
        else {

            cout << "\n Currency Is Not Found :-( \n";
        }

    }

public:

	static void ShowFindCurrencyScreen() {


        _DrawScreenHeader("\t Find Currency Screen");

        cout << "\nFind By: [1] Code or [2] Country ? ";

        short Answer = 1;

        cin >> Answer;

        if (Answer == 1) {

            string CurrencyCode = "";

            cout << "\nPlease Enter Currency Code: ";

            CurrencyCode = clsInputValidate::ReadString();

            clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);

            _ShowResults(Currency);


        }
        else {
            string Country = "";

            cout << "\nPlease Enter Country Name: ";


            Country = clsInputValidate::ReadString();

            clsCurrency Currency = clsCurrency::FindByCountry(Country);

            _ShowResults(Currency);
        }

	}


};

