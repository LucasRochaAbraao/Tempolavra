#include <chrono>
#include <ctime>
#include <fmt/core.h>
#include <iomanip> // for std::put_time
#include <iostream>
#include <string>
#include <tuple>
#include <unistd.h>
#include <vector>

#include "../include/time_to_coords.h"
#include "../include/utilities.h"

// TODO
// major hour position bug (but move to bitmasks first), ex:
// - 00:40 -> {0, 0} {0, 1} {0, 2} {2, 10} {2, 11} {2, 12} {2, 13} {2, 14} {7, 0} {7, 1} {7, 2} {2, 0} {2, 1} {2, 2}... 
// - Arduino code

//#include <Arduino.h>

//int LED_BUILTIN = 2;
//
//void setup()
//{
//    pinMode(LED_BUILTIN, OUTPUT);
//
//}
//
//void loop()
//{
//    digitalWrite(LED_BUILTIN, HIGH);
//    delay(1000);
//
//    digitalWrite(LED_BUILTIN, LOW);
//    delay(1000);
//
//}

std::vector<std::string> get_word_from_matrix(const std::vector<std::tuple<int, int>>& coords)
{
    std::vector<std::vector<std::string>> letterMatrix = {
       // 0    1    2    3    4    5    6    7    8    9   10   11   12   13   14
        {"S", "Ã", "O", "É", "O", "J", "G", "T", "U", "R", "W", "Z", "N", "X", "A"},  // 0 sao é
        {"E", "T", "R", "Ê", "S", "C", "I", "N", "C", "O", "A", "F", "Y", "B", "P"},  // 1 tres cinco
        {"U", "M", "A", "Q", "U", "A", "T", "R", "O", "P", "V", "I", "N", "T", "E"},  // 2 uma quatro vinte
        {"D", "H", "W", "D", "U", "A", "S", "Q", "O", "I", "T", "O", "L", "V", "I"},  // 3 duas oito
        {"O", "N", "Z", "E", "G", "S", "E", "I", "S", "B", "D", "E", "Z", "A", "Y"},  // 4 onze seis dez
        {"K", "J", "N", "O", "V", "E", "B", "Q", "U", "I", "N", "Z", "E", "U", "F"},  // 5 nove quinze u
        {"W", "R", "D", "O", "Z", "E", "F", "S", "E", "T", "E", "B", "E", "H", "T"},  // 6 doze sete e
        {"P", "R", "A", "S", "M", "E", "I", "O", "V", "D", "I", "A", "D", "A", "E"},  // 7 pras meio dia da e
        {"M", "E", "I", "A", "N", "O", "I", "T", "E", "Q", "U", "I", "N", "Z", "E"},  // 8 noite meia quinze
        {"V", "I", "N", "T", "E", "T", "R", "I", "N", "T", "A", "Y", "F", "E", "X"},  // 9 vinte trinta e
        {"N", "O", "V", "E", "D", "U", "A", "S", "U", "M", "A", "S", "E", "T", "E"},  // 10 nove duas uma sete
        {"A", "M", "O", "D", "E", "Z", "S", "E", "I", "S", "H", "O", "I", "T", "O"},  // 11 dez seis oito
        {"Q", "U", "A", "T", "R", "O", "T", "R", "E", "S", "C", "I", "N", "C", "O"},  // 12 quatro tres cinco
        {"H", "O", "R", "A", "S", "D", "I", "A", "E", "M", "E", "I", "A", "D", "A"},  // 13 horas dia e meia da
        {"M", "A", "N", "H", "Ã", "T", "A", "R", "D", "E", "N", "O", "I", "T", "E"}   // 14 manhã tarde noite
       // 0    1    2    3    4    5    6    7    8    9   10   11   12   13   14
    };

    std::vector<std::string> leds_to_activate;

    for (const auto& word_coords : coords)
    {
        int first = std::get<0>(word_coords);
        int second = std::get<1>(word_coords);

        leds_to_activate.push_back(letterMatrix[first][second]);
    }

    return leds_to_activate;
}


std::vector<int> map_matrix_to_1d(std::vector<std::vector<std::tuple<int,int>>>& time_coords)
{
    std::vector<int> led_indices;
    for (const auto& hour_data : time_coords)
    {
        // Loop over the inner vector
        for (const auto& coords : hour_data)
        {
            int column = std::get<0>(coords);
            int row = std::get<1>(coords);
            int index = column * 15 + row;

            log(fmt::format("Coords: ({} - {} = {})", column, row, index), LogLevel::LevelDebug);

            led_indices.push_back(index);
        }
    }
    return led_indices;
}


void run(int hour, int minute, bool silent, bool detailed, int period = 5)
{
    auto time_coords = get_time_coords(hour, minute, period);
        // ex: {{(0,1), (0,2), (0,3)}, {(1,4), (1,5), (1,6), (1,7)}, {(4,6), (4,7), (4,8)}}

    // string with letters representing current hour rounded to nearest 5min
    std::vector<std::string> final_phrase;
    for (const auto& coord : time_coords)
    {
        auto matrix_word = get_word_from_matrix(coord);
        for (const auto& word : matrix_word)
        {
            final_phrase.push_back(word);
        }
    }

    // gets an array of LED index to be turned on.
    auto indices = map_matrix_to_1d(time_coords);

    if (silent)
    {
        for (const auto& index : indices)
        {
            log(fmt::format("led index: {}", index), LogLevel::LevelInfo);
        }
    }

    else if (detailed)
    {
        log(fmt::format("real hour: {}", hour), LogLevel::LevelDebug);
        log(fmt::format("real minute: {}", minute), LogLevel::LevelDebug);

        int letter_index {0};
        for (const auto& index : indices)
        {
            std::cout << "turn on LED: " << index;
            std::cout << " - " << final_phrase[letter_index] << std::endl;
            letter_index++;
        }
        std::cout << "period: " << period << std::endl;
    }

    else
    {
        // for loop for inline letters
        for (const auto& word : final_phrase)
        {
            std::cout << word;
        }
        std::cout << std::endl;
    }
}


void simulate_period(int period)
{
    setLogLevel(LogLevel::LevelNone);

    for (int hour = 0; hour < 24; ++hour)
    {
        for (int minute = 0; minute < 60; minute += period)
        {
            std::cout << "Simulating time: " << std::setw(2) << std::setfill('0') << hour << ":"
                      << std::setw(2) << std::setfill('0') << minute << std::endl;
            bool silent = false;
            bool detailed = false;
            run(hour, minute, silent, detailed, period);
            std::cout << std::endl;
        }
    }
}


void simulate_time(int hour, int minute)
{
    std::cout << "Simulating time: " << std::setw(2) << std::setfill('0') << hour << ":"
              << std::setw(2) << std::setfill('0') << minute << std::endl;
    bool silent = false;
    bool detailed = false;
    run(hour, minute, silent, detailed);
}


int main(int argc, char* argv[])
{
    auto time_point = std::chrono::system_clock::now();
    std::time_t time_t_now = std::chrono::system_clock::to_time_t(time_point);
    std::tm tm_now = *std::localtime(&time_t_now);
    
    int current_hour = tm_now.tm_hour;    // Current hour (0 - 23)
    int current_minute = tm_now.tm_min;  // Current minute (0 - 59)

    if (argc == 1) // default: LED index + letters
    {
        bool silent = false;
        bool detailed = true;
        run(current_hour, current_minute, silent, detailed);
        return 0;
    }

    for (int argIndex = 1; argIndex < argc; ++argIndex) 
    {
        std::string option = argv[argIndex];
        
        if (option == "esp32") 
        {
            bool silent = true;
            bool detailed = true;
            run(current_hour, current_minute, silent, detailed);
            return 0;
        } 
        
        else if (option == "verbose") 
        {
            std::cout << "Current time: " << std::put_time(&tm_now, "%Y-%m-%d %H:%M:%S") << std::endl;
            bool silent = false;
            bool detailed = true;
            run(current_hour, current_minute, silent, detailed);
            return 0;
        } 
        
        else if (option == "log-level") 
        {
            echoLogLevel();
            return 0;
        } 
        
        else if (option == "test-run" && argIndex + 1 < argc) 
        {
            int period = atoi(argv[argIndex + 1]);
            std::cout << "Current time: " << std::put_time(&tm_now, "%Y-%m-%d %H:%M:%S") << std::endl;
            bool silent = false;
            bool detailed = true;
            run(current_hour, current_minute, silent, detailed, period);
            return 0;
        }
        
        else if (option == "simulate-period" && argIndex + 1 < argc) 
        {
            int period = atoi(argv[argIndex + 1]);
            simulate_period(period);
            return 0;
        }
        
        else if (option == "simulate-time" && argIndex + 2 < argc) 
        {
            int hour = atoi(argv[argIndex + 1]);
            int minute = atoi(argv[argIndex + 2]);
            simulate_time(hour, minute);
            return 0;
        }
    }

    std::cerr << "Usage: " << argv[0] << std::endl;
    std::cerr << "[silent]: " << argv[0] << " esp32" << std::endl;
    std::cerr << "[verbose]: " << argv[0] << " verbose" << std::endl;
    std::cerr << "[test any period (default=5)]: " << argv[0] << " test-run [int:period]" << std::endl;
    std::cerr << "[check log level]: " << argv[0] << " log-level" << std::endl;
    std::cerr << "[simulate period (whole day)]: " << argv[0] << " simulate-period [int:period]" << std::endl;
    std::cerr << "[simulate specific time]: " << argv[0] << " simulate-time [int:hour] [int:minute]" << std::endl;
    std::exit(1);
}
