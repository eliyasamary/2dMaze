#pragma once
#include <iostream>
#include <filesystem>
#include <fstream> // implement!!!

#include "Model.h"
#include "mazeGenerator.h"
#include "Solution.h"

class Controller;
//class Model;

using namespace std;

namespace fs = std::filesystem;


// Command interface
class Command {
public:
    virtual ~Command() {}
    virtual void execute() = 0;
};

// Concrete command classes
class DirCommand : public Command {
public:
    void execute() override {
        string path_str;
        
        cout << "Pleasse enter a dir: ";
        cin >> path_str;
        fs::path path(path_str);

        vector<string> fileAndDirNames;

        if (fs::exists(path) && fs::is_directory(path)) {
            for (const auto& entry : fs::directory_iterator(path)) {
                if (fs::is_regular_file(entry)) {
                    fileAndDirNames.push_back("File: " + entry.path().filename().string());
                }
                else if (fs::is_directory(entry)) {
                    fileAndDirNames.push_back("Directory: " + entry.path().filename().string());
                }
            }
        }
        else {
            std::cerr << "The specified path is not a valid directory." << std::endl;
            return;
        }

        // Print the list of file and directory names
        for (const auto& name : fileAndDirNames) {
            cout << name << std::endl;
        }

        return;
    }
};

class GenerateMazeCommand : public Command , public MazeGenerator {
private:
    Model* myModel;
public:
    GenerateMazeCommand(Model* model) : myModel(model) {}
    Maze* generate(int row_size, int col_size) override {
        Maze* temp = new Maze(row_size, col_size);
        return temp;
    }

    void execute() override {
        string name;
        int rows, cols;
        cout << "Enter maze name: ";
        cin >> name;
        cout << "Number of rows: ";
        cin >> rows;
        cout << "Number of cols: ";
        cin >> cols;
        Maze* temp = generate(rows, cols);
        myModel->addMaze(name, temp);
    }
};

class DisplayCommand : public Command {
private:
    Model* myModel;
public:
    DisplayCommand(Model* model) : myModel(model) {}
    void execute() override {
        myModel->printMazesNames();
        string maze_name;
        cout << "Please enter maze name: ";
        cin >> maze_name;
        if (myModel->checkMaze(maze_name)) {
            cout << endl << "-----------------------" << endl;
            myModel->printMaze(maze_name);
            cout << endl << "-----------------------" << endl;
            cout << "Maze has printed successfully!" << endl;
        }
        else {
            cout << "Maze doesn't exist." << endl;
        }
    }
};

class SaveMazeCommand : public Command {
private:
    Model* myModel;
    MazeCompression* compress;
public:
    SaveMazeCommand(Model* model, MazeCompression* compressor) : myModel(model), compress(compressor) {}
    void execute() override {
        string filename, maze_name;
        cout << "Enter maze name to save: ";
        cin >> maze_name;
        if (myModel->checkMaze(maze_name)) {
            cout << "Enter file name: ";
            cin >> filename;
            Maze* tempMaze = myModel->getMaze(maze_name);
            //compress maze and save it with the name
            compress->compress(tempMaze, filename);
            cout << endl << "-----------------------" << endl;
            cout << "Maze saved successfully!" << endl;
        }
        else {
            cout << "Maze doesn't exist." << endl;
        }
    }
};

class LoadMazeCommand : public Command {
private:
    Model* myModel;
    MazeCompression* compress;
public:
    LoadMazeCommand(Model* model, MazeCompression* compressor) : myModel(model), compress(compressor) {}
    void execute() override {
        string directoryPath = ".";
        string filename, mazename;
        cout << "List of files: " << endl;
        for (const auto& entry : fs::directory_iterator(directoryPath)) {
            if (entry.is_regular_file() && entry.path().extension() == ".txt") {
                std::cout << "File: " << entry.path() << endl;
            }
        }
        cout << "Enter file name (*.txt): ";
        cin >> filename;
        filename += ".txt";   
        for (const auto& entry : fs::directory_iterator(directoryPath)) {
            if (entry.is_regular_file() && entry.path().filename() == filename && entry.path().extension() == ".txt") {
                cout << "Enter new maze name: ";
                cin >> mazename;
                Maze* tempmaze = compress->decompress(filename);
                myModel->addMaze(mazename, tempmaze);
                return;
            }
        }
        cout << "File doesn't exist." << endl;
    }
};

class MazeSizeCommand : public Command {
private:
    Model* myModel;
public:
    MazeSizeCommand(Model* model) : myModel(model) {}
    void execute() override {
        myModel->printMazesNames();
        string maze_name;
        cout << "Please enter maze name: ";
        cin >> maze_name;
        cout << endl << "-----------------------" << endl;
        myModel->printMazeSize(maze_name);
    }
};

class FileSizeCommand : public Command {
public:
    void execute() override {
        string directoryPath = ".";
        //printing the size
        for (const auto& entry : fs::directory_iterator(directoryPath)) {
            if (entry.is_regular_file() && entry.path().extension() == ".txt") {
                std::cout << "File: " << entry.path() << ", Size: " << fs::file_size(entry.path()) << " bytes\n";
            }
        }
    }
};

class SolveCommand : public Command {
private:
    Model* myModel;
    Adapter* myAdapter;
public:
    SolveCommand(Model* model, Adapter* adapter) : myModel(model), myAdapter(adapter) {}
    void execute() override {
        string maze_name;
        cout << "Enter maze name to solve: ";
        cin >> maze_name;
        if (myModel->checkMaze(maze_name)) {
            if (myModel->checkSolution(myModel->getMaze(maze_name))) {
                cout << "This maze already have a solution!" << endl;
                return;
            }
            cout << "Converting to searchable problem..." << endl;
            Searchable* temp = myAdapter->convertToGraph(myModel->getMaze(maze_name));
            int choose = 0;
            while (choose != 1 && choose != 2) {
                cout << "1- BFS / 2- AStar || choose: ";
                cin >> choose;
            }
            if (choose == 1) {
                BFS a;
                Solution solution(a.execute(temp, 1));
                myModel->addSolution(myModel->getMaze(maze_name), solution);
            }
            else if (choose == 2) {
                cout << "AStar solving ..." << endl;
            }
            else {
                cout << "Error" << endl;
            }
            cout << endl << "-----------------------" << endl;
            cout << "Maze solved successfully!" << endl;
        }
        else {
            cout << "No such a maze with this name." << endl;
        }
    }
};

class DisplaySolutionCommand : public Command {
    Model* myModel;
public:
    DisplaySolutionCommand(Model* model) : myModel(model) {}
    void execute() override {
        string maze_name;
        cout << "Please enter maze name: ";
        cin >> maze_name;
        if (myModel->checkSolution(myModel->getMaze(maze_name))) {
            string s = myModel->getSolution(myModel->getMaze(maze_name));
            cout << s << endl;
        }
        else {
            cout << "No such a maze / No solution." << endl;
        }
    }
};

class ExitCommand : public Command {
public:
    void execute() override {
        std::cout << "Exiting the CLI." << std::endl;
        exit(0);
    }
};
