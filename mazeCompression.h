#pragma once
#include <fstream>

#include "maze.h"


class MazeCompression {
public:
	int compress(Maze* maze, string filename) {

		string str = maze->getData();

		filename += ".txt";
		
			ofstream outputFile(filename);

			if (!outputFile.is_open()) {
				std::cerr << "Unable to open the file for writing." << std::endl;
				return 1;
			}

			outputFile << str;

			outputFile.close();

			std::cout << "Data written to the file." << std::endl;

			return 0;
		
	}
	
	Maze* decompress(const string& compressedFilePath) {

		std::ifstream compressedFile(compressedFilePath);

		if (!compressedFile.is_open()) {
			std::cerr << "Failed to open compressed file." << std::endl;
			return NULL;
		}
		string compressedLine;
		string decompressedString;
		while (getline(compressedFile, compressedLine)) {
			// Assuming each line contains a compressed string
			decompressedString += compressedLine +"\n";
		}
		string res = decompressedString.substr(0, decompressedString.size() - 1);
		Maze* n = new Maze(res);
		return n;
	}

};