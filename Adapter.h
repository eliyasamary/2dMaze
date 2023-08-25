#pragma once
#include <vector>

#include "Searchable.h"

using namespace std;

class Adapter {
public:
	Searchable* convertToGraph(Maze* maze) {
		int rows = maze->getRowSize();
		int cols = maze->getColSize();
		int size = rows * cols;
		vector<vector<int>> out_vec;
		vector<int> in_vec;
		for (int s = 0; s < size+1; s++) {
			out_vec.push_back(in_vec);
		}
		vector<vector<Cell>> grid = maze->getGrid();
		int counter = 1;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				if (grid[i][j].getWall(UP) == false && counter / cols > 0) {
					out_vec[counter].push_back(counter - cols);
				}
				if (grid[i][j].getWall(DOWN) == false && counter <= (rows - 1) * cols) {
					out_vec[counter].push_back(counter + cols);
				}
				if (grid[i][j].getWall(LEFT) == false && (counter - 1) % cols != 0) {
					out_vec[counter].push_back(counter - 1);
				}
				if (grid[i][j].getWall(RIGHT) == false && counter % cols != 0) {
					out_vec[counter].push_back(counter + 1);
				}
				counter++;
			}
		}
		Searchable* temp = new Searchable(size, out_vec);
		return temp;
	}


};