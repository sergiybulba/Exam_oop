#pragma once

#include"MoveMoney.h"
//using namespace std;

/************************************************************************************************************************/
class Cards                             // ���������� ���� - ������
{
protected:
    string valuta;          // ������ ������
    string bank;            // ����-������
    MoveMoney* Balance_in;  // ������� �� ������ �� ������� ������
    MoveMoney* Input;       // ����������� �����
    MoveMoney* Cashflow;    // ������� �����

public:
    Cards(string bank);  // ����������� � �����������
    void Set_input_balance();       // ������ - �������� ������� �� ������ �� ������� ������ � ���������
    void Set_input_money();         // ������ - �������� ���������� �� ������  � ���������
    void Set_output_money();        // ������ - �������� ������ �� ������  � ���������

    void Set_balance_money_from_file(string path);      // ����� - ����������� ������� ����� �� ������ � txt-�����
    void Set_input_money_from_file(string path);        // ����� - ����������� ���� ����� ���������� �� ��������� ������� � txt-����� 
    void Set_output_money_from_file(string path);       // ����� - ����������� ���� ����� ������ � ���������� �������� � txt-����� 

    void Entering(Money& temp);     // ���������� ������ - �������� ��������� ���� ��� ���� �� ���� ����������
    string Get_bank() const;        // ������ - �������� ����� �����-������� ������

    void Generate_report(Date data, int period, int numbercard);     // ����� - ���������� ��� �� ������� ������ �� �����
    void Generate_rating(Date data, int period, int numbercard);     // ����� - ���������� �������� ��� �� ����. ������� ������ � ����� ������ �� �����

    virtual ~Cards() = 0;           // ����� ���������� ����������
};
//------------------------------------------------------------------------------------------------------------------------
class Debitcard : public Cards          // ������� ���� - ������� ������
{
public:
    Debitcard(string bank) : Cards(bank) {}
    ~Debitcard() override {}
};
//------------------------------------------------------------------------------------------------------------------------
class Creditcard : public Cards         // ������� ���� - �������� ������
{
private:
    int limit;      // ��������� ��� �� ������

public:
    Creditcard(string bank, int limit) : Cards(bank), limit(limit) {}
    ~Creditcard() override {}
};
/************************************************************************************************************************/