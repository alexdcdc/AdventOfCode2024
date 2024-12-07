//
// Created by alexd on 12/5/2024.
//
//
// Created by alexd on 12/5/2024.
//

//
// Created by alexd on 12/5/2024.
//
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <regex>
#include <set>
#include <unordered_set>
#include <tuple>

void rotate(int& dRow, int& dCol) {
    int tmp = dRow;
    dRow = dCol;
    dCol = -tmp;
}

bool isInBounds(const int row, const int col, const std::vector<std::string>& grid) {
    return row >= 0 && row < grid.size() && col >= 0 && col < grid[0].size();
}

void move(int& row, int& col, int& dRow, int& dCol, const std::vector<std::string>& grid) {
    int newRow = row + dRow;
    int newCol = col + dCol;
    if (!isInBounds(newRow, newCol, grid) || grid[newRow][newCol] != '#') {
        row = newRow;
        col = newCol;
    }
    else {
        rotate(dRow, dCol);
    }
}

std::tuple<int, int, int, int> encode(int row, int col, int dRow, int dCol) {
    return {row, col, dRow, dCol};
}

int calcSteps(std::vector<std::string> grid, int guardRow, int guardCol) {
    int dRow = -1;
    int dCol = 0;
    int totalTilesWalked = 0;

    std::set<std::tuple<int, int, int, int>> states{};

    while (isInBounds(guardRow, guardCol, grid)) {
        //std::cout << guardRow << " " << guardCol << std::endl;
        std::tuple<int, int, int, int> encoding = encode(guardRow, guardCol, dRow, dCol);
        if (states.find(encoding) != states.end()) {
            return -1;
        }
        states.insert(encoding);
        if (grid[guardRow][guardCol] != 'x') {
            grid[guardRow][guardCol] = 'x';
            totalTilesWalked++;
        }

        move(guardRow, guardCol, dRow, dCol, grid);
    }

    return totalTilesWalked;
}

void part1() {
    std::ifstream inputFile("Day6/input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }

    std::vector<std::string> grid{};

    int guardRow = 0;
    int guardCol = 0;

    std::string nextLine;
    while (std::getline(inputFile, nextLine)) {
        int col = nextLine.find('^');
        if (col != std::string::npos) {
            guardCol = col;
            guardRow = grid.size();
        }
        grid.push_back(nextLine);
    }

    int totalTilesWalked = calcSteps(grid, guardRow, guardCol);

    std::cout << totalTilesWalked << std::endl;
}

//this solution sucks really bad O(m^2n^2)
void part2() {
    std::ifstream inputFile("Day6/input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }

    std::vector<std::string> grid{};

    int guardRow = 0;
    int guardCol = 0;

    std::string nextLine;
    while (std::getline(inputFile, nextLine)) {
        int col = nextLine.find('^');
        if (col != std::string::npos) {
            guardCol = col;
            guardRow = grid.size();
        }
        grid.push_back(nextLine);
    }

    int numCyclic = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == '.') {
                grid[i][j] = '#';
                if (calcSteps(grid, guardRow, guardCol) == -1) {
                    numCyclic++;
                }
                grid[i][j] = '.';
            }
        }
    }

    std::cout << numCyclic << std::endl;
}


int main() {
    part2();
    return 0;
}
