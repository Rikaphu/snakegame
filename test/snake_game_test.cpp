#include "pch.h"
#include "../snake_game/helpers.h"
#include "../snake_game/snake_game.cpp"


linked_list* NO_WALLS = new linked_list;
TEST(snake_game, next_col_row) {
	int cols = 5;
	int rows = 3;

	linked_list* snake = new linked_list();
	snake->append(to_index(1, 1, cols));

	snake_game* game = new snake_game(cols, rows, snake, NO_WALLS, NO_FRUIT);

	game->set_direction(UP);

	EXPECT_EQ(1, game->next_col());
	EXPECT_EQ(0, game->next_row());

	game->set_direction(DOWN);

	EXPECT_EQ(1, game->next_col());
	EXPECT_EQ(2, game->next_row());

	game->set_direction(RIGHT);

	EXPECT_EQ(2, game->next_col());
	EXPECT_EQ(1, game->next_row());

	game->set_direction(LEFT);

	EXPECT_EQ(0, game->next_col());
	EXPECT_EQ(1, game->next_row());
}

TEST(snake_game, is_game_over_upper_right) {
	int cols = 3;
	int rows = 2;

	linked_list* snake = new linked_list();
	snake->append(to_index(2, 0, cols));

	snake_game* game = new snake_game(cols, rows, snake, NO_WALLS, NO_FRUIT);

	game->set_direction(UP);
	EXPECT_TRUE(game->is_over());

	game->set_direction(RIGHT);
	EXPECT_TRUE(game->is_over());

	game->set_direction(DOWN);
	EXPECT_FALSE(game->is_over());

	game->set_direction(LEFT);
	EXPECT_FALSE(game->is_over());
}

TEST(snake_game, is_game_over_lower_left) {
	int cols = 3;
	int rows = 2;

	linked_list* snake = new linked_list();
	snake->append(to_index(0, 1, cols));

	snake_game* game = new snake_game(cols, rows, snake, NO_WALLS, NO_FRUIT);

	game->set_direction(UP);
	EXPECT_FALSE(game->is_over());

	game->set_direction(RIGHT);
	EXPECT_FALSE(game->is_over());

	game->set_direction(DOWN);
	EXPECT_TRUE(game->is_over());

	game->set_direction(LEFT);
	EXPECT_TRUE(game->is_over());
}

TEST(snake_game, is_game_over_wall_snake) {
	int cols = 4;
	int rows = 3;

	linked_list* snake = new linked_list();
	snake->append(to_index(1, 1, cols));
	snake->append(to_index(1, 2, cols));
	snake->append(to_index(0, 2, cols));

	linked_list* walls = new linked_list();
	snake->append(to_index(2, 1, cols));

	//   -01234-
	//   ÜÜÜÜÜÜÜ
	// 0 Û°°°°°Û
	// 1 Û°SÛ°°Û
	// 2 Û²²°°°Û
	//   ßßßßßßß

	snake_game* game = new snake_game(cols, rows, snake, walls, NO_FRUIT);

	game->set_direction(UP);
	EXPECT_FALSE(game->is_over());

	game->set_direction(RIGHT);
	EXPECT_TRUE(game->is_over());

	game->set_direction(DOWN);
	EXPECT_TRUE(game->is_over());

	game->set_direction(LEFT);
	EXPECT_FALSE(game->is_over());
}

TEST(snake_game, move_snake) {
	int cols = 4;
	int rows = 3;

	linked_list* snake = new linked_list();
	snake->append(to_index(2, 1, cols));
	snake->append(to_index(1, 1, cols));
	snake->append(to_index(0, 1, cols));

	//   -01234-
	//   ÜÜÜÜÜÜÜ
	// 0 Û°°°°°Û
	// 1 Û²²S°°Û
	// 2 Û°°°°°Û
	//   ßßßßßßß

	snake_game* game = new snake_game(cols, rows, snake, NO_WALLS, NO_FRUIT);

	game->set_direction(UP);
	game->move_snake();

	//   -01234-
	//   ÜÜÜÜÜÜÜ
	// 0 Û°°S°°Û
	// 1 Û°²²°°Û
	// 2 Û°°°°°Û
	//   ßßßßßßß

	EXPECT_EQ(3, game->get_snake()->get_size());
	EXPECT_EQ(to_index(2, 0, cols), game->get_snake()->get(0));
	EXPECT_EQ(to_index(2, 1, cols), game->get_snake()->get(1));
	EXPECT_EQ(to_index(1, 1, cols), game->get_snake()->get(2));
}

TEST(snake_game, eat_fruit) {
	int cols = 7;
	int rows = 5;

	int fruit = to_index(2, 3, cols);

	linked_list* snake = new linked_list();
	snake->append(to_index(1, 3, cols));
	snake->append(to_index(0, 3, cols));

	//   -0123456-
	//   ÜÜÜÜÜÜÜÜÜ
	// 0 Û°°°°°°°Û
	// 1 Û°°°°°°°Û
	// 2 Û°°°°°°°Û
	// 3 Û²²o°°°°Û
	// 4 Û°°°°°°°Û
	//   ßßßßßßßßß

	snake_game* game = new snake_game(cols, rows, snake, NO_WALLS, fruit);

	EXPECT_EQ(2, snake->get_size());


	game->set_direction(RIGHT);
	game->move_snake();

	//   -0123456-
	//   ÜÜÜÜÜÜÜÜÜ
	// 0 Û°°°°°°°Û
	// 1 Û°°°°°°°Û
	// 2 Û°°°°°°°Û
	// 3 Û²²²°°°°Û
	// 4 Û°°°°°°°Û
	//   ßßßßßßßßß

	EXPECT_EQ(3, snake->get_size());

	EXPECT_EQ(NO_FRUIT, game->get_fruit());
}

TEST(snake_game, place_fruit_randomly) {
	int cols = 6;
	int rows = 5;

	linked_list* snake = new linked_list();
	snake->append(to_index(1, 0, cols));
	snake->append(to_index(2, 0, cols));
	snake->append(to_index(3, 0, cols));
	snake->append(to_index(4, 0, cols));
	snake->append(to_index(4, 1, cols));

	linked_list* walls = new linked_list();
	walls->append(to_index(2, 4, cols));
	walls->append(to_index(2, 3, cols));
	walls->append(to_index(2, 2, cols));

	snake_game* game = new snake_game(cols, rows, snake, walls, NO_FRUIT);;

	for (int i = 0; i < 1000; i++) {

		game->place_fruit();

		EXPECT_FALSE(game->get_snake()->contains(game->get_fruit()));
		EXPECT_FALSE(game->get_walls()->contains(game->get_fruit()));

		EXPECT_TRUE(game->get_fruit() >= 0);
		EXPECT_TRUE(game->get_fruit() <= cols * rows - 1);
	}
}