#pragma once
#pragma warning(disable : 4996)
#include <ctime>
#include <string>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <vector>
using namespace std;

namespace my_date_lib
{
    struct st_date
    {
        int day;
        int month;
        int year;
    };

    struct st_period {
        st_date date_from;
        st_date date_to;

    };

    bool is_year_leap(int year)
    {
        return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
    }

    int read_positive_number_from_to(string massage, int from, int to)
    {
        int number;
        do {
            cout << massage;
            cin >> number;
        } while (number < from || number > to);
        return number;
    }

    int read_number(string massage)
    {
        int number = 0;
        cout << massage;
        cin >> number;
        return number;
    }

    int how_many_days_in_month(int year, int month)
    {

        int number_of_dayes_in_month[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
        return (month == 2) ? (is_year_leap(year) ? 29 : 28) : number_of_dayes_in_month[month - 1];

    }

    st_date read_date()
    {
        st_date date;
        date.year = read_number("please enter a year :");
        date.month = read_positive_number_from_to("please enter the month : ", 1, 12);
        date.day = read_positive_number_from_to("please enter the day : ", 1, how_many_days_in_month(date.year, date.month));
        cout << endl;
        return date;
    }

    bool is_date1_before_date2(st_date date1, st_date date2)
    {
        return (date1.year < date2.year) ? true : ((date1.year ==
            date2.year) ? (date1.month < date2.month ? true : (date1.month ==
                date2.month ? date1.day < date2.day : false)) : false);
    }

    bool is_dates_equal(st_date date1, st_date date2)
    {
        return (date1.year == date2.year && date1.month == date2.month && date1.day == date2.day);

    }

    bool is_date1_after_date2(st_date date1, st_date date2)
    {
        return (!is_dates_equal(date1, date2) && !is_date1_before_date2(date1, date2));
    }

    enum en_dates_compier { befor = -1, equel = 0, after = 1 };

    en_dates_compier compier_dates(st_date date1, st_date date2)
    {
        if (is_date1_before_date2(date1, date2))
        {
            return en_dates_compier::befor;
        }
        if (is_dates_equal(date1, date2))
        {
            return en_dates_compier::equel;
        }
        return en_dates_compier::after;
    }

    bool is_day_the_last_day_in_month(st_date date)
    {
        return (date.day == how_many_days_in_month(date.year, date.month));
    }

    bool is_month_is_last_month_in_the_year(int month)
    {
        return (month == 12);
    }

    st_date increase_date_by_one_day(st_date& date)
    {

        if (is_day_the_last_day_in_month(date) && is_month_is_last_month_in_the_year(date.month))
        {
            date.day = 1;
            date.month = 1;
            date.year++;
        }
        else if (is_day_the_last_day_in_month(date))
        {
            date.day = 1;
            date.month++;
        }
        else
        {
            date.day++;
        }
        return date;
    }

    bool is_periods_overlapet(st_period period1, st_period period2)
    {
        if (compier_dates(period2.date_from, period1.date_to) == en_dates_compier::after || compier_dates(period1.date_from, period2.date_to) == en_dates_compier::after)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    int defrence_betwen_two_date(st_date date1, st_date date2, bool w = false)
    {
        int counter = 0;
        while (date1.year != date2.year || date1.month != date2.month || date1.day != date2.day)
        {
            increase_date_by_one_day(date1);
            counter++;
        }
        if (w)
            return counter + 1;
        else
            return counter;
    }

    int period_length_in_days(st_period period, bool w = false)
    {
        return defrence_betwen_two_date(period.date_from, period.date_to, w);
    }

    st_period read_period()
    {
        st_period period;
        period.date_from = read_date();
        period.date_to = read_date();
        return period;
    }

    bool is_date_within_period(st_period period, st_date date)
    {
        return (!(compier_dates(period.date_from, date) == en_dates_compier::after) && !(compier_dates(period.date_to, date) == en_dates_compier::befor));
    }

    int count_overlap_days_betwen_two_period(st_period period1, st_period period2)
    {
        int period1_length = period_length_in_days(period1, true);
        int period2_length = period_length_in_days(period2, true);
        int counter = 0;

        if (!is_periods_overlapet(period1, period2))
        {
            return 0;
        }
        if (period1_length < period2_length)
        {
            while (!is_date1_after_date2(period1.date_from, period1.date_to))
            {
                if (is_date_within_period(period2, period1.date_from))
                {
                    counter++;
                }
                period1.date_from = increase_date_by_one_day(period1.date_from);
            }
        }
        else
        {
            while (!is_date1_after_date2(period2.date_from, period2.date_to))
            {
                if (is_date_within_period(period1, period2.date_from))
                {
                    counter++;
                }
                period2.date_from = increase_date_by_one_day(period2.date_from);
            }
        }
        return counter;
    }

    bool validate_date(st_date date)
    {
        if (date.year < 1)
        {
            return false;
        }
        if (date.month > 12 || date.month < 1)
        {
            return false;
        }
        if (date.day < 1 || date.day > how_many_days_in_month(date.year, date.month))
        {
            return false;
        }

        return true;
    }

    string lower_all_string(string s1)
    {

        for (int i = 0; i < s1.length(); i++)
        {
            s1.at(i) = towlower(s1.at(i));

        }
        return s1;
    }

    vector <string> split_string(string s1, string delim = " ")
    {
        vector<string> v_string;

        short pos = 0;
        string s_word;

        while ((pos = s1.find(delim)) != std::string::npos)
        {
            s_word = s1.substr(0, pos);
            if (s_word != " ")
            {

                v_string.push_back(s_word);

            }
            s1.erase(0, pos + delim.length());
        }
        if (s1 != " ")
        {

            v_string.push_back(s1);
        }
        return v_string;
    }

    string join_string(vector<string> v_string, string delim = " ")
    {
        string s2;
        for (int i = 0; i < v_string.size(); i++)
        {
            s2.append(v_string[i]);
            s2.append(delim);
        }
        return s2.substr(0, s2.length() - delim.length());
    }

    string replace_word_in_string(string s1, string string_from, string string_to)
    {
        short pos = s1.find(string_from);
        while (pos != std::string::npos)
        {
            s1 = s1.replace(pos, string_from.length(), string_to);
            pos = s1.find(string_from);
        }
        return s1;
    }
    
    string read_string_date(string Message)
    {

        string DateString;
        cout << Message;
        getline(cin >> ws, DateString);
        return DateString;
    }

    st_date string_to_date(string s1, string delim = "/")
    {
        st_date date;
        vector<string> date_string = split_string(s1, delim);
        date.day = stoi(date_string[0]);
        date.month = stoi(date_string[1]);
        date.year = stoi(date_string[2]);

        return date;
    }

    string date_to_string(st_date Date)
    {
        return to_string(Date.day) + "/" + to_string(Date.month) +
            "/" + to_string(Date.year);
    }

    string format_the_date(st_date date, string s1 = "dd/mm/yyyy")
    {
        string formated_date = s1;

        formated_date = replace_word_in_string(formated_date, "dd", to_string(date.day));
        formated_date = replace_word_in_string(formated_date, "mm", to_string(date.month));
        formated_date = replace_word_in_string(formated_date, "yyyy", to_string(date.year));

        return formated_date;
    }



}