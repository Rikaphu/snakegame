#pragma once
#include <iostream>
#include <vector>
#include "helpers.h"
#include "linked_list.cpp"

enum direction { UP, DOWN, RIGHT, LEFT };

const int NO_FRUIT = -1;

class snake_game {
private:
	int cols;
	int rows;
	linked_list* snake;
	linked_list* walls;
	int fruit;
	int score = 0;

	direction dir = RIGHT;

public:
	snake_game(int cols, int rows, linked_list* snake, linked_list* walls, int fruit) {
		this->cols = cols;
		this->rows = rows;
		this->snake = snake;
		this->walls = walls;
		this->fruit = fruit;
	}

	int get_cols() { 
		return this->cols; 
	}

	int get_rows() { 
		return this->rows;
	}

	int get_fruit() {
		return this->fruit;
	}

	int get_score() {
		return this->score;
	}

	linked_list* get_walls() {
		return this->walls;
	}

	linked_list* get_snake() {
		return this->snake;
	}

	void set_direction(direction dir) {
		this->dir = dir;
	}

	int next_col() {
		int current_col = to_col(snake->get(0), cols);

		switch (dir) {
			case UP:
				return current_col;
			case DOWN:
				return current_col;
			case RIGHT:
				return current_col + 1;
			case LEFT:
				return current_col - 1;
		}
	}

	int next_row() {
		int current_row = to_row(snake->get(0), cols);

		switch (dir) {
		case UP:
			return current_row - 1;
		case DOWN:
			return current_row + 1;
		case RIGHT:
			return current_row;
		case LEFT:
			return current_row;
		}
	}

	bool is_over() {
		int next_col = this->next_col();
		int next_row = this->next_row();
		int next_index = to_index(next_col, next_row, cols);

		return next_row < 0
			|| next_row >= rows
			|| next_col < 0
			|| next_col >= cols
			|| walls->contains(next_index)
			|| snake->contains(next_index);
	}

	void move_snake() {
		int next_index = to_index(next_col(), next_row(), cols);
			
		snake->prepend(next_index);

		if (next_index != get_fruit()) {
			snake->remove(snake->get_size() - 1);
		}
		else {
			fruit = NO_FRUIT;
			score++;
		}
	}

	void place_fruit() {
		int new_fruit = NO_FRUIT;
		bool collides = false;

		do {
			new_fruit = rand() % (cols * rows - 1);
			collides = snake->contains(new_fruit) || walls->contains(new_fruit);
		} while (collides);

		fruit = new_fruit;
	}
};