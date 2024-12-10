#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <regex>
#include <set>
#include <unordered_set>

bool isInBounds(const int i, const int j, const std::vector<std::vector<int>>& grid) {
    return i >= 0 && i < grid.size() && j >= 0 && j < grid[0].size();
}

std::set<std::pair<int,int>> countPaths(const int i, const int j, std::vector<std::vector<int>>& grid) {
    if (grid[i][j] == 9) {
        return std::set{std::pair{i, j}};
    }

    std::pair<int, int> offsets[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    std::set<std::pair<int, int>> seen{};

    for (auto [di, dj] : offsets) {
        int newI = i + di;
        int newJ = j + dj;

        if (isInBounds(newI, newJ, grid) && grid[newI][newJ] == grid[i][j] + 1) {
            std::set<std::pair<int, int>> results = countPaths(newI, newJ, grid);
            for (auto p : results) {
                if (seen.find(p) == seen.end()) {
                    seen.insert(p);
                }
            }
        }
    }

    return seen;
}

int countPaths2(const int i, const int j, std::vector<std::vector<int>>& grid) {
    if (grid[i][j] == 9) {
        return 1;
    }

    std::pair<int, int> offsets[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    int totalPaths = 0;

    for (auto [di, dj] : offsets) {
        int newI = i + di;
        int newJ = j + dj;

        if (isInBounds(newI, newJ, grid) && grid[newI][newJ] == grid[i][j] + 1) {
            totalPaths += countPaths2(newI, newJ, grid);
        }
    }

    return totalPaths;
}

void part1() {
    std::ifstream inputFile("Day10/input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }

    std::vector<std::vector<int>> grid{};
    std::string nextLine;

    while (std::getline(inputFile, nextLine)) {
        std::vector<int> row{};
        for (char c : nextLine) {
            row.push_back(c - '0');
        }
        grid.emplace_back(row);
    }

    int totalPaths = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == 0) {
                totalPaths += (countPaths(i, j, grid).size());
            }
        }
    }

    std::cout << totalPaths << std::endl;
}

void part2() {
    std::ifstream inputFile("Day10/input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }

    std::vector<std::vector<int>> grid{};
    std::string nextLine;

    while (std::getline(inputFile, nextLine)) {
        std::vector<int> row{};
        for (char c : nextLine) {
            row.push_back(c - '0');
        }
        grid.emplace_back(row);
    }

    int totalPaths = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == 0) {
                totalPaths += countPaths2(i, j, grid);
            }
        }
    }

    std::cout << totalPaths << std::endl;
}


int main() {
    part2();
    return 0;
}