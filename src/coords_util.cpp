#include <map>
#include <iostream>
#include <random>

#include "../include/coords_util.h"


bool flip_coin(double weight) {
    //Simulates a coin flip with a given weight bias.

    //Args:
    //    weight: A value between 0 and 1 representing the weight or bias.

    //Returns:
    //    Returns True if a random value is less than the given weight and False otherwise.

    if (weight < 0.0 || weight > 1.0)
    {
        std::cerr << "Error: Weight must be between 0 and 1." << std::endl;
        std::exit(1);
    }
    else if (weight == 0.0)
    {
        return false;
    }

    std::random_device rd;  // Use a random device to seed the generator
    std::mt19937 gen(rd()); // Initialize the Mersenne Twister engine
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    double reference = dist(gen);
    return weight >= reference;
}


std::vector<IntTuple> get_coord_hour(int hour) {
    // Given an hour and a position, returns a list of coordinates (tuples) in the matrix that correspond
    // to the hour.
    // Args:
    //      hour: An integer representing the hour in the range 0 to 23.
    //      pos: An optional integer representing the position of the hour word in the sentence.
    //           It can be either WordPosition.primary or WordPosition.secondary, defaulting to WordPosition.primary.
    //           This represents where the hour is in the time phrase. For example, in 'são cinco pras dez',
    //           'dez' is in the secondary hour position, while 'cinco' is in the primary.
    // Returns:
    //      A vector of tuples with two integers representing the (row, column) coordinates in a clock
    //      where the hour word starts.

    std::map<int, std::vector<IntTuple>> time_words = {
        { // meia noite
            0,  {{8, 5}, {8, 6}, {8, 7}, {8, 8}, {14, 10}, {14, 11}, {14, 12}, {14, 13}, {14, 14}}
        },
        {
            1,  {{2, 0}, {2, 1}, {2, 2}}
        },
        {
            2,  {{3, 3}, {3, 4}, {3, 5}, {3, 6}}
        },
        {
            3,  {{1, 1}, {1, 2}, {1, 3}, {1, 4}}
        },
        {
            4,  {{2, 3}, {2, 4}, {2, 5}, {2, 6}, {2, 7}, {2, 8}}
        },
        {
            5,  {{1, 5}, {1, 6}, {1, 7}, {1, 8}, {1, 9}}
        },
        {
            6,  {{4, 5}, {4, 6}, {4, 7}, {4, 8}}
        },
        {
            7,  {{6, 7}, {6, 8}, {6, 9}, {6, 10}}
        },
        {
            8,  {{3, 8}, {3, 9}, {3, 10}, {3, 11}}
        },
        {
            9,  {{5, 2}, {5, 3}, {5, 4}, {5, 5}}
        },
        {
            10,  {{4, 10}, {4, 11}, {4, 12}}
        },
        {
            11,  {{4, 0}, {4, 1}, {4, 2}, {4, 3}}
        },
        { // meio dia ????????
            12,  {{7, 4}, {7, 5}, {7, 6}, {7, 7}, {7, 9}, {7, 10}, {7, 11}}
        },
        { // uma...
            13,  {{2, 0}, {2, 1}, {2, 2}}
        },
        {
            14,  {{3, 3}, {3, 4}, {3, 5}, {3, 6}}
        },
        {
            15,  {{1, 1}, {1, 2}, {1, 3}, {1, 4}}
        },
        {
            16,  {{2, 3}, {2, 4}, {2, 5}, {2, 6}, {2, 7}, {2, 8}}
        },
        {
            17,  {{1, 5}, {1, 6}, {1, 7}, {1, 8}, {1, 9}}
        },
        {
            18,  {{4, 5}, {4, 6}, {4, 7}, {4, 8}}
        },
        {
            19,  {{6, 7}, {6, 8}, {6, 9}, {6, 10}}
        },
        {
            20,  {{3, 8}, {3, 9}, {3, 10}, {3, 11}}
        },
        {
            21,  {{5, 2}, {5, 3}, {5, 4}, {5, 5}}
        },
        {
            22,  {{4, 10}, {4, 11}, {4, 12}}
        },
        {
            23,  {{4, 0}, {4, 1}, {4, 2}, {4, 3}}
        }
    };

    auto time_tuple = time_words.find(hour);

    if (time_tuple != time_words.end())
    {
        const std::vector<IntTuple>& hour_data = time_tuple->second;

        return hour_data;
    }

    return {};
}


std::vector<IntTuple> get_coord_minute(int minute) {
    // Returns the coordinate tuples of the minute word, corresponding to a given minute and position.
    // Args:
    //     minute: The minute value, which must be one of 5, 10, 15, 20, or 30.
    // Returns:
    //     A list of coordinate tuples corresponding to the specified minute and position.
    //         Each tuple contains two integers that represent the row and column indices of a word in the time grid.
    //         The row index ranges from 1 to 13 and the column index ranges from 0 to 14.
    //         For example, [(1, 5), (1, 6), ..., (1, 9)] corresponds to the word 'cinco' in the primary position,
    //         which is located in the first row, from column 5 to 9 inclusive.

    std::map<int, std::vector<IntTuple>> time_words = {
        {
            5,  {{12, 10}, {12, 11}, {12, 12}, {12, 13}, {12, 14}}
        },
        {
            10,  {{11, 3}, {11, 4}, {11, 5}}
        },
        {
            15,  {{8, 9}, {8, 10}, {8, 11}, {8, 12}, {8, 13}, {8, 14}}
        },
        {
            20,  {{8, 0}, {8, 1}, {8, 2}, {8, 3}, {8, 4}}
        },
        {
            30,  {{13, 9}, {13, 10}, {13, 11}, {13, 12}}
        },
    };

    auto time_tuple = time_words.find(minute);

    if (time_tuple != time_words.end())
    {
        std::cout << minute << std::endl;
        const std::vector<IntTuple>& minute_data = time_tuple->second;
        return minute_data;
    }

    return {};
}
