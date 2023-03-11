#!/usr/bin/env python3
# coding=utf-8

import sys
from datetime import datetime

from tempolavra.time_to_text import get_time_phrase


# fmt: off
def get_matrix(coords: list) -> list[str]:
    """
    Return a list of LEDs to activate based on given coordinates in the matrix.

        Args:
            coords: List of tuples representing coordinates in the matrix.

        Returns:
            List of strings representing the LEDs to activate.

        Examples
        --------

        >>> get_matrix([(0, 0), (0, 1), (0, 2)])
        ['S', 'Ã', 'O']

        >>> get_matrix([(0, 3)])
        ['É']
    """

    letter_matrix = [
        # 0    1    2    3    4    5    6    7    8    9   10   11   12   13   14
        ['S', 'Ã', 'O', 'É', 'O', 'J', 'G', 'T', 'U', 'R', 'W', 'Z', 'N', 'X', 'A'],  # 0 sao é
        ['E', 'T', 'R', 'Ê', 'S', 'C', 'I', 'N', 'C', 'O', 'A', 'R', 'I', 'K', 'A'],  # 1 tres cinco
        ['U', 'M', 'A', 'Q', 'U', 'A', 'T', 'R', 'O', 'P', 'V', 'I', 'N', 'T', 'E'],  # 2 uma quatro vinte
        ['D', 'H', 'W', 'D', 'U', 'A', 'S', 'Q', 'O', 'I', 'T', 'O', 'L', 'V', 'I'],  # 3 duas oito
        ['O', 'N', 'Z', 'E', 'G', 'S', 'E', 'I', 'S', 'B', 'D', 'E', 'Z', 'A', 'Y'],  # 4 onze seis dez
        ['K', 'J', 'N', 'O', 'V', 'E', 'B', 'Q', 'U', 'I', 'N', 'Z', 'E', 'U', 'F'],  # 5 nove quinze u
        ['W', 'R', 'D', 'O', 'Z', 'E', 'F', 'S', 'E', 'T', 'E', 'B', 'E', 'H', 'T'],  # 6 doze sete e
        ['P', 'R', 'A', 'S', 'M', 'E', 'I', 'O', 'V', 'D', 'I', 'A', 'D', 'A', 'E'],  # 7 pras meio dia da e
        ['V', 'I', 'N', 'T', 'E', 'M', 'E', 'I', 'A', 'Q', 'U', 'I', 'N', 'Z', 'E'],  # 8 vinte meia quinze
        ['N', 'O', 'I', 'T', 'E', 'T', 'R', 'I', 'N', 'T', 'A', 'E', 'F', 'Y', 'X'],  # 9 noite trinta e
        ['N', 'O', 'V', 'E', 'D', 'U', 'A', 'S', 'U', 'M', 'A', 'S', 'E', 'T', 'E'],  # 10 nove duas uma sete
        ['A', 'M', 'O', 'D', 'E', 'Z', 'S', 'E', 'I', 'S', 'H', 'O', 'I', 'T', 'O'],  # 11 dez seis oito
        ['Q', 'U', 'A', 'T', 'R', 'O', 'T', 'R', 'E', 'S', 'C', 'I', 'N', 'C', 'O'],  # 12 quatro tres cinco
        ['H', 'O', 'R', 'A', 'S', 'D', 'I', 'A', 'E', 'M', 'E', 'I', 'A', 'D', 'A'],  # 13 horas dia e meia da
        ['M', 'A', 'N', 'H', 'Ã', 'T', 'A', 'R', 'D', 'E', 'N', 'O', 'I', 'T', 'E']  # 14 manhã tarde noite
        # 0    1    2    3    4    5    6    7    8    9   10   11   12   13   14
    ]

    leds_to_activate = list()
    for word_coords in coords:
        leds_to_activate.append(letter_matrix[word_coords[0]][word_coords[1]])
    return leds_to_activate


def tempolavra(current_hour: int = 0, current_minute: int = 0) -> list[str]:
    """
        Takes current hour and minute as input and returns a list of strings to display the time
        in "TempoLavra" LED matrix format (currently the app only prints to the terminal, but will
        eventually run in an embedded board like the ESP32).

        Args:
            current_hour: Current hour in 24-hour format. Defaults to 0.
            current_minute: Current minute. Defaults to 0.

        Returns:
            List of strings to display the time in "TempoLavra" LED matrix format. This
                currently returns strings, but will eventually become LED indexes.
    """
    # TODO: Move these comments to a new test.
    #interval = 0
    # for _ in range(291):
    #    #time_reference = datetime.now() - timedelta(hours=10, minutes=30)
    #    #time_reference.time()
    #    #time_reference = datetime.now().time()
    #    time_reference = datetime.now() + timedelta(minutes=interval)
    #    current_minute = 5 * round(time_reference.minute/5)
    #    current_hour = time_reference.hour
    #    if current_minute == 60:
    #        current_minute = 0
    #        if current_hour != 23:
    #            current_hour += 1
    #        else:
    #            current_hour = 0
    #    display_phrase = get_time_phrase(current_hour, current_minute)
    #    final_phrase = [''.join(get_matrix(word_list)) for word_list in display_phrase]
    #    print(f"{current_hour}:{current_minute}", ' '.join(final_phrase))
    #    #print(time_reference)
    #    interval += 5

    time_reference = datetime.now()
    if current_hour == 0:
        current_hour: int = time_reference.hour
    if current_minute == 0:
        current_minute: int = 5 * round(time_reference.minute/5)

    if current_minute == 60:
        current_minute = 0
        if current_hour != 23:
            current_hour += 1
        else:
            current_hour = 0

    display_phrase: list = get_time_phrase(current_hour, current_minute)
    final_phrase: list = [''.join(get_matrix(word_list))
                    for word_list in display_phrase]

    return final_phrase


if __name__ == '__main__':
    if len(sys.argv) == 3:
        # it's not pretty, but will remain for debuggin purposes (for now)
        current_time_in_words = tempolavra(int(sys.argv[1]), int(sys.argv[2]))
    else:
        current_time_in_words = tempolavra()

    print(' '.join(current_time_in_words))
