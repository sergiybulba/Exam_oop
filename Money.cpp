

#include"Money.h"

/************************************************************************************************************************/

Money::Money() : summ(0), cost("") {}           // ���������� � �����������

void Money::Set_day(int dd, int mm, int yyyy)   // ������ - �������� ���� ����������
    {
        this->day.dd = dd;
        this->day.mm = mm;
        this->day.yyyy = yyyy;
    }

void Money::Set_summ(double value)   // ������ - �������� ���� ����������
    {
        this->summ = value;
    }

void Money::Set_cost(string cost)   // ������ - �������� ����� ������/������ �� ����������
    {
        this->cost = cost;
    }

int Money::Get_day()const           // ������ - �������� ���� ����������
    {
        return this->day.dd;
    }

double Money::Get_summ()const      // ������ - �������� ���� ����������
    {
        return this->summ;
    }

string Money :: Get_cost()const      // ������ - �������� ������  ������/������ �� ����������
    {
        return this->cost;
    }

/************************************************************************************************************************/