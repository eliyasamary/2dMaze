#pragma once

#include "mazeGenerator.h"

class SimpleMazeGenerator : public MazeGenerator {
	int X;
public:
	SimpleMazeGenerator(int x) {
		X = x;
	};
	Maze* generate(int row_size, int col_size) {
		Maze* temp = new Maze(row_size, col_size);
		return temp;
	}
};