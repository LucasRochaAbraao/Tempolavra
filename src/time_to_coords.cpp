#include <iostream>
#include <vector>
#include <tuple>
#include <cmath>
#include <typeinfo>

#include "../include/time_to_coords.h"
#include "../include/coords_util.h"


std::vector<std::vector<std::tuple<int, int>>> get_time_coords(int hour, int minute, int freq = 5)
{
    std::vector<std::vector<std::tuple<int, int>>> phrase;

    minute = freq * std::round(minute / static_cast<float>(freq));  // make minute a multiple of 5 (wordclock precision)


    if (minute == 0)
    {  // for cases like 24 00, which would not be caught below
        if (hour > 23) {hour = 0;}
    }

    // rounds minutes above 55 (which are multiples of 5 at this point) to 0 for the next hour.
    if (minute >= 60)
    {
        minute = 0;
        if (hour >= 23)
        { // in cases where 24 (or greater) was passed in as cli arg.
            hour = 0;
        }
        else {hour += 1;} // all other regular hours need to increase when minute >= 60.
    }

    // if the minutes are not rounding to the next hour, but was specified in the cli.
    if (hour > 23) {hour = 0;}

    //std::cout << hour << ":" << minute << std::endl;
    
    // # é 1h..., é meio dia..., é meia noite...
    if ((hour == 1 or hour == 12 or hour == 13 or hour == 0) && minute == 0)
    {
        phrase.push_back({{0, 3}});  // é
    } 
    else
    {
        phrase.push_back({{0, 0}, {0, 1}, {0, 2}});  // são
    }

    if (minute >= 40) {hour += 1;}
    if (hour == 24) {hour = 0;}

    // hour coords
    if (hour == 0)
    {
        phrase.push_back({{8, 5}, {8, 6}, {8, 7}, {8, 8}});  // # meia
        phrase.push_back({{14, 10}, {14, 11}, {14, 12}, {14, 13}, {14, 14}});  // # noite
        if (minute == 0) {return phrase;}
    }
    else if (hour == 12)
    {
        phrase.push_back({{7, 4}, {7, 5}, {7, 6}, {7, 7}});  // meio
        phrase.push_back({{7, 9}, {7, 10}, {7, 11}});  // dia
        if (minute == 0) {return phrase;}
    }
    else
    { // if not one of the special phrases above, get the hour coords
        auto current_hour = get_coord_hour(hour, WordPosition::primary);      
        phrase.push_back(current_hour);
    }

    // minute coords
    if (minute == 0 && (hour == 1 or hour == 13))
    {
        phrase.push_back({{13, 0}, {13, 1}, {13, 2}, {13, 3}});  // hora
        return phrase;
    }

    if (minute == 0)
    {
        if (hour < 12)
        {  // manhã
            phrase.push_back({{13, 0}, {13, 1}, {13, 2}, {13, 3}, {13, 4}});  // horas
            if (flip_coin(0.8))
            {
                phrase.push_back({{13, 13}, {13, 14}});  // da
                phrase.push_back({{13, 0}, {13, 1}, {13, 2}, {13, 3}, {13, 4}});  // manhã
            }
        }
        else if (hour >= 12 && hour < 18)
        {  // tarde
            phrase.push_back({{13, 0}, {13, 1}, {13, 2}, {13, 3}, {13, 4}});  // horas
            if (flip_coin(0.5))
            {
                phrase.push_back({{13, 13}, {13, 14}});  // da
                phrase.push_back({{14, 5}, {14, 6}, {14, 7}, {14, 8}, {14, 9}});  // tarde
            }
        }
        else { // noite
            phrase.push_back({{13, 0}, {13, 1}, {13, 2}, {13, 3}, {13, 4}});  // horas
            if (flip_coin(0.6))
            {
                phrase.push_back({{13, 13}, {13, 14}});  // da
                phrase.push_back({{14, 10}, {14, 11}, {14, 12}, {14, 13}, {14, 14}});  // noite
            }
        }
        return phrase;  // since minute = 0
    }

    else if (minute == 25)
    {
        phrase.push_back({{6, 12}});  // e
        phrase.push_back({{8, 0}, {8, 1}, {8, 2}, {8, 3}, {8, 4}});  // vinte
        phrase.push_back({{6, 12}});  // e
        phrase.push_back({{12, 10}, {12, 11}, {12, 12}, {12, 13}, {12, 14}});  // cinco
    }

    else if (minute == 35)
    {
        phrase.push_back({{6, 12}});  // e
        phrase.push_back({{9, 5}, {9, 6}, {9, 7}, {9, 8}, {9, 9}, {9, 10}});  // trinta
        phrase.push_back({{6, 12}});  // e
        phrase.push_back({{12, 10}, {12, 11}, {12, 12}, {12, 13}, {12, 14}});  // cinco
    }

    else if (minute == 40)
    {
        phrase.insert(phrase.begin() + 1, {{2, 10}, {2, 11}, {2, 12}, {2, 13}, {2, 14}});  // inserts "vinte"
        if (hour == 1 or hour == 12 or hour == 13 or hour == 0)
        {
            phrase.insert(phrase.begin() + 2, {{7, 0}, {7, 1}, {7, 2}});  // inserts "pra"
        }
        else
        {
            phrase.insert(phrase.begin() + 2, {{7, 0}, {7, 1}, {7, 2}, {7, 3}});  // inserts "pras"
        }
    }

    else if (minute == 45)
    {
        phrase.insert(phrase.begin() + 1, {{5, 7}, {5, 8}, {5, 9}, {5, 10}, {5, 11}, {5, 12}});  // inserts "quinze"
        if (hour == 1 or hour == 12 or hour == 13 or hour == 0)
        {
            phrase.insert(phrase.begin() + 2, {{7, 0}, {7, 1}, {7, 2}});  // inserts "pra"
        }
        else
        {
            phrase.insert(phrase.begin() + 2, {{7, 0}, {7, 1}, {7, 2}, {7, 3}});  // inserts "pras"
        }
    }

    else if (minute == 50)
    {
        phrase.insert(phrase.begin() + 1, {{4, 10}, {4, 11}, {4, 12}});  // inserts "dez"
        if (hour == 1 or hour == 12 or hour == 13 or hour == 0)
        {
            phrase.insert(phrase.begin() + 2, {{7, 0}, {7, 1}, {7, 2}});  // inserts "pra"
        }
        else
        {
            phrase.insert(phrase.begin() + 2, {{7, 0}, {7, 1}, {7, 2}, {7, 3}});  // inserts "pras"
        }
    }

    else if (minute == 55)
    {
        phrase.insert(phrase.begin() + 1, {{1, 5}, {1, 6}, {1, 7}, {1, 8}, {1, 9}});  // inserts "cinco"
        if (hour == 1 or hour == 12 or hour == 13 or hour == 0)
        {
            phrase.insert(phrase.begin() + 2, {{7, 0}, {7, 1}, {7, 2}});  // inserts "pra"
        }
        else
        {
            phrase.insert(phrase.begin() + 2, {{7, 0}, {7, 1}, {7, 2}, {7, 3}});  // inserts "pras"
        }
    }
    else
    {
        phrase.push_back({{9, 11}});  // e
        // If not one of the special phrases above, get regular minute
        auto current_minute = get_coord_minute(hour, WordPosition::primary);
        phrase.push_back(current_minute);
    }

    // Time of day
    if (hour > 0 && hour < 12)
    {
        if (flip_coin(0.8))
        {
            phrase.push_back({{13, 13}, {13, 14}});  // da
            phrase.push_back({{14, 5}, {14, 6}, {14, 7}, {14, 8}, {14, 9}});  // manhã
        }
    } 
    else if (hour >= 13 && hour < 19)
    {
        if (flip_coin(0.8))
        {
            phrase.push_back({{13, 13}, {13, 14}});  // da
            phrase.push_back({{14, 5}, {14, 6}, {14, 7}, {14, 8}, {14, 9}});  // tarde
        }
    }
    else if ((hour >= 19 && hour < 23) || (hour == 23 && minute <= 59))
    {
        if (flip_coin(0.8))
        {
            phrase.push_back({{13, 13}, {13, 14}});  // da
            phrase.push_back({{14, 10}, {14, 11}, {14, 12}, {14, 13}, {14, 14}});  // noite
        }
    }

    return phrase;
}
