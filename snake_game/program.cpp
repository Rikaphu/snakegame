#include "play_game.h"
#include <conio.h>
#include <time.h>
#include <thread>


void print_game(snake_game* game) {
	vector<string> lines = draw_game(game);

	system("cls");
	for (int i = 0; i < lines.size(); i++)
		cout << lines[i] << "\n";
	cout << "score: " << game->get_score();
}

snake_game* initialize_game() {
	int cols = 50;
	int rows = 15;

	linked_list* snake = new linked_list();

	snake->append(to_index(0, 0, cols));

	//for (int i = 0; i <= 3; i++) {
	//	snake->append(to_index(0, 0, cols));
	//}

	srand(time(NULL));
	linked_list* walls = new linked_list();
	//for (int i = 0; i < 800; i++) {
	//	walls->append(to_index(rand() % cols, rand() % rows, cols));
	//}

	snake_game* game = new snake_game(cols, rows, snake, walls, NO_FRUIT);
	game->place_fruit();

	return game;
}



int main()
{
	snake_game* game = initialize_game();

	std::thread thr([game] {
		char command;
		while (true) {
			command = _getch();

			if (command == 'w') game->set_direction(UP);
			if (command == 'a') game->set_direction(LEFT);
			if (command == 's') game->set_direction(DOWN);
			if (command == 'd') game->set_direction(RIGHT);
			if (command == 'l') exit(0);
		}
	});

	bool is_game_over = false;
	do {
		print_game(game);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

		is_game_over = game->is_over();

		if (!is_game_over) {
			game->move_snake();
			if (game->get_fruit() == NO_FRUIT)
				game->place_fruit();
		}
	} while (!is_game_over);

	thr.detach();
}