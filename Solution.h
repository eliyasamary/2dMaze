#pragma once
#include <string>

using namespace std;

class Solution {
	string solute;
public:
	Solution(string solution) {
		solute = solution;
	}
	Solution() {}
	string getSolute() { return solute; }
};