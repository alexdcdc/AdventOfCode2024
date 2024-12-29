#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <mutex>
#include <sstream>
#include <regex>

std::vector<int> parseGrid(const std::vector<std::string>& grid) {
    std::vector heights(grid[0].size(), 0);
    for (int i = 1; i < grid.size() - 1; i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == '#') {
                heights[j]++;
            }
        }
    }
    return heights;
}

bool canFit(std::vector<int> key, std::vector<int> lock) {
    for (int i = 0; i < key.size(); i++) {
        if (key[i] + lock[i] > 5) {
            return false;
        }
    }
    return true;
}

void part1() {
    std::ifstream inputFile("Day25/input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }

    std::vector<std::vector<int>> keys;
    std::vector<std::vector<int>> locks;
    std::string nextLine;

    while (std::getline(inputFile, nextLine)) {
        std::vector<std::string> grid;
        while (!nextLine.empty()) {
            grid.push_back(nextLine);
            if (!std::getline(inputFile, nextLine)) {
                break;
            }
        }
        if (grid[0][0] == '#') {
            locks.push_back(parseGrid(grid));
        }
        else {
            keys.push_back(parseGrid(grid));
        }
    }

    int count = 0;
    for (auto lock : locks) {
        for (auto key : keys) {
            if (canFit(key, lock)) {
                count++;
            }
        }
    }

    std::cout << count << std::endl;
}

void part2() {
    std::ifstream inputFile("DayX/input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }
}


int main() {
    part1();
    return 0;
}