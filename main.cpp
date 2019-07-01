#include <iostream>
#include <fstream>



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
    year += 1;

    int index = (year + (4 * century)) % 28;
    int weekday = weekdays[index - 1];

    weekday += is_leap ? shift_leap[month - 1]
                       : shift_not_leap[month - 1];
    weekday += (day - 1);
    weekday %= 7;

    return weekday;
}

int main()
{ 
    // first_weekdays_table();

    cout << get_weekday(2019, 7, 1) << endl;

    return 0;
}
