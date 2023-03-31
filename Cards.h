#pragma once

#include"MoveMoney.h"
//using namespace std;

/************************************************************************************************************************/
class Cards                             // астрактний клас - Картки
{
protected:
    string valuta;          // валюта картки
    string bank;            // банк-емітент
    MoveMoney* Balance_in;  // залишок на картці на початок періоду
    MoveMoney* Input;       // надходження коштів
    MoveMoney* Cashflow;    // витрати коштів

public:
    Cards(string bank);  // конструктор з параметрами
    void Set_input_balance();       // сеттер - введення залишку на картці на початок періоду з клавіатури
    void Set_input_money();         // сеттер - введення надходжень на картці  з клавіатури
    void Set_output_money();        // сеттер - введення витрат на картці  з клавіатури

    void Set_balance_money_from_file(string path);      // метод - завантажити залишок коштів на картці з txt-файлу
    void Set_input_money_from_file(string path);        // метод - завантажити базу даних надходжень на картковий рахунок з txt-файлу 
    void Set_output_money_from_file(string path);       // метод - завантажити базу даних витрат з карткового рахуноку з txt-файлу 

    void Entering(Money& temp);     // додатковий сеттер - введення однотипної інфо про дату та суму транзакції
    string Get_bank() const;        // геттер - отримати назву банка-емітента картки

    void Generate_report(Date data, int period, int numbercard);     // метод - сформувати звіт по статтях витрат за період
    void Generate_rating(Date data, int period, int numbercard);     // метод - сформувати рейтинги звіт по макс. статтях витрат і сумах витрат за період

    virtual ~Cards() = 0;           // чисто віртуальний деструктор
};
//------------------------------------------------------------------------------------------------------------------------
class Debitcard : public Cards          // дочірній клас - Дебітова картка
{
public:
    Debitcard(string bank) : Cards(bank) {}
    ~Debitcard() override {}
};
//------------------------------------------------------------------------------------------------------------------------
class Creditcard : public Cards         // дочірній клас - Кредитна картка
{
private:
    int limit;      // кредитний ліміт на картці

public:
    Creditcard(string bank, int limit) : Cards(bank), limit(limit) {}
    ~Creditcard() override {}
};
/************************************************************************************************************************/