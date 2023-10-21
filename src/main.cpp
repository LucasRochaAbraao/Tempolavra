#include <chrono>
#include <ctime>
#include <iomanip> // for std::put_time
#include <iostream>
#include <string>
#include <tuple>
#include <unistd.h>
#include <vector>

#include "../include/time_to_coords.h"

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
        {"V", "I", "N", "T", "E", "M", "E", "I", "A", "Q", "U", "I", "N", "Z", "E"},  // 8 vinte meia quinze
        {"N", "O", "I", "T", "E", "T", "R", "I", "N", "T", "A", "E", "F", "Y", "X"},  // 9 noite trinta e
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
    for (const auto& hour_data : time_coords) {
        // Loop over the inner vector
        for (const auto& coords : hour_data) {
            int column = std::get<0>(coords);
            int row = std::get<1>(coords);
            int index = 1 + (column * 15 + row);
            //std::cout << "Pair: (" << column << " - " << row << " = " << index << ")" << std::endl;
            led_indices.push_back(index);
        }
    }
    return led_indices;
}


int main(int argc, char* argv[])
{
    auto time_point = std::chrono::system_clock::now();
    std::time_t time_t_now = std::chrono::system_clock::to_time_t(time_point);
    std::tm tm_now = *std::localtime(&time_t_now);
    // std::cout << "Current time: " << std::put_time(&tm_now, "%Y-%m-%d %H:%M:%S") << std::endl;

    int current_hour = tm_now.tm_hour;    // Current hour (0 - 23)
    int current_minute = tm_now.tm_min;  // Current minute (0 - 59)

    auto time_coords = get_time_coords(current_hour, current_minute);

    // string with letters representing current hour rounded to nearest 5min
    std::vector<std::string> final_phrase;
    for (const auto& coord : time_coords) {
        auto matrix_word = get_word_from_matrix(coord);
        for (const auto& word : matrix_word) {
            final_phrase.push_back(word);
        }
    }

    // gets an array of LED index to be turned on.
    auto indices = map_matrix_to_1d(time_coords);

    if (argc == 1) { // cout out LED index + letters
        int letter_index {0};
        for (const auto& index : indices) {
            std::cout << "turn on LED: " << index;
            std::cout << " - " << final_phrase[letter_index] << std::endl;
            letter_index++;
        }
        return 0;
    }
    else if (argc > 1) { // cout LED index only.
        std::string option = argv[1]; // only accepts "LED" as an option, otherwise error out
        if (option == "LED") {
            for (const auto& index : indices) {
                std::cout << index << std::endl;
            }
            std::cout << std::endl;
            return 0;
        }
    }
    else {
        std::cerr << "Usage: " << argv[0] << " [LED]" << std::endl;
        std::exit(1);
    }
}
