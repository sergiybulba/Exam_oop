/* OOP  exam, 04.03.2023

task № 3:
Створіть систему управління персональними фінансами.
Система мусить мати такі можливості:
- Наявність різних гаманців і карт (дебетових/кредитних);
- Поповнення гаманців і карт;
- Внесення витрат. Кожна витрата належить певній категорії;
- Формування звітів за витратами та категоріями:
    • день;
    • тиждень;
    • місяць.
-  Формування рейтингів за максимальними сумами:
    • ТОП-3 витрат:
        - тиждень;
        - місяць.
    • ТОП-3 категорій:
        - тиждень;
        - місяць.
- Збереження звітів і рейтингів у файл.*/

#include<iostream>
#include"Date.h"
#include"Money.h"
#include"MoveMoney.h"
#include"Cards.h"
using namespace std;
/************************************************************************************************************************/
ostream& operator<<(ostream& out, const Money& temp);   // прототипи функцій
istream& operator>>(istream& in, Money& temp);
/************************************************************************************************************************/

int main()
{
    int index, index2;

    cout << "Program \"Examination \"Personal finances\"" << endl << endl;

    do {
        cout << "How much cards do you have? ";     // запит інформації про кількість карток в гаманці
        cin >> index;
        if (index < 1)
            cout << "Error! Try again" << endl;
    } while (index < 1 );
    
    Cards** Wallet = new Cards*[index];             // формування масиву з карток в гаманці

    for (int i = 0; i < index; ++i)
    {
        do {
            cout << endl << "Choose the card type #" << (i + 1) << " (1 - debit, 2 - credit): ";  // вибір типу карти: debit or credit
            cin >> index2;
            if (index2 < 1 || index2 > 2)
                cout << "Error! Try again" << endl;
        } while (index2 < 1 || index2 > 2);

        switch (index2)
        {
        case 1:
            Wallet[i] = new Debitcard("Privatbank");            // динамічний поліморфізм на етапі runtime - виділення пам'яті під debitcard
            break;
        case 2:
            Wallet[i] = new Creditcard("Monobank", 50000);      // динамічний поліморфізм на етапі runtime - виділення пам'яті під creditcard
            break;
        }
    }

    string path_dt_balance = "DebitCard_balance.txt";       // перелік файлів для завантаження з них інформації про рух коштів
    string path_dt_input = "DebitCard_input.txt";
    string path_dt_output = "DebitCard_output.txt";
    string path_ct_balance = "CreditCard_balance.txt";
    string path_ct_input = "CreditCard_input.txt";
    string path_ct_output = "CreditCard_output.txt";

    cout << endl << "WARNING! Info about the movement of money only for January 2023! " << endl;   // інформація про рух коштів по картках - тільки в межах одного місяця

    for (int i = 0; i < index; ++i)             // цикл для введення інфо в базу даних про рух коштів на картках
    {
        cout << endl << "For card " << typeid(*Wallet[i]).name() << ", bank '" << Wallet[i]->Get_bank() << "': " << endl << endl;

        cout << "To download (recommended) movement money from file (1) or enter manually (2)? ";  // рекомендовано завантажити з файлу (для економії часу)
        cin >> index2;

        if (index2 == 1 && (typeid(*Wallet[i]) == typeid(Debitcard)))  // завантаження інфо для дебітової картки з файлів
        {
            Wallet[i]->Set_balance_money_from_file(path_dt_balance);       // завантажити вхідний залишок на картковому рахунку
            Wallet[i]->Set_input_money_from_file(path_dt_input);          // завантажити надходження коштів на картковий рахунок
            Wallet[i]->Set_output_money_from_file(path_dt_output);        // завантажити витрати коштів з карткового рахунку
            cout << endl << "Your debit card info was downloaded successfully. " << endl;
        }
        else if (index2 == 1 && (typeid(*Wallet[i]) == typeid(Creditcard)))  // завантаження інфо для кредитної картки з файлів
        {
            Wallet[i]->Set_balance_money_from_file(path_ct_balance);       // завантажити вхідний залишок на картковому рахунку
            Wallet[i]->Set_input_money_from_file(path_ct_input);          // завантажити надходження коштів на картковий рахунок
            Wallet[i]->Set_output_money_from_file(path_ct_output);        // завантажити витрати коштів з карткового рахунку
            cout << endl << "Your credit card info was downloaded successfully. " << endl;
        }
        else
        {                                               // введення інформації про рух коштів по картці з клавіатури
            Wallet[i]->Set_input_balance();             // вхідний залишок                
            Wallet[i]->Set_input_money();               // надходження коштів 
            Wallet[i]->Set_output_money();              // витрати коштів
        }
    }

    cout << endl << "The list of your cards: " << endl << endl;         // виведення списку карток в гаманці
    for (int i = 0; i < index; ++i)
    {
        cout << "Card #" << i + 1 << ": " << typeid(*Wallet[i]).name() << ", bank '" << Wallet[i]->Get_bank() << "'; " << endl;
    }

    do          // цикл для формування звітів
    {
        do {                                                            // вибір картки для формування звітів
            cout << endl << "Enter the card number for generating reports: ";
            cin >> index2;
            if (index2 < 1 || index2 > index)
                cout << "Error! Try again" << endl;
        } while (index2 < 1 || index2 > index);

        Date data; int period;

        cout << endl << "Enter the starting date to generate the expense report (__ january 2023): " << endl << "dd: ";
        do {
            cin >> data.dd;                                 // введення початкової дати для формування звіту про витрати
            if (data.dd < 1 || data.dd > 31)
                cout << "Error! Try again" << endl << "dd: ";
        } while (data.dd < 1 || data.dd > 31);
        data.mm = 1; data.yyyy = 2023;

        cout << endl << "Enter the period (days) to generate the expense report: "; // введення періоду, за який формувати звіт про витрати
        do {
            cout << endl << "(1 - one day, 2 - one week, 3 - one month): ";
            cin >> period;
            if (period < 1 || period > 3)
                cout << "Error! Try again" << endl;
        } while (period < 1 || period > 3);

        if (period == 2)
            period = 7;
        else if (period == 3)
            period = 31;

        Wallet[index2 - 1]->Generate_report(data, period, index2);      // формування звіту про витрати по  поточній картці


        cout << endl << "Enter the starting date to generate the rating (__ january 2023): " << endl << "dd: ";
        do {
            cin >> data.dd;                                     // введення початкової дати для формування рейтингів
            if (data.dd < 1 || data.dd > 31)
                cout << "Error! Try again" << endl;
        } while (data.dd < 1 || data.dd > 31);
        data.mm = 1; data.yyyy = 2023;

        do {
            cout << endl << "Enter the period (days) to generate the rating (3 max expenses&costs): "; // введення періоду, за який формувати рейтинг
            cout << endl << "(1 - one week, 2 - one month): ";
            cin >> period;
            if (period < 1 || period > 2)
                cout << "Error! Try again" << endl;
        } while (period < 1 || period > 2);

        if (period == 1)
            period = 7;
        else if (period == 2)
            period = 31;

        Wallet[index2 - 1]->Generate_rating(data, period, index2);        // формування рейтингу про 3 максимальні витрати і 3 максимальні категорії витрат

        // продовжити формування звітів?												

        cout << endl << endl << "Continue? ('1' for 'yes' or '2' for 'not'): ";
        cin >> index2;
        cout << "================================================================================" << endl << endl;
    } while (index2 == 1);

    cout << endl << endl << "Sorry, but your wallet is lost ..." << endl << endl;   // кінець програми
    return 0;
}
/************************************************************************************************************************/
ostream& operator<<(ostream& out, const Money& temp)                                // перевантаження оператора << (для запису в файл, дружня функція)
{
    out << "\tCost: " << temp.cost << "\tSumm: " << temp.summ << endl;
    return out;
}

istream& operator>>(istream& in, Money& temp)                                       // перевантаження оператора >> (для зчитування за файлу, дружня функція)
{
    in >> temp.day.dd >> temp.day.mm >> temp.day.yyyy >> temp.summ >> temp.cost;
    return in;
}
/************************************************************************************************************************/

