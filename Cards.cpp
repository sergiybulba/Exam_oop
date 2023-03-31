#include"Cards.h"

/************************************************************************************************************************/
Cards::Cards(string bank) : valuta("UAH"), bank(bank)  // конструктор з параметрами
    {
        Balance_in = nullptr;
        Input = nullptr;
        Cashflow = nullptr;
    }

void Cards::Set_input_balance()            // сеттер - введення залишку на картці на початок періоду з клавіатури
    {
        cout << endl << "Entering input balance: " << endl;
        Money temp;
        Entering(temp);
        temp.Set_cost("Input_balance");

        Balance_in = new Enter_money;
        Balance_in->Set(temp);
    }

void Cards::Set_input_money()            // сеттер - введення надходжень на картці  з клавіатури
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

            // продовжити ?												
            cout << endl << endl << "Do you have another inputs? ('1' for 'yes' or other symbol for 'not'): ";
            cin >> value;

        } while (value == 1);
    }

void Cards::Set_output_money()            // сеттер - введення витрат на картці  з клавіатури
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

            // продовжити ?												
            cout << endl << endl << "Do you have another costs? ('1' for 'yes' or other symbol for 'not'): ";
            cin >> value;

        } while (value == 1);
    }

void Cards::Set_balance_money_from_file(string path)       // метод - завантажити залишок коштів на картці з txt-файлу
{
    Balance_in = new Enter_money;
    Balance_in->Load_transaction_txt_file(path);
}

void Cards::Set_input_money_from_file(string path)       // метод - завантажити базу даних надходжень на картковий рахунок з txt-файлу 
{
    Input = new Enter_money;
    Input->Load_transaction_txt_file(path);
}

void Cards::Set_output_money_from_file(string path)    // метод - завантажити базу даних витрат з карткового рахуноку з txt-файлу  
{
    Cashflow = new Enter_money;
    Cashflow->Load_transaction_txt_file(path);
}

void Cards::Entering(Money& temp)     // додатковий сеттер - введення однотипної інфо про дату та суму транзакції
    {
        int value;
        cout << endl << "Enter the date (__ january 2023): " << endl << "dd: ";
        do {
            cin >> value;                                     // введення дати 
            if (value < 1 || value > 31)
                cout << "Error! Try again" << endl;
        } while (value < 1 || value > 31);
        temp.Set_day(value, 1, 2023);

        cout << "Enter the cost amount: ";      // введення суми
        cin >> value;
        temp.Set_summ(value);
    }

string Cards::Get_bank() const     // геттер - отримати назву банка-емітента картки
    {
        return this->bank;
    }

void Cards::Generate_report(Date data, int period, int numbercard)     // метод - сформувати звіт по статтях витрат за період
    {
        Cashflow->Report(data, period, numbercard, this->bank, typeid(*this).name());
        cout << endl << "You can view generated reports in the file 'Card_reports.txt'." << endl << endl;
    }

void Cards::Generate_rating(Date data, int period, int numbercard)     // метод - сформувати рейтинги звіт по макс. статтях витрат і сумах витрат за період
    {
        Cashflow->Max_category(data, period, numbercard, this->bank, typeid(*this).name());
        Cashflow->Max_Expense(data, period, numbercard, this->bank, typeid(*this).name());
        cout << endl << "You can view generated ratings in the file 'Card_reports.txt'." << endl << endl;
    }

Cards::~Cards()                     // реалізація чисто віртуального деструктора
{
    delete Balance_in;
    delete Input;
    delete Cashflow;
};
/************************************************************************************************************************/