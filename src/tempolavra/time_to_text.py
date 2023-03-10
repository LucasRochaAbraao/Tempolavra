# coding=utf-8

import random

from tempolavra.time_coords import WordPosition, get_coord_hour, get_coord_minute


def flip_coin(weight: float) -> bool:
    """
    Simulates a coin flip with a given weight bias.

    Args:
        weight: A value between 0 and 1 representing the weight or bias.

    Returns:
        Returns True if a random value is less than the given weight and False otherwise.

    Raises:
        ValueError: If the weight is not between 0 and 1.
    """

    if weight < 0 or weight > 1:
        raise ValueError("Weight must be between 0 and 1")
    if weight == 0:
        return False

    reference = random.getrandbits(3) / 7
    return True if weight >= reference else False


def get_time_phrase(hour: int, minute: int) -> list[list[tuple[int, int]]]:
    """
    Creates the phrase from a list of words that can be used to make up the word clock.

    Args:
        hour: The hour value of the time to be displayed (0-23).
        minute: The minute value of the time to be displayed (0-59).

    Returns:
        A list of coordinates that make up the word positions in a matrix.
    """

    coords = list()  # create coordinates to activate leds in a matrix

    minute = 5 * round(minute / 5)  # make minute a multiple of 5 (wordclock precision)
    if minute == 60:
        minute = 0  # rounds minutes above 55 to the next hour.
        if hour != 23:  # any hour except 23
            hour += 1  # round up to the next hour in this case
        else:
            hour = 0  # except when the hour is 23, in which case it needs to be 0 and not 24.

    # é 1h..., é meio dia..., é meia noite...
    if (hour == 1 or hour == 12 or hour == 13 or hour == 0) and minute == 0:
        # if flip_coin(weight=0.9): # weight returns True or False
        #    phrase += ['é']
        # I still need to adjust the probability of not including "é" or "são",
        # because it could come out as: dez cinco pras da noite 21:55.
        coords.append([(0, 3)])  # é
        # phrase += matrix[time_words2['é'][0]][matrix[time_words2['é'][0]]]
    else:
        # if flip_coin(weight=0.9): # weight returns True or False
        #    phrase += ['são']
        coords.append([(0, 0), (0, 1), (0, 2)])  # são

    if minute >= 40:
        hour += 1
        if hour == 24:
            hour = 0

    # get HOUR coords
    if hour == 0:
        coords.append([(8, 5), (8, 6), (8, 7), (8, 8)])  # meia
        coords.append([(14, 10), (14, 11), (14, 12), (14, 13), (14, 14)])  # noite
        if minute == 0:
            return coords

    elif hour == 12:
        coords.append([(7, 4), (7, 5), (7, 6), (7, 7)])  # meio
        coords.append([(7, 9), (7, 10), (7, 11)])  # dia
        if minute == 0:
            return coords

    else:  # if not one of the special words above, get the hour coords
        coords.append(get_coord_hour(hour, pos=WordPosition.primary))

    # get MINUTE coords
    if minute == 0 and (hour == 1 or hour == 13):
        coords.append([(13, 0), (13, 1), (13, 2), (13, 3)])  # hora
        return coords

    if minute == 0:
        if hour < 12:
            coords.append([(13, 0), (13, 1), (13, 2), (13, 3), (13, 4)])  # horas
            if flip_coin(weight=0.8):  # weight returns True or False
                coords.append([(13, 13), (13, 14)])  # da
                coords.append([(14, 0), (14, 1), (14, 2), (14, 3), (14, 4)])  # manhã
        elif 12 < hour < 18:
            coords.append([(13, 0), (13, 1), (13, 2), (13, 3), (13, 4)])  # horas
            if flip_coin(weight=0.5):  # weight returns True or False
                coords.append(
                    [(13, 13), (13, 14)]  # pragma: no cover
                )  # da (this is flaky in test coverage because of weighted chance)
                coords.append(
                    [(14, 5), (14, 6), (14, 7), (14, 8), (14, 9)]  # pragma: no cover
                )  # tarde (also flaky for same reason)
        else:
            coords.append([(13, 0), (13, 1), (13, 2), (13, 3), (13, 4)])  # horas
            if flip_coin(weight=0.6):  # weight returns True or False
                coords.append([(13, 13), (13, 14)])  # da
                coords.append([(14, 10), (14, 11), (14, 12), (14, 13), (14, 14)])  # noite
        return coords

    elif minute == 25:
        coords.append([(6, 12)])  # e
        coords.append([(8, 0), (8, 1), (8, 2), (8, 3), (8, 4)])  # vinte
        coords.append([(6, 12)])  # e
        coords.append([(12, 10), (12, 11), (12, 12), (12, 13), (12, 14)])  # cinco

    elif minute == 35:
        coords.append([(6, 12)])  # e
        coords.append([(9, 5), (9, 6), (9, 7), (9, 8), (9, 9), (9, 10)])  # trinta
        coords.append([(6, 12)])  # e
        coords.append([(12, 10), (12, 11), (12, 12), (12, 13), (12, 14)])  # cinco

    elif minute == 40:
        coords.insert(1, [(2, 10), (2, 11), (2, 12), (2, 13), (2, 14)])  # vinte
        if hour == 1 or hour == 12 or hour == 13 or hour == 0:
            coords.insert(2, [(7, 0), (7, 1), (7, 2)])  # pra
        else:
            coords.insert(2, [(7, 0), (7, 1), (7, 2), (7, 3)])  # pras

    elif minute == 45:
        coords.insert(1, [(5, 7), (5, 8), (5, 9), (5, 10), (5, 11), (5, 12)])
        if hour == 1 or hour == 12 or hour == 13 or hour == 0:
            coords.insert(2, [(7, 0), (7, 1), (7, 2)])  # pra
        else:
            coords.insert(2, [(7, 0), (7, 1), (7, 2), (7, 3)])  # pras

    elif minute == 50:
        coords.insert(1, [(4, 10), (4, 11), (4, 12)])
        if hour == 1 or hour == 12 or hour == 13 or hour == 0:
            coords.insert(2, [(7, 0), (7, 1), (7, 2)])  # pra
        else:
            coords.insert(2, [(7, 0), (7, 1), (7, 2), (7, 3)])  # pras

    elif minute == 55:
        coords.insert(1, [(1, 5), (1, 6), (1, 7), (1, 8), (1, 9)])  # cinco
        if hour == 1 or hour == 12 or hour == 13 or hour == 0:
            coords.insert(2, [(7, 0), (7, 1), (7, 2)])  # pra
        else:
            coords.insert(2, [(7, 0), (7, 1), (7, 2), (7, 3)])  # pras

    else:  # If not one of the special words above, get regular minute
        coords.append([(9, 11)])  # e
        coords.append(get_coord_minute(minute, pos=WordPosition.secondary))  # minute

    # Time of Day
    if 0 < hour < 12:
        if flip_coin(weight=0.8):  # weight returns True or False
            coords.append([(13, 13), (13, 14)])  # da
            coords.append([(14, 0), (14, 1), (14, 2), (14, 3), (14, 4)])  # manhã

    elif 13 <= hour < 19:
        if flip_coin(weight=0.8):  # weight returns True or False
            coords.append([(13, 13), (13, 14)])  # da
            coords.append([(14, 5), (14, 6), (14, 7), (14, 8), (14, 9)])  # tarde
    elif (19 <= hour < 23) or (hour == 23 and minute <= 59):
        if flip_coin(weight=0.8):  # weight returns True or False
            coords.append([(13, 13), (13, 14)])  # da
            coords.append([(14, 10), (14, 11), (14, 12), (14, 13), (14, 14)])  # noite

    return coords
