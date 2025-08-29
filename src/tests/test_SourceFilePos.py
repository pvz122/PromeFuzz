from src.generator.extractor import SourceFilePos
from pathlib import Path

def run():
    test_pos = SourceFilePos.from_location_line(str(Path(__file__).parent / "Duino.txt") + ":6:10")

    assert test_pos.col == 10
    assert test_pos.line == 6
    assert test_pos.index == 186
    assert test_pos.cur_char == "e"
    assert test_pos.cur_line == "stronger existence. For beauty is nothing but"
    print(test_pos.human_str)

    test_pos.set_to_start_of_line()
    assert test_pos.cur_char == "s"
    print(test_pos.human_str)

    test_pos.set_to_end_of_line()
    assert test_pos.cur_char == "\n"
    print(test_pos.human_str)

    test_pos.set_forward(18)
    assert test_pos.cur_char == "t"
    print(test_pos.human_str)

    s = ""
    for _ in range(18):
        test_pos.set_to_next_char()
        s+=test_pos.cur_char
    assert s == "error, that we are"
    print(test_pos.human_str)

    home_pos = test_pos.find_str("home")
    assert home_pos.line == 14
    assert home_pos.col == 27
    assert home_pos.cur_line == "that we are not really at home"
    print(home_pos.human_str)

    test_pos += 300
    assert test_pos.is_in_same_line(home_pos)
    print(test_pos.human_str)

    test_pos += 20
    test_pos.set_to_end_of_line()
    print(test_pos.get_content_till_pos(home_pos))