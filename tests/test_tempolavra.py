from tempolavra.tempolavra import get_matrix, main


def test_tempolavra():
    # Manually setting 11:15 to check if tempolavra returns the correct time in words.
    # It checks for a subset because tempolavra might return "da tarde" or "da manhã"
    # randomly, so we can't check for equality always.
    onze_e_quinze = {"SÃO", "ONZE", "E", "QUINZE"}
    assert onze_e_quinze.issubset(set(main(11, 15)))


def test_get_matrix():
    # For now, this asserts that the results are letter strings, but eventually
    # this will change to LED indexes.
    assert get_matrix([(0, 0), (0, 1), (0, 2)]) == ["S", "Ã", "O"]

    assert get_matrix([(0, 3)]) == ["É"]

    assert get_matrix([(2, 3), (2, 4), (2, 5), (2, 6), (2, 7), (2, 8)]) == [
        "Q",
        "U",
        "A",
        "T",
        "R",
        "O",
    ]

    assert get_matrix([(10, 4), (10, 5), (10, 6), (10, 7)]) == ["D", "U", "A", "S"]
