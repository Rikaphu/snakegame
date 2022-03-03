#include "helpers.h"

int to_index(int col, int row, int cols) {
	return cols * row + col;
}

int to_col(int index, int cols) {
	return index % cols;
}

int to_row(int index, int cols) {
	return index / cols;
}