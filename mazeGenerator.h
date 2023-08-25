#pragma once

#include "maze.h"
#include <chrono>
#include <algorithm>



class MazeGenerator {
public:
	virtual Maze* generate(int row_size, int col_size) = 0;
	void measureAlgorithmTime(int row_size, int col_size) { // input algo
		
		auto start = chrono::high_resolution_clock::now(); // start time

		Maze* temp = generate(row_size, col_size);

		auto stop = chrono::high_resolution_clock::now(); // stop time

		auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
		
		cout << "Measured Time: " << duration.count() << " microseconds." << endl;

		free(temp);
	}


};