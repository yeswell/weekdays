#include <iostream>
#include <fstream>
#include <string>



using namespace std;



bool is_leap_year(int year)
{
    if ((year % 400) == 0) return true;

    if ((year % 100) == 0) return false;

    if ((year %   4) == 0) return true;

    return false;
}

void first_weekdays_table()
{
    ofstream file("weekdays.txt", ios_base::out);

    int weekday = 3;

    for (int i = 1801; i <= 3000; ++i)
    {
        file << weekday;

        if ((i % 100) != 0)
        {
            file << " ";
        }
        else
        {
            file << endl;
        }

        weekday += is_leap_year(i) ? 2 : 1;
        weekday %= 7;
    }

    file.close();
}

int get_weekday(int year, int month, int day)
{
    int weekdays[] = {0, 1, 2, 3, 5, 6,
                      0, 1, 3, 4, 5, 6,
                         1, 2, 3, 4, 6,
                      0, 1, 2, 4, 5, 6,
                      0, 2, 3, 4, 5};

    int shift_not_leap[] = {0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5};
    int shift_leap[]     = {0, 3, 4, 0, 2, 5, 0, 3, 6, 1, 4, 6};

    bool is_leap = is_leap_year(year);

    year -= 1;
    year %= 400;

    int century = year / 100;

    year %= 100;

    int index   = (year + (4 * century)) % 28;
    int weekday = weekdays[index];

    weekday += is_leap ? shift_leap[month - 1]
                       : shift_not_leap[month - 1];
    weekday += (day - 1);
    weekday %= 7;

    return weekday;
}

int get_weekday_x(int year, int month, int day)
{
    int weekdays[] =
    {
        0, 1, 2, 3,    5, 6,
        0, 1,    3, 4, 5, 6,
           1, 2, 3, 4,    6,
        0, 1, 2,    4, 5, 6,
        0,    2, 3, 4, 5
    };

    int shifts[] = {0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5};

    bool is_leap = is_leap_year(year);

    year -= 1;
    year %= 400;

    int century = year / 100;

    year %= 100;

    int index = (year + (4 * century)) % 28;
    int weekday = weekdays[index];

    int shift = shifts[month - 1];
    if (is_leap and (month > 2))
    {
        shift += 1;
        shift %= 7;
    };

    weekday += shift + (day - 1);
    weekday %= 7;

    return weekday;
}

int get_weekday_c(int year, int month, int day)
{
    int shifts[] = {0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5};

    int shift = shifts[month - 1];

    if (is_leap_year(year) and (month > 2))
    {
        shift += 1;
    };

    year = (year - 1) % 400;

    int century = year / 100;

    int index   = ((4 * century) + (year % 100)) % 28;

    int weekday = (index + (index / 4)) + shift + (day - 1);

    return (weekday % 7);
}

void print_weekday_name(int weekday)
{
    string names[] =
    {
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday",
        "Friday",
        "Saturday",
        "Sunday"
    };

    cout << names[weekday] << endl;
}

void eternal_question()
{
    int year, month, day;

    cout << "Input year, month and day:" << endl;

    while (true)
    {
        cout << endl;
        cin >> year >> month >> day;

        if ((year > 0) and (month > 0) and (month <= 12) and (day > 0))
        {
            cout << day << "." << month << "." << year << ", ";
            print_weekday_name(get_weekday_c(year, month, day));
        }
        else
        {
            break;
        }
    }
}

int main()
{ 
    // first_weekdays_table();

    // cout << get_weekday(1, 1, 1) << endl;

    eternal_question();

    return 0;
}
