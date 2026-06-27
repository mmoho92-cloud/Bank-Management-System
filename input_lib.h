#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

namespace input_lib
{
    enum en_charecter {
        small_charecter = 1,
        capital_charecter = 2,
        spicel_charecter = 3,
        digit = 4
    };

    int random_number_from_to(int from, int to)
    {
        int random_number = rand() % (to - from + 1) + from;
        return random_number;
    }

    char return_random_char(en_charecter char_type)
    {
        switch (char_type)
        {
        case en_charecter::small_charecter:
        {
            return char(random_number_from_to(97, 122));
            break;
        }
        case en_charecter::capital_charecter:
        {
            return char(random_number_from_to(65, 90));
            break;
        }
        case en_charecter::spicel_charecter:
        {
            return char(random_number_from_to(33, 47));
            break;
        }
        case en_charecter::digit:
        {
            return char(random_number_from_to(48, 57));
            break;
        }
        }
    }

    int read_positive_number(string massage)
    {
        float number;
        do {
            cout << massage << endl;
            cin >> number;
        } while (number < 0);
        return number;
    }


    void read_array(int arr[100], int& length)
    {
        cout << "enter the number of elemnts :\n";
        cin >> length;

        for (int i = 0; i < length; i++)
        {
            arr[i] = random_number_from_to(1, 100);

        }

    }

    int min_of_array(int arr[100], int length)
    {

        int min = arr[0];

        for (int i = 0; i < length; i++)
        {
            if (arr[i] < min)
            {
                min = arr[i];

            }
        }
        return min;

    }

    void print_array(int arr[100], int length)
    {
        cout << "the array elements : \n ";
        for (int i = 0; i < length; i++)
        {
            cout << arr[i] << " - ";

        }
        cout << endl;
    }

    void copy_of_array(int arr[100], int length, int arr1[100])
    {

        int sum = 0;

        for (int i = 0; i < length; i++)
        {

            arr1[i] = arr[i];
        }


    }

    void revers_of_array(int arr[100], int length, int arr1[100])
    {

        int j = length;

        for (int i = 0; i < length; i++)
        {
            arr1[j - 1] = arr[i];
            j--;

        }
    }

    short find_number_in_array(int arr[100], int length, int num)
    {


        for (int i = 0; i < length; i++)
        {

            if (arr[i] == num)
            {
                return i;

            }

        }
        return -1;

    }

    void add_array_element(int num, int arr[100], int& length)
    {
        length++;
        arr[length - 1] = num;
    }

    void read_two_dimentional_array(int arr[3][3], int rows, int columns)
    {

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                arr[i][j] = random_number_from_to(1, 100);

            }

        }

    }

    void print_two_dimentional_array(int arr[3][3], int rows, int columns)
    {
        cout << "the array elements : \n";
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                cout << setw(5) << arr[i][j];
            }
            cout << endl;
        }
        cout << endl;
    }

}