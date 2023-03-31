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
class MoveMoney                             // ����������� ���� - ��� ����� �� �������
{
protected:
    vector<Money> table;            // ���� ����� � ������������ � ������ �������

public:
    void Set(Money summ);            // ������ - ���������� ���������� � ����� �������
    virtual void Load_transaction_txt_file(string path);        // ����� - ����������� ���� ����� � ������������ � txt-����� 
    virtual void Report(Date data, int period, int numbercard, string bank, string typecard);  // ����� - ���������� ��� �� �������� � ����������� � txt-����
    virtual void Max_category(Date data, int period, int numbercard, string bank, string typecard);  // ����� - ���������� ������� �� ������������ ��������� ������ � ����������� � txt-����
    virtual void Max_Expense(Date data, int period, int numbercard, string bank, string typecard);  // ����� - ���������� ������� �� ������������ �������� � ����������� � txt-����
};
//------------------------------------------------------------------------------------------------------------------------

class Enter_money : public MoveMoney        // ������� ���� - ���������� ��� ����� � ��������/��������� ����� �� �������
{
public:
    void Load_transaction_txt_file(string path) override;        // ����� - ����������� ���� ����� � ������������ � txt-����� 
    void Report(Date data, int period, int numbercard, string bank, string typecard) override;   // ����� - ���������� ��� �� �������� � ����������� � txt-����
    void Max_Expense(Date data, int period, int numbercard, string bank, string typecard) override;  // ����� - ���������� ������� �� ������������ �������� � ����������� � txt-����
    void Max_category(Date data, int period, int numbercard, string bank, string typecard) override; // ����� - ���������� ������� �� ������������ ������� ������ � ����������� � txt-����
};
/************************************************************************************************************************/