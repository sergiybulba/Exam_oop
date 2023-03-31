#pragma once

#include<iostream>
#include<string>
#include"Date.h"
using namespace std;
/************************************************************************************************************************/
class Money                         // ���� ����� - ���������� ��� ����������: ���� ���������� ��������, ����, ������ ������/������    
{
protected:
    Date day;
    double summ;
    string cost;
public:
    Money();                                // ���������� � �����������
    void Set_day(int dd, int mm, int yyyy); // ������ - �������� ���� ����������
    void Set_summ(double value);            // ������ - �������� ���� ����������
    void Set_cost(string cost);             // ������ - �������� ����� ������/������ �� ����������
    int Get_day()const;                     // ������ - �������� ���� ����������
    double Get_summ()const;                 // ������ - �������� ���� ����������
    string Get_cost()const;                 // ������ - �������� ������  ������/������ �� ����������
    friend ostream& operator<<(ostream& out, const Money& temp);    // �������������� ��������� << (��� ������ � ����, ������ �������)
    friend istream& operator>>(istream& in, Money& temp);           // �������������� ��������� >> (��� ���������� �� �����, ������ �������)
};
/************************************************************************************************************************/
