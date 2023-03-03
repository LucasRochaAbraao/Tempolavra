from src.tempolavra.tempolavra import tempolavra


def test_tempolavra():
    """
    manually setting 11:15 to check if tempolavra returns the correct time in words.
    It checks for a subset because tempolavra might return "da tarde" or "da manhã"
    randomly, so we can't check for equality always.
    """
    onze_e_quinze = {"SÃO", "ONZE", "E", "QUINZE"}
    assert onze_e_quinze.issubset(set(tempolavra(11, 15)))
