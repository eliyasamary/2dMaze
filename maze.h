#pragma once

#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <string>
#include <random>


using namespace std;

//const int rows = 10;
//const int cols = 10;

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Position {
private:
    int row;
    int col;
public:
    Position(int Row, int Col) {
        this->row = Row;
        this->col = Col;
    }
    void printPosition() {
        cout << "row: " << row << endl << "col: " << col << endl;
    }
    int getRow() { return row; }
    int getCol() { return col; }
};

class Cell {
private:
    int row;
    int col;
    bool visited = false;
    bool walls[4] = { true, true, true, true }; // Up, Down, Left, Right
public:
    Cell(int Row, int Col) : row(Row), col(Col), visited(false) {}
    Cell(int Row, int Col, string& compressedCellData) : row(Row), col(Col), visited(false) {
        walls[0] = (compressedCellData[0]=='1') ? true : false;
        walls[1] = (compressedCellData[1] == '1') ? true : false;
        walls[2] = (compressedCellData[2] == '1') ? true : false;
        walls[3] = (compressedCellData[3] == '1') ? true : false;

    }

    Cell& operator=(Cell &cell) {
        if (this == &cell) {
            return *this;
        }
        row = cell.row;
        col = cell.col;
        visited = cell.visited;
        for (int i = 0; i < 4; i++) {
            walls[i] = cell.walls[i];
        }

        return *this;
    }

    bool getVisited() { return visited; }
    void setVisited(bool Visited) { visited = Visited; }
    bool getWall(Direction dir) {
        switch (dir)
        {
        case UP:
            return (walls[0] == true);
            break;
        case DOWN:
            return (walls[1] == true);
            break;
        case LEFT:
            return (walls[2] == true);
            break;
        case RIGHT:
            return (walls[3] == true);
            break;
        default:
            break;
        }
    }
    void setWall(Direction dir, bool isWall) {
        switch (dir)
        {
        case UP:
            walls[0] = isWall;
            break;
        case DOWN:
            walls[1] = isWall;
            break;
        case LEFT:
            walls[2] = isWall;
            break;
        case RIGHT:
            walls[3] = isWall;
            break;
        default:
            break;
        }
    }
    int getRow() { return row; }
    void setRow(int Row) { row = Row; }
    int getCol() { return col; }
    void setCol(int Col) { col = Col; }

    string compressCell() const {
        string compressedCell;

        // Serialize cell attributes
        compressedCell += (walls[0] == true ? '1' : '0');
        compressedCell += (walls[1] == true ? '1' : '0');
        compressedCell += (walls[2] == true ? '1' : '0');
        compressedCell += (walls[3] == true ? '1' : '0');

        return compressedCell;
    }

  
};

class Maze {
private:
    string name;
    vector<vector<Cell>> grid;
    stack<pair<int, int>> backtrackStack;
    Cell* startPosition;
    Cell* goalPosition;
    int rowSize;
    int colSize;

public:
    Maze(int rows, int cols) : rowSize(rows), colSize(cols) {
        grid = vector<vector<Cell>>(rows, vector<Cell>(cols, Cell(rows, cols)));
        srand(time(0)); // Seed the random number generator
        generateMaze(0, 0); // Generate maze starting from (0, 0)
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                grid[i][j].setRow(i);
                grid[i][j].setCol(j);
            }
        }
        startPosition = &grid[0][0];
        pair<int, int> p = backtrackStack.top();
        goalPosition = &grid[p.first][p.second];
    }

    Maze(string & compressedData) {
        vector<string> parts = splitString(compressedData, '@');

        rowSize = stringToInt(parts[0]);
        colSize = stringToInt(parts[1]); 

        vector<string> rows = splitString(parts[2], '\n');
        grid = vector<vector<Cell>>(rowSize, vector<Cell>(colSize, Cell(rowSize, colSize)));

        // Parse rows and reconstruct grid
        for (size_t i = 0; i < rows.size(); ++i) {
            vector<string> cellData = splitString(rows[i], ',');
            for (int j = 0; j < cellData.size(); ++j) {
                Cell cell(i, j, cellData[j]);
                grid[i][j] = cell;
            }
        }

        //vector<pair<int,int>> stackPairs = splitPairs(parts[3], ';');

        /*for (size_t i = 0; i < stackPairs.size(); i++) {

        };*/

        backtrackStack = decompressStack(parts[3]);

        Position posStart = decompressPosition(parts[4]);
        Position posGoal = decompressPosition(parts[5]);

        startPosition = &grid[posStart.getRow()][posStart.getCol()];
        goalPosition = &grid[posGoal.getRow()][posGoal.getCol()];  
        
    }

    ~Maze() {
        free(startPosition);
        free(goalPosition);
    }

    void generateMaze(int row, int col) {
        grid[row][col].setVisited(true);

        vector<Direction> directions = { UP, DOWN, LEFT, RIGHT };
        shuffle(directions.begin(), directions.end(), std::mt19937(std::random_device()()));

        for (Direction dir : directions) {
            int newRow = row;
            int newCol = col;

            if (dir == UP && row > 0) {
                newRow--;
            }
            else if (dir == DOWN && row < rowSize - 1) {
                newRow++;
            }
            else if (dir == LEFT && col > 0) {
                newCol--;
            }
            else if (dir == RIGHT && col < colSize - 1) {
                newCol++;
            }

            if (!grid[newRow][newCol].getVisited()) {
                // Knock down the wall between current cell and new cell
                if (dir == UP) {
                    grid[row][col].setWall(UP, false);
                    grid[newRow][newCol].setWall(DOWN, false);
                }
                else if (dir == DOWN) {
                    grid[row][col].setWall(DOWN, false);
                    grid[newRow][newCol].setWall(UP, false);
                }
                else if (dir == LEFT) {
                    grid[row][col].setWall(LEFT,false);
                    grid[newRow][newCol].setWall(RIGHT, false);
                }
                else if (dir == RIGHT) {
                    grid[row][col].setWall(RIGHT, false);
                    grid[newRow][newCol].setWall(LEFT, false);
                }

                backtrackStack.push(make_pair(row, col));
                generateMaze(newRow, newCol);
            }

        }
    }

    void printMaze() {
        // Print the maze
        cout << "Size: " << rowSize << "X" << colSize << endl;
        for (int i = 0; i < rowSize; i++) {
            for (int j = 0; j < colSize; j++) {
                cout << " ";
                if (grid[i][j].getWall(UP)) cout << "_";
                else cout << "";
                cout << "";
                if (grid[i][j].getWall(LEFT)) cout << "|";
                else cout << "";
            }
            cout << endl;
        }
    }

    Position getStartPosition() {
        int row = this->startPosition->getRow();
        int col = this->startPosition->getCol();
        Position pos(row, col);
        return pos;
    }
    
    Position getGaolPosition() {
        int row = this->startPosition->getRow();
        int col = this->startPosition->getCol();
        Position pos(row, col);
        return pos;
    }

    vector<string> getPossibleMoves(Position p) {
        Cell* cell = &grid[p.getRow()][p.getCol()];
        vector<Direction> directions = { UP, DOWN, LEFT, RIGHT };
        vector<string> possiable;
        for (Direction dir : directions) {
            if (dir == UP) {
                if (!cell->getWall(UP)) {
                    possiable.push_back("UP");
                }
            }
            else if (dir == RIGHT) {
                if (!cell->getWall(RIGHT)) {
                    possiable.push_back("RIGHT");
                } 
            }
            else if (dir == DOWN) {
                 if (!cell->getWall(DOWN)) {
                    possiable.push_back("DOWN");
                 }
            }
            else if (dir == LEFT) {
                if(!cell->getWall(LEFT)) {
                    possiable.push_back("LEFT");
                }
            }
        }
        return possiable;
    }

    string getData() const {
        string compressedData;

        compressedData += to_string(rowSize) + "@";
        compressedData += to_string(colSize) + "@";

        // Serialize grid data
        for (const auto& row : grid) {
            for (const Cell& cell : row) {
                compressedData += cell.compressCell() + ','; // Separator between cells
            }
            compressedData += '\n'; // Newline between rows
        }

        // Serialize backtrackStack, startPosition, and goalPosition
        compressedData += "@";
        compressedData += compressStack(backtrackStack);
        compressedData += "@";
        compressedData += compressPosition(startPosition);
        compressedData += "@";
        compressedData += compressPosition(goalPosition);



        // Append them to compressedData

        return compressedData;
    }

    string compressStack(const stack<pair<int, int>>& stk) const {
        string compressedStack;

        // Serialize stack data
        stack<pair<int, int>> tempStack = stk; // Create a copy of the stack
        while (!tempStack.empty()) {
            compressedStack += to_string(tempStack.top().first) + ',' + to_string(tempStack.top().second) + ';';
            tempStack.pop();
        }

        return compressedStack;
    }

    string compressPosition(Cell* cell) const {
        int row = cell->getRow();
        int col = cell->getCol();
        return to_string(row) + ',' + to_string(col);
    }

    stack<pair<int, int>> decompressStack(const string& compressedStackData) {
        stack<pair<int, int>> stk;

        vector<string> stackPairs = splitString(compressedStackData, ';');
        for (const string& pairData : stackPairs) {
            vector<string> coords = splitString(pairData, ',');
            if (coords.size() == 2) {
                int row = stoi(coords[0]);
                int col = stoi(coords[1]);
                stk.push(make_pair(row, col));
            }
        }

        return stk;
    }

    Position decompressPosition(const string& compressedPositionData) {
        vector<string> posData = splitString(compressedPositionData, ',');
        int row = stringToInt(posData[0]);
        int col = stringToInt(posData[1]);
        return Position(row, col);
    }

    vector<string> splitString(const string& str, char delimiter) {
        vector<string> tokens;
        string token;
        size_t start = 0, end = 0;

        while ((end = str.find(delimiter, start)) != string::npos) {
            token = str.substr(start, end - start);
            tokens.push_back(token);
            start = end + 1;
        }

        if (start < str.length()) {
            token = str.substr(start);
            tokens.push_back(token);
        }

        return tokens;
    }

    int stringToInt(const string& str) {
        int result = 0;
        for (char c : str) {
            result = result * 10 + (c - '0');
        }
        return result;
    }

    int getRowSize() { return rowSize; }
    int getColSize() { return colSize; }
    vector<vector<Cell>> getGrid() { return grid; }


};