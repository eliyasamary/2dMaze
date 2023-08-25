#include "maze.h"
#include "mazeCompression.h"
#include "SimpleMazeGenerator.h"
#include "BFS.h"
#include "Controller.h"
#include "View.h"
#include "Model.h"

int main() {
	string str = "start";
	Model* myModel = new Model(str);
	Controller myController(myModel);
	Controller* p = &myController;
	CLI cli(cin, cout, p);
	cli.start();
	free(myModel);
	return 0;
}