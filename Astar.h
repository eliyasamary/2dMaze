#pragma once
#include <iostream>

#include "Adapter.h"
#include "Algorithm.h"

using namespace std;

class Astar : public Algorithm {
	void execute(Searchable* g, int s) override {
		cout << "Astar Algorithm" << endl;
	}
};

