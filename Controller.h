#pragma once
#include <map>

#include "Observer.h"
#include "maze.h"
#include "Command.h"
#include "mazeCompression.h"


using namespace std;

class Controller : public Observer {
private:
    Model* mymodel;
    MazeCompression* compress;
    Adapter* adapter;
    friend class Command;

    map<string, Command*> commands;


public:
    Controller(Model* model) : Observer() {
        mymodel = model;
        compress = new MazeCompression();
        adapter = new Adapter();
        DirCommand* dir = new DirCommand();
        GenerateMazeCommand* generatemaze = new GenerateMazeCommand(model);
        DisplayCommand* display = new DisplayCommand(model);
        SaveMazeCommand* savemaze = new SaveMazeCommand(model, compress);
        LoadMazeCommand* loadmaze = new LoadMazeCommand(model, compress);
        MazeSizeCommand* mazesize = new MazeSizeCommand(model);
        FileSizeCommand* filesize = new FileSizeCommand();
        SolveCommand* solve = new SolveCommand(model, adapter);
        DisplaySolutionCommand* displaysolution = new DisplaySolutionCommand(model);
        ExitCommand* exit = new ExitCommand();

        commands["dir"] = (dir);
        commands["generate maze"] = (generatemaze);
        commands["display"] = (display);
        commands["save maze"] = (savemaze);
        commands["load maze"] = (loadmaze);
        commands["maze size"] = (mazesize);
        commands["file size"] = (filesize);
        commands["solve"] = (solve);
        commands["display solution"] = (displaysolution);
        commands["exit"] = (exit);

    }

    ~Controller() {
        free(compress);
        for (const auto& ptr : commands) {
            free(ptr.second);
        }
        commands.clear();
    }

    void update(string message) override {}

    map<string , Command*> getCommands() { return commands; }

};

