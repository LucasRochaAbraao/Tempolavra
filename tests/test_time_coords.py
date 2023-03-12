import pytest

from tempolavra.time_coords import WordPosition, get_coord_hour, get_coord_minute


def test_get_coord_hour():
    # Testing primary position
    assert get_coord_hour(3) == [
        (1, 1),
        (1, 2),
        (1, 3),
        (1, 4),
    ]  # tres
    assert get_coord_hour(6) == [
        (4, 5),
        (4, 6),
        (4, 7),
        (4, 8),
    ]  # seis
    assert get_coord_hour(12) == [
        (7, 4),
        (7, 5),
        (7, 6),
        (7, 7),
        (7, 9),
        (7, 10),
        (7, 11),
    ]  # meio dia

    # Testing secondary position
    assert get_coord_hour(2, WordPosition.secondary) == [
        (10, 4),
        (10, 5),
        (10, 6),
        (10, 7),
    ]  # duas
    assert get_coord_hour(5, WordPosition.secondary) == [
        (12, 10),
        (12, 11),
        (12, 12),
        (12, 13),
        (12, 14),
    ]  # cinco
    assert (
        get_coord_hour(11, WordPosition.secondary) == []
    )  # onze (empty because it doesn't have a sec pos)


def test_get_coord_minute():
    # Testing primary position
    assert get_coord_minute(5) == [
        (1, 5),
        (1, 6),
        (1, 7),
        (1, 8),
        (1, 9),
    ]  # cinco
    assert get_coord_minute(10) == [
        (4, 10),
        (4, 11),
        (4, 12),
    ]  # dez
    assert get_coord_minute(15) == [
        (5, 7),
        (5, 8),
        (5, 9),
        (5, 10),
        (5, 11),
        (5, 12),
    ]  # quinze

    # Testing secondary position
    assert get_coord_minute(20, WordPosition.secondary) == [
        (8, 0),
        (8, 1),
        (8, 2),
        (8, 3),
        (8, 4),
    ]  # vinte
    assert get_coord_minute(30, WordPosition.secondary) == [
        (13, 9),
        (13, 10),
        (13, 11),
        (13, 12),
    ]  # meia


def test_get_coord_hour_raises_error():
    with pytest.raises(KeyError):
        get_coord_hour(24)


def test_get_coord_minute_raises_error():
    with pytest.raises(KeyError):
        get_coord_minute(40)
