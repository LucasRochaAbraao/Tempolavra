import pytest

from tempolavra.tempolavra import get_matrix
from tempolavra.time_coords import WordPosition, get_coord_hour, get_coord_minute
from tempolavra.time_to_text import flip_coin, get_time_phrase


def test_flip_coin():
    # Test that the function returns a boolean value
    result = flip_coin(0.5)
    assert isinstance(result, bool)

    # Test that the function returns True if weight is 1.0
    result = flip_coin(1.0)
    assert result == True

    # Test that the function returns False if weight is 0.0
    result = flip_coin(0.0)
    assert result == False

    # Test that the function raises a TypeError if weight is not a float
    with pytest.raises(TypeError):
        flip_coin("1")

    # Test that the function raises a ValueError if weight is less than 0 or greater than 1
    with pytest.raises(ValueError):
        flip_coin(-0.1)

    with pytest.raises(ValueError):
        flip_coin(1.1)


def test_get_time_phrase_types():
    # Test that the function returns the correct object structure
    assert isinstance(get_time_phrase(5, 30), list)  # the function should return a list
    assert all(isinstance(row, list) for row in get_time_phrase(5, 30))  # each row should be a list
    assert all(
        isinstance(cell, tuple) for row in get_time_phrase(5, 30) for cell in row
    )  # each cell should be a tuple


def test_get_time_phrase_general_results():
    # Test cases for various hours and minutes
    test_cases = (
        (0, 0, "É MEIA NOITE"),
        (0, 20, "SÃO MEIA NOITE E VINTE"),
        (0, 25, "SÃO MEIA NOITE E VINTE E CINCO"),
        (0, 30, "SÃO MEIA NOITE E MEIA"),
        (0, 35, "SÃO MEIA NOITE E TRINTA E CINCO"),
        (0, 40, "SÃO VINTE PRA UMA"),
        (0, 45, "SÃO QUINZE PRA UMA"),
        (0, 50, "SÃO DEZ PRA UMA"),
        (0, 55, "SÃO CINCO PRA UMA"),
        (1, 0, "É UMA HORA"),
        (1, 30, "SÃO UMA E MEIA"),
        (1, 40, "SÃO VINTE PRAS DUAS"),
        (1, 45, "SÃO QUINZE PRAS DUAS"),
        (1, 50, "SÃO DEZ PRAS DUAS"),
        (1, 55, "SÃO CINCO PRAS DUAS"),
        (2, 0, "SÃO DUAS HORAS"),
        (2, 30, "SÃO DUAS E MEIA"),
        (2, 55, "SÃO CINCO PRAS TRÊS"),
        (3, 0, "SÃO TRÊS HORAS"),
        (3, 30, "SÃO TRÊS E MEIA"),
        (3, 55, "SÃO CINCO PRAS QUATRO"),
        (4, 0, "SÃO QUATRO HORAS"),
        (4, 30, "SÃO QUATRO E MEIA"),
        (4, 55, "SÃO CINCO PRAS CINCO"),
        (5, 0, "SÃO CINCO HORAS"),
        (5, 30, "SÃO CINCO E MEIA"),
        (5, 55, "SÃO CINCO PRAS SEIS"),
        (6, 0, "SÃO SEIS HORAS"),
        (6, 30, "SÃO SEIS E MEIA"),
        (6, 55, "SÃO CINCO PRAS SETE"),
        (7, 0, "SÃO SETE HORAS"),
        (7, 30, "SÃO SETE E MEIA"),
        (7, 55, "SÃO CINCO PRAS OITO"),
        (8, 0, "SÃO OITO HORAS"),
        (8, 30, "SÃO OITO E MEIA"),
        (8, 55, "SÃO CINCO PRAS NOVE"),
        (9, 0, "SÃO NOVE HORAS"),
        (9, 30, "SÃO NOVE E MEIA"),
        (9, 55, "SÃO CINCO PRAS DEZ"),
        (10, 0, "SÃO DEZ HORAS"),
        (10, 30, "SÃO DEZ E MEIA"),
        (10, 55, "SÃO CINCO PRAS ONZE"),
        (11, 0, "SÃO ONZE HORAS"),
        (11, 30, "SÃO ONZE E MEIA"),
        (11, 55, "SÃO CINCO PRA MEIO DIA"),
        (12, 0, "É MEIO DIA"),
        (12, 30, "SÃO MEIO DIA E MEIA"),
        (12, 55, "SÃO CINCO PRA UMA"),
        (13, 0, "É UMA HORA"),
        (13, 30, "SÃO UMA E MEIA"),
        (13, 55, "SÃO CINCO PRAS DUAS"),
        (14, 0, "SÃO DUAS HORAS"),
        (14, 30, "SÃO DUAS E MEIA"),
        (14, 55, "SÃO CINCO PRAS TRÊS"),
        (15, 0, "SÃO TRÊS HORAS"),
        (15, 30, "SÃO TRÊS E MEIA"),
        (15, 55, "SÃO CINCO PRAS QUATRO"),
        (16, 0, "SÃO QUATRO HORAS"),
        (16, 30, "SÃO QUATRO E MEIA"),
        (16, 55, "SÃO CINCO PRAS CINCO"),
        (17, 0, "SÃO CINCO HORAS"),
        (17, 30, "SÃO CINCO E MEIA"),
        (17, 55, "SÃO CINCO PRAS SEIS"),
        (18, 0, "SÃO SEIS HORAS"),
        (18, 30, "SÃO SEIS E MEIA"),
        (18, 55, "SÃO CINCO PRAS SETE"),
        (19, 0, "SÃO SETE HORAS"),
        (19, 30, "SÃO SETE E MEIA"),
        (19, 55, "SÃO CINCO PRAS OITO"),
        (20, 0, "SÃO OITO HORAS"),
        (20, 30, "SÃO OITO E MEIA"),
        (20, 55, "SÃO CINCO PRAS NOVE"),
        (21, 0, "SÃO NOVE HORAS"),
        (21, 30, "SÃO NOVE E MEIA"),
        (21, 55, "SÃO CINCO PRAS DEZ"),
        (22, 0, "SÃO DEZ HORAS"),
        (22, 30, "SÃO DEZ E MEIA"),
        (22, 55, "SÃO CINCO PRAS ONZE"),
        (23, 0, "SÃO ONZE HORAS"),
        (23, 30, "SÃO ONZE E MEIA"),
        (23, 55, "SÃO CINCO PRA MEIA NOITE"),
    )

    for hour, minute, expected_phrase in test_cases:
        result = get_time_phrase(hour, minute)
        final_phrase = " ".join(["".join(get_matrix(word_list)) for word_list in result])
        assert expected_phrase in final_phrase


def test_get_time_phrase_corner_cases_results():
    # Tests corner cases
    test_cases = (
        (23, 55, "SÃO CINCO PRA MEIA NOITE"),
        (23, 54, "SÃO CINCO PRA MEIA NOITE"),
        (23, 59, "É MEIA NOITE"),
        (22, 59, "SÃO ONZE HORAS"),
    )

    for hour, minute, expected_phrase in test_cases:
        result = get_time_phrase(hour, minute)
        final_phrase = " ".join(["".join(get_matrix(word_list)) for word_list in result])
        assert expected_phrase in final_phrase
