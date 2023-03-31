#pragma once

#include<iostream>
#include<string>
#include"Date.h"
using namespace std;
/************************************************************************************************************************/
class Money                         // клас Гроші - інформація про транзакції: дата проведення операції, сума, стаття доходів/витрат    
{
protected:
    Date day;
    double summ;
    string cost;
public:
    Money();                                // коструктор з параметрами
    void Set_day(int dd, int mm, int yyyy); // сеттер - введення дати транзакції
    void Set_summ(double value);            // сеттер - введення суми транзакції
    void Set_cost(string cost);             // сеттер - введення статті доходів/витрат по транзакції
    int Get_day()const;                     // геттер - отримату дату транзакції
    double Get_summ()const;                 // геттер - отримату суму транзакції
    string Get_cost()const;                 // геттер - отримату статтю  доходів/витрат по транзакції
    friend ostream& operator<<(ostream& out, const Money& temp);    // перевантаження оператора << (для запису в файл, дружня функція)
    friend istream& operator>>(istream& in, Money& temp);           // перевантаження оператора >> (для зчитування за файлу, дружня функція)
};
/************************************************************************************************************************/
