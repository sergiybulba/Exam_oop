

#include"Money.h"

/************************************************************************************************************************/

Money::Money() : summ(0), cost("") {}           // коструктор з параметрами

void Money::Set_day(int dd, int mm, int yyyy)   // сеттер - введення дати транзакції
    {
        this->day.dd = dd;
        this->day.mm = mm;
        this->day.yyyy = yyyy;
    }

void Money::Set_summ(double value)   // сеттер - введення суми транзакції
    {
        this->summ = value;
    }

void Money::Set_cost(string cost)   // сеттер - введення статті доходів/витрат по транзакції
    {
        this->cost = cost;
    }

int Money::Get_day()const           // геттер - отримату дату транзакції
    {
        return this->day.dd;
    }

double Money::Get_summ()const      // геттер - отримату суму транзакції
    {
        return this->summ;
    }

string Money :: Get_cost()const      // геттер - отримату статтю  доходів/витрат по транзакції
    {
        return this->cost;
    }

/************************************************************************************************************************/