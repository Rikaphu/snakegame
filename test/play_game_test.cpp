#include "pch.h"
#include "../snake_game/helpers.cpp"
#include "../snake_game/play_game.cpp"

TEST(play_game, empty_field) {
	snake_game* game = new snake_game(4, 3, new linked_list, new linked_list, -1);

	vector<string> lines = draw_game(game);

	//                   -0123-
	EXPECT_EQ(lines[0], "‹‹‹‹‹‹");
	EXPECT_EQ(lines[1], "€∞∞∞∞€");
	EXPECT_EQ(lines[2], "€∞∞∞∞€");
	EXPECT_EQ(lines[3], "€∞∞∞∞€");
	EXPECT_EQ(lines[4], "ﬂﬂﬂﬂﬂﬂ");
}


TEST(play_game, fruit) {
	int cols = 5;
	int rows = 3;
	int fruit = to_index(4, 1, cols);
	snake_game* game = new snake_game(cols, rows, new linked_list, new linked_list, fruit);

	vector<string> lines = draw_game(game);

	//                   -01234-
	EXPECT_EQ(lines[0], "‹‹‹‹‹‹‹");
	EXPECT_EQ(lines[1], "€∞∞∞∞∞€");
	EXPECT_EQ(lines[2], "€∞∞∞∞o€");
	EXPECT_EQ(lines[3], "€∞∞∞∞∞€");
	EXPECT_EQ(lines[4], "ﬂﬂﬂﬂﬂﬂﬂ");
}


TEST(play_game, walls) {
	int cols = 5;
	int rows = 3;
	linked_list* walls = new linked_list();
	walls->append(to_index(1, 0, cols));
	walls->append(to_index(3, 2, cols));
	snake_game* game = new snake_game(cols, rows, new linked_list, walls, -1);

	vector<string> lines = draw_game(game);

	//                   -01234-
	EXPECT_EQ(lines[0], "‹‹‹‹‹‹‹");
	EXPECT_EQ(lines[1], "€∞€∞∞∞€");
	EXPECT_EQ(lines[2], "€∞∞∞∞∞€");
	EXPECT_EQ(lines[3], "€∞∞∞€∞€");
	EXPECT_EQ(lines[4], "ﬂﬂﬂﬂﬂﬂﬂ");
}


TEST(play_game, snake) {
	int cols = 5;
	int rows = 3;
	linked_list* snake = new linked_list();
	snake->append(to_index(0, 0, cols));
	snake->append(to_index(0, 1, cols));
	snake->append(to_index(1, 1, cols));
	snake->append(to_index(2, 1, cols));
	snake_game* game = new snake_game(cols, rows, snake, new linked_list, -1);

	vector<string> lines = draw_game(game);

	//                   -01234-
	EXPECT_EQ(lines[0], "‹‹‹‹‹‹‹");
	EXPECT_EQ(lines[1], "€≤∞∞∞∞€");
	EXPECT_EQ(lines[2], "€≤≤≤∞∞€");
	EXPECT_EQ(lines[3], "€∞∞∞∞∞€");
	EXPECT_EQ(lines[4], "ﬂﬂﬂﬂﬂﬂﬂ");
}