#pragma once

#include<iostream>
#include<vector>
#include<algorithm>
#include<fstream>
#include<string>
#include"Money.h"
#include"Date.h"
using namespace std;

/************************************************************************************************************************/
class MoveMoney                             // батьківський клас - Рух коштів по рахунку
{
protected:
    vector<Money> table;            // бази даних з транзакціями у вигляді вектору

public:
    void Set(Money summ);            // сеттер - добавлення транзакції в кінець вектору
    virtual void Load_transaction_txt_file(string path);        // метод - завантажити базу даних з транзакціями з txt-файлу 
    virtual void Report(Date data, int period, int numbercard, string bank, string typecard);  // метод - сформувати звіт по витратах і завантажити в txt-файл
    virtual void Max_category(Date data, int period, int numbercard, string bank, string typecard);  // метод - сформувати рейтинг по максимальних категоріях витрат і завантажити в txt-файл
    virtual void Max_Expense(Date data, int period, int numbercard, string bank, string typecard);  // метод - сформувати рейтинг по максимальних витратах і завантажити в txt-файл
};
//------------------------------------------------------------------------------------------------------------------------

class Enter_money : public MoveMoney        // дочірній клас - формування баз даних з доходами/витратами коштів по рахунку
{
public:
    void Load_transaction_txt_file(string path) override;        // метод - завантажити базу даних з транзакціями з txt-файлу 
    void Report(Date data, int period, int numbercard, string bank, string typecard) override;   // метод - сформувати звіт по витратах і завантажити в txt-файл
    void Max_Expense(Date data, int period, int numbercard, string bank, string typecard) override;  // метод - сформувати рейтинг по максимальних витратах і завантажити в txt-файл
    void Max_category(Date data, int period, int numbercard, string bank, string typecard) override; // метод - сформувати рейтинг по максимальних статтях витрат і завантажити в txt-файл
};
/************************************************************************************************************************/