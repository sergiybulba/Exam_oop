/* OOP  exam, 04.03.2023

task � 3:
������� ������� ��������� ������������� ���������.
������� ������ ���� ��� ���������:
- �������� ����� �������� � ���� (���������/���������);
- ���������� �������� � ����;
- �������� ������. ����� ������� �������� ����� �������;
- ���������� ���� �� ��������� �� ����������:
    � ����;
    � �������;
    � �����.
-  ���������� �������� �� ������������� ������:
    � ���-3 ������:
        - �������;
        - �����.
    � ���-3 ��������:
        - �������;
        - �����.
- ���������� ���� � �������� � ����.*/

#include<iostream>
#include"Date.h"
#include"Money.h"
#include"MoveMoney.h"
#include"Cards.h"
using namespace std;
/************************************************************************************************************************/
ostream& operator<<(ostream& out, const Money& temp);   // ��������� �������
istream& operator>>(istream& in, Money& temp);
/************************************************************************************************************************/

int main()
{
    int index, index2;

    cout << "Program \"Examination \"Personal finances\"" << endl << endl;

    do {
        cout << "How much cards do you have? ";     // ����� ���������� ��� ������� ������ � �������
        cin >> index;
        if (index < 1)
            cout << "Error! Try again" << endl;
    } while (index < 1 );
    
    Cards** Wallet = new Cards*[index];             // ���������� ������ � ������ � �������

    for (int i = 0; i < index; ++i)
    {
        do {
            cout << endl << "Choose the card type #" << (i + 1) << " (1 - debit, 2 - credit): ";  // ���� ���� �����: debit or credit
            cin >> index2;
            if (index2 < 1 || index2 > 2)
                cout << "Error! Try again" << endl;
        } while (index2 < 1 || index2 > 2);

        switch (index2)
        {
        case 1:
            Wallet[i] = new Debitcard("Privatbank");            // ��������� ���������� �� ���� runtime - �������� ���'�� �� debitcard
            break;
        case 2:
            Wallet[i] = new Creditcard("Monobank", 50000);      // ��������� ���������� �� ���� runtime - �������� ���'�� �� creditcard
            break;
        }
    }

    string path_dt_balance = "DebitCard_balance.txt";       // ������ ����� ��� ������������ � ��� ���������� ��� ��� �����
    string path_dt_input = "DebitCard_input.txt";
    string path_dt_output = "DebitCard_output.txt";
    string path_ct_balance = "CreditCard_balance.txt";
    string path_ct_input = "CreditCard_input.txt";
    string path_ct_output = "CreditCard_output.txt";

    cout << endl << "WARNING! Info about the movement of money only for January 2023! " << endl;   // ���������� ��� ��� ����� �� ������� - ����� � ����� ������ �����

    for (int i = 0; i < index; ++i)             // ���� ��� �������� ���� � ���� ����� ��� ��� ����� �� �������
    {
        cout << endl << "For card " << typeid(*Wallet[i]).name() << ", bank '" << Wallet[i]->Get_bank() << "': " << endl << endl;

        cout << "To download (recommended) movement money from file (1) or enter manually (2)? ";  // ������������� ����������� � ����� (��� �����쳿 ����)
        cin >> index2;

        if (index2 == 1 && (typeid(*Wallet[i]) == typeid(Debitcard)))  // ������������ ���� ��� ������� ������ � �����
        {
            Wallet[i]->Set_balance_money_from_file(path_dt_balance);       // ����������� ������� ������� �� ���������� �������
            Wallet[i]->Set_input_money_from_file(path_dt_input);          // ����������� ����������� ����� �� ��������� �������
            Wallet[i]->Set_output_money_from_file(path_dt_output);        // ����������� ������� ����� � ���������� �������
            cout << endl << "Your debit card info was downloaded successfully. " << endl;
        }
        else if (index2 == 1 && (typeid(*Wallet[i]) == typeid(Creditcard)))  // ������������ ���� ��� �������� ������ � �����
        {
            Wallet[i]->Set_balance_money_from_file(path_ct_balance);       // ����������� ������� ������� �� ���������� �������
            Wallet[i]->Set_input_money_from_file(path_ct_input);          // ����������� ����������� ����� �� ��������� �������
            Wallet[i]->Set_output_money_from_file(path_ct_output);        // ����������� ������� ����� � ���������� �������
            cout << endl << "Your credit card info was downloaded successfully. " << endl;
        }
        else
        {                                               // �������� ���������� ��� ��� ����� �� ������ � ���������
            Wallet[i]->Set_input_balance();             // ������� �������                
            Wallet[i]->Set_input_money();               // ����������� ����� 
            Wallet[i]->Set_output_money();              // ������� �����
        }
    }

    cout << endl << "The list of your cards: " << endl << endl;         // ��������� ������ ������ � �������
    for (int i = 0; i < index; ++i)
    {
        cout << "Card #" << i + 1 << ": " << typeid(*Wallet[i]).name() << ", bank '" << Wallet[i]->Get_bank() << "'; " << endl;
    }

    do          // ���� ��� ���������� ����
    {
        do {                                                            // ���� ������ ��� ���������� ����
            cout << endl << "Enter the card number for generating reports: ";
            cin >> index2;
            if (index2 < 1 || index2 > index)
                cout << "Error! Try again" << endl;
        } while (index2 < 1 || index2 > index);

        Date data; int period;

        cout << endl << "Enter the starting date to generate the expense report (__ january 2023): " << endl << "dd: ";
        do {
            cin >> data.dd;                                 // �������� ��������� ���� ��� ���������� ���� ��� �������
            if (data.dd < 1 || data.dd > 31)
                cout << "Error! Try again" << endl << "dd: ";
        } while (data.dd < 1 || data.dd > 31);
        data.mm = 1; data.yyyy = 2023;

        cout << endl << "Enter the period (days) to generate the expense report: "; // �������� ������, �� ���� ��������� ��� ��� �������
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

        Wallet[index2 - 1]->Generate_report(data, period, index2);      // ���������� ���� ��� ������� ��  ������� ������


        cout << endl << "Enter the starting date to generate the rating (__ january 2023): " << endl << "dd: ";
        do {
            cin >> data.dd;                                     // �������� ��������� ���� ��� ���������� ��������
            if (data.dd < 1 || data.dd > 31)
                cout << "Error! Try again" << endl;
        } while (data.dd < 1 || data.dd > 31);
        data.mm = 1; data.yyyy = 2023;

        do {
            cout << endl << "Enter the period (days) to generate the rating (3 max expenses&costs): "; // �������� ������, �� ���� ��������� �������
            cout << endl << "(1 - one week, 2 - one month): ";
            cin >> period;
            if (period < 1 || period > 2)
                cout << "Error! Try again" << endl;
        } while (period < 1 || period > 2);

        if (period == 1)
            period = 7;
        else if (period == 2)
            period = 31;

        Wallet[index2 - 1]->Generate_rating(data, period, index2);        // ���������� �������� ��� 3 ���������� ������� � 3 ���������� ������� ������

        // ���������� ���������� ����?												

        cout << endl << endl << "Continue? ('1' for 'yes' or '2' for 'not'): ";
        cin >> index2;
        cout << "================================================================================" << endl << endl;
    } while (index2 == 1);

    cout << endl << endl << "Sorry, but your wallet is lost ..." << endl << endl;   // ����� ��������
    return 0;
}
/************************************************************************************************************************/
ostream& operator<<(ostream& out, const Money& temp)                                // �������������� ��������� << (��� ������ � ����, ������ �������)
{
    out << "\tCost: " << temp.cost << "\tSumm: " << temp.summ << endl;
    return out;
}

istream& operator>>(istream& in, Money& temp)                                       // �������������� ��������� >> (��� ���������� �� �����, ������ �������)
{
    in >> temp.day.dd >> temp.day.mm >> temp.day.yyyy >> temp.summ >> temp.cost;
    return in;
}
/************************************************************************************************************************/

