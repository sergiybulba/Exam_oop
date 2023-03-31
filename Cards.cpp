#include"Cards.h"

/************************************************************************************************************************/
Cards::Cards(string bank) : valuta("UAH"), bank(bank)  // ����������� � �����������
    {
        Balance_in = nullptr;
        Input = nullptr;
        Cashflow = nullptr;
    }

void Cards::Set_input_balance()            // ������ - �������� ������� �� ������ �� ������� ������ � ���������
    {
        cout << endl << "Entering input balance: " << endl;
        Money temp;
        Entering(temp);
        temp.Set_cost("Input_balance");

        Balance_in = new Enter_money;
        Balance_in->Set(temp);
    }

void Cards::Set_input_money()            // ������ - �������� ���������� �� ������  � ���������
    {
        cout << endl << "Entering input funds: " << endl;
        int value;
        Input = new Enter_money;
        Money temp;
        do
        {
            Entering(temp);
            temp.Set_cost("Input_money");

            Input->Set(temp);

            // ���������� ?												
            cout << endl << endl << "Do you have another inputs? ('1' for 'yes' or other symbol for 'not'): ";
            cin >> value;

        } while (value == 1);
    }

void Cards::Set_output_money()            // ������ - �������� ������ �� ������  � ���������
    {
        cout << endl << "Entering output costs: " << endl;
        int value; string cost;
        Cashflow = new Enter_money;
        Money temp;

        do
        {
            Entering(temp);
            cout << "Enter the cost item: ";
            cin.ignore(10, '\n');
            getline(cin, cost);
            temp.Set_cost(cost);

            Cashflow->Set(temp);

            // ���������� ?												
            cout << endl << endl << "Do you have another costs? ('1' for 'yes' or other symbol for 'not'): ";
            cin >> value;

        } while (value == 1);
    }

void Cards::Set_balance_money_from_file(string path)       // ����� - ����������� ������� ����� �� ������ � txt-�����
{
    Balance_in = new Enter_money;
    Balance_in->Load_transaction_txt_file(path);
}

void Cards::Set_input_money_from_file(string path)       // ����� - ����������� ���� ����� ���������� �� ��������� ������� � txt-����� 
{
    Input = new Enter_money;
    Input->Load_transaction_txt_file(path);
}

void Cards::Set_output_money_from_file(string path)    // ����� - ����������� ���� ����� ������ � ���������� �������� � txt-�����  
{
    Cashflow = new Enter_money;
    Cashflow->Load_transaction_txt_file(path);
}

void Cards::Entering(Money& temp)     // ���������� ������ - �������� ��������� ���� ��� ���� �� ���� ����������
    {
        int value;
        cout << endl << "Enter the date (__ january 2023): " << endl << "dd: ";
        do {
            cin >> value;                                     // �������� ���� 
            if (value < 1 || value > 31)
                cout << "Error! Try again" << endl;
        } while (value < 1 || value > 31);
        temp.Set_day(value, 1, 2023);

        cout << "Enter the cost amount: ";      // �������� ����
        cin >> value;
        temp.Set_summ(value);
    }

string Cards::Get_bank() const     // ������ - �������� ����� �����-������� ������
    {
        return this->bank;
    }

void Cards::Generate_report(Date data, int period, int numbercard)     // ����� - ���������� ��� �� ������� ������ �� �����
    {
        Cashflow->Report(data, period, numbercard, this->bank, typeid(*this).name());
        cout << endl << "You can view generated reports in the file 'Card_reports.txt'." << endl << endl;
    }

void Cards::Generate_rating(Date data, int period, int numbercard)     // ����� - ���������� �������� ��� �� ����. ������� ������ � ����� ������ �� �����
    {
        Cashflow->Max_category(data, period, numbercard, this->bank, typeid(*this).name());
        Cashflow->Max_Expense(data, period, numbercard, this->bank, typeid(*this).name());
        cout << endl << "You can view generated ratings in the file 'Card_reports.txt'." << endl << endl;
    }

Cards::~Cards()                     // ��������� ����� ����������� �����������
{
    delete Balance_in;
    delete Input;
    delete Cashflow;
};
/************************************************************************************************************************/