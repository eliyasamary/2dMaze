#pragma once
#include <vector>

using namespace std;

//Graph = Seachable
class Searchable {
	int V; // Number of vertices
	vector<vector<int>> adj; // Adjacency list

public:
	Searchable(int v, vector<vector<int>> e) : V(v), adj(e) {}

	int getV() { return V; }

	vector<vector<int>> getAdj() { return adj; }

};