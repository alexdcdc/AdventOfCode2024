#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <regex>
#include <unordered_map>
std::unordered_map<char, std::pair<int, int>> instructionMap =
    {
    {'^', {-1, 0}},
    {'>', {0, 1}},
    {'v', {1, 0}},
    {'<', {0, -1}}
    };

std::pair<int, int> locateRobot(const std::vector<std::string>& grid) {
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == '@') {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}

int calcCoords(const std::vector<std::string>& grid) {
    int total = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == 'O') {
                total += (100 * i + j);
            }
        }
    }
    return total;
}

void executeInstruction(const char instruction, std::vector<std::string>& grid, int& robotRow, int& robotCol) {
    auto [di, dj] = instructionMap[instruction];
    int i = robotRow + di;
    int j = robotCol + dj;
    while (grid[i][j] == 'O') {
        i += di;
        j += dj;
    }

    if (grid[i][j] == '#') {
        return;
    }

    grid[i][j] = 'O';
    grid[robotRow + di][robotCol + dj] = '@';
    grid[robotRow][robotCol] = '.';
    robotRow += di;
    robotCol += dj;
}

std::vector<std::string> convertGrid(const std::vector<std::string>& grid) {
    std::vector<std::string> newGrid;
    for (const std::string& row : grid) {
        std::string newRow;
        for (char c : row) {
            if (c == 'O') {
                newRow.append("[]");
            }
            else if (c == '@') {
                newRow.append(1, c);
                newRow.append(1, '.');
            }
            else {
                newRow.append(2, c);
            }
        }
        newGrid.push_back(newRow);
    }
    return newGrid;
}



bool isPushable(int i, int j, const std::pair<int, int>& direction, const std::vector<std::string>& grid) {
    if (grid[i][j] == '#') {
        return false;
    }
    if (grid[i][j] == '.') {
        return true;
    }

    if (direction.first == 0) {
        return isPushable(i + direction.first, j + direction.second, direction, grid);
    }

    int leftJ = j, rightJ = j;
    if (grid[i][j] == ']') {
        leftJ--;
    }
    else if (grid[i][j] == '[') {
        rightJ++;
    }

    return isPushable(i + direction.first, leftJ, direction, grid) &&
        isPushable(i + direction.first, rightJ, direction, grid);
}

void push(int i, int j, const std::pair<int, int>& direction, std::vector<std::string>& grid) {
    if (grid[i][j] == '.') {
        return;
    }

    int newI = i + direction.first;
    int newJ = j + direction.second;
    if (direction.first == 0) {
        push(newI, newJ, direction, grid);
        grid[newI][newJ] = grid[i][j];
        grid[i][j] = '.';
    }

    int leftJ = j, rightJ = j;
    if (grid[i][j] == ']') {
        leftJ--;
    }
    else if (grid[i][j] == '[') {
        rightJ++;
    }

    push(i + direction.first, leftJ, direction, grid);
    push(i + direction.first, rightJ, direction, grid);
    grid[i + direction.first][leftJ] = grid[i][leftJ];
    grid[i + direction.first][rightJ] = grid[i][rightJ];
    grid[i][leftJ] = '.';
    grid[i][rightJ] = '.';
}

void executeInstruction2(const char instruction, std::vector<std::string>& grid, int& robotRow, int& robotCol) {
    auto [di, dj] = instructionMap[instruction];
    int i = robotRow + di;
    int j = robotCol + dj;
    if (isPushable(i, j, {di, dj}, grid)) {
        push(i, j, {di, dj}, grid);
        grid[robotRow + di][robotCol + dj] = '@';
        grid[robotRow][robotCol] = '.';
        robotRow += di;
        robotCol += dj;
    }
}

int calcCoords2(const std::vector<std::string>& grid) {
    int total = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == '[') {
                total += (100 * i + j);
            }
        }
    }
    return total;
}

void part1() {
    std::ifstream inputFile("Day15/input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }

    std::vector<std::string> grid;
    std::string nextLine;
    while (std::getline(inputFile, nextLine) && !nextLine.empty()) {
        grid.push_back(nextLine);
    }
    std::vector<char> instructions;
    while (std::getline(inputFile, nextLine)) {
        for (char c : nextLine) {
            instructions.push_back(c);
        }
    }

    auto [robotRow, robotCol] = locateRobot(grid);
    for (char instruction : instructions) {
        executeInstruction(instruction, grid, robotRow, robotCol);
    }

    std::cout << calcCoords(grid) << std::endl;
}

void part2() {
    std::ifstream inputFile("Day15/input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }

    std::vector<std::string> grid;
    std::string nextLine;
    while (std::getline(inputFile, nextLine) && !nextLine.empty()) {
        grid.push_back(nextLine);
    }
    std::vector<char> instructions;
    while (std::getline(inputFile, nextLine)) {
        for (char c : nextLine) {
            instructions.push_back(c);
        }
    }

    grid = convertGrid(grid);

    auto [robotRow, robotCol] = locateRobot(grid);
    for (char instruction : instructions) {
        executeInstruction2(instruction, grid, robotRow, robotCol);
    }

    std::cout << calcCoords2(grid) << std::endl;

}


int main() {
    part2();
    return 0;
}