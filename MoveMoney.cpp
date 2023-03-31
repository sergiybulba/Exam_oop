
#include"MoveMoney.h"


/************************************************************************************************************************/
    void MoveMoney::Set(Money summ)            // ������ - ���������� ���������� � ����� �������												
    {
        table.push_back(summ);
    }

    void MoveMoney::Load_transaction_txt_file(string path) {}       // ����� - ����������� ���� ����� � ������������ � txt-����� 

    void MoveMoney::Report(Date data, int period, int numbercard, string bank, string typecard) {} // ����� - ���������� ��� �� �������� � ����������� � txt-����

    void MoveMoney::Max_category(Date data, int period, int numbercard, string bank, string typecard) {} // ����� - ���������� ������� �� ������������ ��������� ������ � ����������� � txt-����

    void MoveMoney::Max_Expense(Date data, int period, int numbercard, string bank, string typecard) {} // ����� - ���������� ������� �� ������������ �������� � ����������� � txt-����

//------------------------------------------------------------------------------------------------------------------------

    void Enter_money:: Load_transaction_txt_file(string path)         // ����� - ����������� ���� ����� � ������������ � txt-����� 
    {
        fstream file;
        file.open(path, fstream::in | fstream::out | fstream::app);     // ������� ����

        if (!file.is_open())
        {
            cout << "Error, file isn't open." << endl;
        }
        else
        {
            Money temp;
            while (true)
            {
                file >> temp;       // ������� ����� 
                if (file.eof())
                    break;
                Set(temp);          // �������� ����� ���� Money (transaction) � ������ 
            }
        }
        file.close();
    }

    void Enter_money::Report(Date data, int period, int numbercard, string bank, string typecard)    // ����� - ���������� ��� �� �������� � ����������� � txt-����
    {
        vector<Money> report;                               // ��������� ������ ���� ���� ����������� � ���������
        vector<Money>::iterator index = table.begin();      // �������� ������� ���� �����
        while (true)
        {
            if ((*index).Get_day() == data.dd)              // ����� ��������� ���� ���������, � ��� ���������� ���� �����
                break;
            ++index;
        }

        while ((*index).Get_day() < (data.dd + period))     // ���� ���������� ���������� �� ����� � ��������� ������
        {
            vector<Money>::iterator index2 = report.begin();    // �������� ��������� ���� �����
            for (; index2 != report.end(); ++index2)            // � ���� ���������� ��������� �� ������� ������
            {
                if ((*index).Get_cost() == (*index2).Get_cost())   // ���� ����� ���������� - ���� �������� �� ���� ����� ������     
                {
                    (*index2).Set_summ((*index2).Get_summ() + (*index).Get_summ());
                    break;
                }
            }
            if (index2 == report.end())     // ���� � ���������� ������ ���� ������ ������ ������� - �� ���������� �������� � ����� ���������� ������� 
            {
                report.push_back(*index);
            }
            if (++index == table.end())     // �������� �� ����� ��������� �������
                break;
        }


        string path = "Card_reports.txt";
        fstream file;
        file.open(path, fstream::in | fstream::out | fstream::app);     // ������� ���� � ������

        if (!file.is_open())
        {
            cout << "Error, file isn't open." << endl;
        }
        else                                                // ����� ���� � ����
        {
            file << "Expense report for card #" << numbercard << ", " << typecard
                << ", bank " << bank << ", for " << period << " day(s) since "
                << data.dd << "." << data.mm << "." << data.yyyy << ": " << endl << endl;
            vector<Money>::iterator index2 = report.begin();
            for (; index2 != report.end(); ++index2)
            {
                file << (*index2);                      // ���������� ���������� � ����������� ������� ��� ������� ��������� �� ����� ������
            }
            file << endl << endl;
        }
        file.close();
    }

    void Enter_money::Max_Expense(Date data, int period, int numbercard, string bank, string typecard)   // ����� - ���������� ������� �� ������������ �������� � ����������� � txt-����
    {
        vector<Money> report;                           // ��������� ������ ���� ���� ����������� � ���������
        vector<Money>::iterator index = table.begin();  // �������� ������� ���� �����
        while (true)
        {
            if ((*index).Get_day() == data.dd)          // ����� ��������� ���� ���������, � ��� ���������� ���� �����
                break;
            ++index;
        }

        while ((*index).Get_day() < (data.dd + period)) // ���� ���������� ���������� �� ����� � ��������� ������
        {
            report.push_back(*index);
            if (++index == table.end())
                break;
        }

        sort(report.begin(), report.end(), [](const Money& temp1, const Money& temp2)  // ���������� ���������� ������� � ������������ �� ���
            {
                return temp1.Get_summ() > temp2.Get_summ();
            });


        string path = "Card_reports.txt";
        fstream file;
        file.open(path, fstream::in | fstream::out | fstream::app);     // ������� ���� � ������

        if (!file.is_open())
        {
            cout << "Error, file isn't open." << endl;
        }
        else                        // ����� ���� � ����
        {
            file << "Expense report by the 3 largest summs for card #" << numbercard << ", " << typecard
                << ", bank " << bank << ", for " << period << " day(s) since " << data.dd << "." << data.mm
                << "." << data.yyyy << ": " << endl << endl;
            vector<Money>::iterator index2 = report.begin();
            for (; index2 < report.begin() + 3; ++index2)           // ��� ���������� ����������
            {
                file << (*index2);
            }
            file << endl << endl;
        }
        file.close();               // ������� ����
    }

    void Enter_money::Max_category(Date data, int period, int numbercard, string bank, string typecard)  // ����� - ���������� ������� �� ������������ ������� ������ � ����������� � txt-����
    {
        vector<Money> report;                           // ��������� ������ ���� ���� ����������� � ���������
        vector<Money>::iterator index = table.begin();  // �������� ������� ���� �����
        while (true)
        {
            if ((*index).Get_day() == data.dd)      // ����� ��������� ���� ���������, � ��� ���������� ���� �����
                break;
            ++index;
        }

        while ((*index).Get_day() < (data.dd + period)) // ���� ���������� ���������� �� ����� � ��������� ������
        {
            vector<Money>::iterator index2 = report.begin();    // �������� ��������� ���� �����
            for (; index2 != report.end(); ++index2)            // � ���� ���������� ��������� �� ������� ������
            {
                if ((*index).Get_cost() == (*index2).Get_cost())    // ���� ����� ���������� - ���� �������� �� ���� ����� ������
                {
                    (*index2).Set_summ((*index2).Get_summ() + (*index).Get_summ());
                    break;
                }
            }
            if (index2 == report.end())     // ���� � ���������� ������ ���� ������ ������ ������� - �� ���������� �������� � ����� ���������� ������� 
            {
                report.push_back(*index);
            }
            if (++index == table.end())     // �������� �� ����� ��������� �������
                break;
        }

        sort(report.begin(), report.end(), [](const Money& temp1, const Money& temp2) // ���������� ���������� ������� � ������������ �� ���
            {
                return temp1.Get_summ() > temp2.Get_summ();
            });


        string path = "Card_reports.txt";
        fstream file;
        file.open(path, fstream::in | fstream::out | fstream::app);         // ������� ���� � ������

        if (!file.is_open())
        {
            cout << "Error, file isn't open." << endl;
        }
        else                                                                // ����� ���� � ����
        {
            file << "Expense report by the 3 largest categories for card #" << numbercard << ", " << typecard
                << ", bank " << bank << ", for " << period << " day(s) since " << data.dd << "." << data.mm
                << "." << data.yyyy << ": " << endl << endl;
            vector<Money>::iterator index2 = report.begin();
            for (; index2 < report.begin() + 3; ++index2)           // ��� ���������� ����� ������
            {
                file << (*index2);
            }
            file << endl << endl;
        }
        file.close();
    }

//------------------------------------------------------------------------------------------------------------------------