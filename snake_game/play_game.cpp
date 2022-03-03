#include "helpers.h"
#include "play_game.h"

using namespace std;

string upper_wall(int length) {
	string wall;
	for (int i = 0; i < length; i++) {
		wall += 'Ü';
	}
	return wall;
}

string lower_wall(int length) {
	string wall;
	for (int i = 0; i < length; i++) {
		wall += 'ß';
	}
	return wall;
}

vector<string> draw_game(snake_game* game) {
	int rows = game->get_rows();
	int cols = game->get_cols();
	vector<string> lines(rows + 2);

	lines[0] = upper_wall(cols + 2);
	lines[rows + 1] = lower_wall(cols + 2);

	for (int row = 0; row < rows; row++) {
		string line;
		line += 'Û';
		for (int col = 0; col < cols; col++) {
			int index = to_index(col, row, cols);
			
			if (game->get_fruit() == index) {
				line += 'o';
			}
			else if (game->get_walls()->contains(index)) {
				line += 'Û';
			}
			else if (game->get_snake()->contains(index)) {
				line += '²';
			}
			else {
				line += '°';
			}
		}
		line += 'Û';
		lines[row + 1] = line;
	}

	return lines;
}
