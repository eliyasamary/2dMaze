#pragma once
#include <iostream>
#include <vector>
#include <queue>

#include "Adapter.h"
#include "Algorithm.h"

using namespace std;

class BFS : public Algorithm {

public:
    
    string execute(Searchable* g, int s) override {
        vector<vector<int>> adj = g->getAdj();
        
        vector<bool> visited(g->getV()+1, false); // Keep track of visited vertices        
        queue<int> q;

        visited[s] = true;
        q.push(s);

        string solution;

        solution += "Vertex:";

        while (!q.empty()) {
            int current = q.front();
            q.pop();
            string temp = to_string(current);
            solution += temp + " -> ";

            for (int neighbor : adj[current]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        return solution;
    }
};