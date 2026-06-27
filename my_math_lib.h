
#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

namespace my_math_lib
{
    enum en_prime_notprime { prime = 1, notprime = 2 };
    enum en_perfect_notperfect { perfect = 1, notperfect = 2 };

    en_prime_notprime check_prime_number(int number)
    {
        int num = round(number / 2);
        for (int counter = 2; counter <= num; counter++)
        {
            if (number % counter == 0)
                return en_prime_notprime::notprime;
        }
        return en_prime_notprime::prime;
    }

    en_perfect_notperfect check_perfect_number(int number)
    {

        int sum = 0;
        for (int counter = 1; counter < number; counter++)
        {
            if (number % counter == 0)
            {

                sum += counter;
            }

        }
        if (sum == number)
            return en_perfect_notperfect::perfect;

        return en_perfect_notperfect::notperfect;

    }

    void add_array_element(int num, int arr[100], int& length)
    {
        length++;
        arr[length - 1] = num;
    }

    int revers_number(int number)
    {
        int number2 = 0;
        int remainder = 0;


        while (number > 0)
        {
            remainder = number % 10;

            number = number / 10;

            number2 = remainder + number2 * 10;

        }
        return number2;
    }

    bool IsPalindromeNumber(int number)
    {
        int number2 = 0;
        int remainder = 0;


        while (number > 0)
        {
            remainder = number % 10;

            number = number / 10;

            number2 = remainder + number2 * 10;

        }

        return number == number2;
    }

    void print_inverted_number(int number)
    {

        for (int i = number; i != 0; i--)
        {
            for (int j = i; j != 0; j--)
            {
                cout << i;
            }
            cout << endl;
        }
    }

    int sum_of_array(int arr[100], int length)
    {

        int sum = 0;

        for (int i = 0; i < length; i++)
        {

            sum += arr[i];
        }
        return sum;

    }

    float avrage_of_array(int arr[100], int length)
    {
        int avrage = 0;

        for (int i = 0; i < length; i++)
        {
            avrage += arr[i];

        }
        return avrage / length;

    }

    void sum_of_tow_array(int arr[100], int arr1[100], int arr2[100], int length)
    {

        for (int i = 0; i < length; i++)
        {
            arr2[i] = arr[i] + arr1[i];

        }

    }

    void swap(int& num1, int& num2)
    {
        int num3;
        num3 = num1;
        num1 = num2;
        num2 = num3;
    }

    void odd_numbers_in_array(int arr[100], int arr2[100], int length, int& length2)
    {

        for (int i = 0; i < length; i++)
        {

            if (arr[i] % 2 != 0)
            {
                add_array_element(arr[i], arr2, length2);
            }

        }

    }


}




