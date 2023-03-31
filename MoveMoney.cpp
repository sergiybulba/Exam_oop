
#include"MoveMoney.h"


/************************************************************************************************************************/
    void MoveMoney::Set(Money summ)            // сеттер - добавлення транзакції в кінець вектору												
    {
        table.push_back(summ);
    }

    void MoveMoney::Load_transaction_txt_file(string path) {}       // метод - завантажити базу даних з транзакціями з txt-файлу 

    void MoveMoney::Report(Date data, int period, int numbercard, string bank, string typecard) {} // метод - сформувати звіт по витратах і завантажити в txt-файл

    void MoveMoney::Max_category(Date data, int period, int numbercard, string bank, string typecard) {} // метод - сформувати рейтинг по максимальних категоріях витрат і завантажити в txt-файл

    void MoveMoney::Max_Expense(Date data, int period, int numbercard, string bank, string typecard) {} // метод - сформувати рейтинг по максимальних витратах і завантажити в txt-файл

//------------------------------------------------------------------------------------------------------------------------

    void Enter_money:: Load_transaction_txt_file(string path)         // метод - завантажити базу даних з транзакціями з txt-файлу 
    {
        fstream file;
        file.open(path, fstream::in | fstream::out | fstream::app);     // відкрити файл

        if (!file.is_open())
        {
            cout << "Error, file isn't open." << endl;
        }
        else
        {
            Money temp;
            while (true)
            {
                file >> temp;       // зчитати рядок 
                if (file.eof())
                    break;
                Set(temp);          // записати рядок типу Money (transaction) в вектор 
            }
        }
        file.close();
    }

    void Enter_money::Report(Date data, int period, int numbercard, string bank, string typecard)    // метод - сформувати звіт по витратах і завантажити в txt-файл
    {
        vector<Money> report;                               // допоміжний вектор який буде формуватися з основного
        vector<Money>::iterator index = table.begin();      // ітератор основної бази даних
        while (true)
        {
            if ((*index).Get_day() == data.dd)              // пошук необхідної дати тразакції, з якої починається відбір даних
                break;
            ++index;
        }

        while ((*index).Get_day() < (data.dd + period))     // відбір необхідних транзакцій за період в допоміжний вектор
        {
            vector<Money>::iterator index2 = report.begin();    // ітератор додаткової бази даних
            for (; index2 != report.end(); ++index2)            // в циклі транзакції сумуються по статтях витрат
            {
                if ((*index).Get_cost() == (*index2).Get_cost())   // якщо статті співпадають - сума додається до цієї статті витрат     
                {
                    (*index2).Set_summ((*index2).Get_summ() + (*index).Get_summ());
                    break;
                }
            }
            if (index2 == report.end())     // якщо в допоміжному векторі така стаття витрат відсутня - ця транзакція додається в кінець допоміжного вектору 
            {
                report.push_back(*index);
            }
            if (++index == table.end())     // перевірка на кінець основного вектору
                break;
        }


        string path = "Card_reports.txt";
        fstream file;
        file.open(path, fstream::in | fstream::out | fstream::app);     // відкрити файл зі звітами

        if (!file.is_open())
        {
            cout << "Error, file isn't open." << endl;
        }
        else                                                // запис звіту у файл
        {
            file << "Expense report for card #" << numbercard << ", " << typecard
                << ", bank " << bank << ", for " << period << " day(s) since "
                << data.dd << "." << data.mm << "." << data.yyyy << ": " << endl << endl;
            vector<Money>::iterator index2 = report.begin();
            for (; index2 != report.end(); ++index2)
            {
                file << (*index2);                      // записується інформація з додаткового вектору про витрати згруповані по статті витрат
            }
            file << endl << endl;
        }
        file.close();
    }

    void Enter_money::Max_Expense(Date data, int period, int numbercard, string bank, string typecard)   // метод - сформувати рейтинг по максимальних витратах і завантажити в txt-файл
    {
        vector<Money> report;                           // допоміжний вектор який буде формуватися з основного
        vector<Money>::iterator index = table.begin();  // ітератор основної бази даних
        while (true)
        {
            if ((*index).Get_day() == data.dd)          // пошук необхідної дати тразакції, з якої починається відбір даних
                break;
            ++index;
        }

        while ((*index).Get_day() < (data.dd + period)) // відбір необхідних транзакцій за період в допоміжний вектор
        {
            report.push_back(*index);
            if (++index == table.end())
                break;
        }

        sort(report.begin(), report.end(), [](const Money& temp1, const Money& temp2)  // сортування допоміжного вектора з транзакціями по сумі
            {
                return temp1.Get_summ() > temp2.Get_summ();
            });


        string path = "Card_reports.txt";
        fstream file;
        file.open(path, fstream::in | fstream::out | fstream::app);     // відкрити файл зі звітами

        if (!file.is_open())
        {
            cout << "Error, file isn't open." << endl;
        }
        else                        // запис звіту у файл
        {
            file << "Expense report by the 3 largest summs for card #" << numbercard << ", " << typecard
                << ", bank " << bank << ", for " << period << " day(s) since " << data.dd << "." << data.mm
                << "." << data.yyyy << ": " << endl << endl;
            vector<Money>::iterator index2 = report.begin();
            for (; index2 < report.begin() + 3; ++index2)           // три максимальні транзакції
            {
                file << (*index2);
            }
            file << endl << endl;
        }
        file.close();               // закрити файл
    }

    void Enter_money::Max_category(Date data, int period, int numbercard, string bank, string typecard)  // метод - сформувати рейтинг по максимальних статтях витрат і завантажити в txt-файл
    {
        vector<Money> report;                           // допоміжний вектор який буде формуватися з основного
        vector<Money>::iterator index = table.begin();  // ітератор основної бази даних
        while (true)
        {
            if ((*index).Get_day() == data.dd)      // пошук необхідної дати тразакції, з якої починається відбір даних
                break;
            ++index;
        }

        while ((*index).Get_day() < (data.dd + period)) // відбір необхідних транзакцій за період в допоміжний вектор
        {
            vector<Money>::iterator index2 = report.begin();    // ітератор додаткової бази даних
            for (; index2 != report.end(); ++index2)            // в циклі транзакції сумуються по статтях витрат
            {
                if ((*index).Get_cost() == (*index2).Get_cost())    // якщо статті співпадають - сума додається до цієї статті витрат
                {
                    (*index2).Set_summ((*index2).Get_summ() + (*index).Get_summ());
                    break;
                }
            }
            if (index2 == report.end())     // якщо в допоміжному векторі така стаття витрат відсутня - ця транзакція додається в кінець допоміжного вектору 
            {
                report.push_back(*index);
            }
            if (++index == table.end())     // перевірка на кінець основного вектору
                break;
        }

        sort(report.begin(), report.end(), [](const Money& temp1, const Money& temp2) // сортування допоміжного вектора з транзакціями по сумі
            {
                return temp1.Get_summ() > temp2.Get_summ();
            });


        string path = "Card_reports.txt";
        fstream file;
        file.open(path, fstream::in | fstream::out | fstream::app);         // відкрити файл зі звітами

        if (!file.is_open())
        {
            cout << "Error, file isn't open." << endl;
        }
        else                                                                // запис звіту у файл
        {
            file << "Expense report by the 3 largest categories for card #" << numbercard << ", " << typecard
                << ", bank " << bank << ", for " << period << " day(s) since " << data.dd << "." << data.mm
                << "." << data.yyyy << ": " << endl << endl;
            vector<Money>::iterator index2 = report.begin();
            for (; index2 < report.begin() + 3; ++index2)           // три максимальні статті витрат
            {
                file << (*index2);
            }
            file << endl << endl;
        }
        file.close();
    }

//------------------------------------------------------------------------------------------------------------------------