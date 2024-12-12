#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <regex>

std::pair<int, int> dirs[4]{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

bool isUpperCase(char c) {
    return c >= 'A' && c <= 'Z';
}

bool isLowerCase(char c) {
    return c >= 'a' && c <= 'z';
}

bool isInBounds(int i, int j, const std::vector<std::string>& grid) {
    return i >= 0 && i < grid.size() && j >= 0 && j < grid[0].size();
}

void printGrid(const std::vector<std::string>& grid) {
    for (auto line : grid) {
        std::cout << line << std::endl;
    }
    std::cout << std::endl;
}

void restoreGrid(std::vector<std::string>& grid) {
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            grid[i][j] -= 32;
        }
    }
}

int calcArea(int i, int j, std::vector<std::string>& grid) {
    char id = grid[i][j];
    grid[i][j]+=32;
    int area = 1;
    for (auto [di, dj] : dirs) {
        int newI = i + di;
        int newJ = j + dj;
        if (isInBounds(newI, newJ, grid) && grid[newI][newJ] == id) {
            area += calcArea(newI, newJ, grid);
        }
    }
    return area;
}

int calcPerimeter(int i, int j, std::vector<std::string>& grid) {
    char id = grid[i][j];
    grid[i][j] -= 32;
    int perimeter = 0;
    for (auto [di, dj] : dirs) {
        int newI = i + di;
        int newJ = j + dj;
        if (isInBounds(newI, newJ, grid) && grid[newI][newJ] == id) {
            perimeter += calcPerimeter(newI, newJ, grid);
        }
        else if (!isInBounds(newI, newJ, grid) || grid[newI][newJ] != grid[i][j]) {
            perimeter++;
        }
    }
    return perimeter;
}

bool isEdgeContinued(int i, int j, int n, const std::vector<std::vector<std::vector<int>>>& sides, const std::vector<std::string>& grid) {
    return isInBounds(i, j, grid) && sides[i][j][n];
}

void calcNumSides(int i, int j, std::vector<std::string>& grid, std::vector<std::vector<std::vector<int>>>& sides, int& numSides) {
    char id = grid[i][j];
    grid[i][j] -= 32;
    int n = 0;
    for (auto [di, dj] : dirs) {
        int newI = i + di;
        int newJ = j + dj;
        if (isInBounds(newI, newJ, grid) && grid[newI][newJ] == id) {
            calcNumSides(newI, newJ, grid, sides, numSides);
        }
        else if (!isInBounds(newI, newJ, grid) || grid[newI][newJ] != grid[i][j]) {
            numSides++;
            numSides -= isEdgeContinued(i + dj, j + di, n, sides, grid);
            numSides -= isEdgeContinued(i - dj, j - di, n, sides, grid);
            //if (!(isEdgeContinued(i + dj, j + di, n, sides, grid) || isEdgeContinued(i - dj, j - di, n, sides, grid))) {

            //}
            sides[i][j][n] = 1;
        }
        n++;
    }
}

std::vector<std::vector<std::vector<int>>> initSides(const std::vector<std::string>& grid) {
    int m = grid.size();
    int n = grid[0].size();
    std::vector<std::vector<std::vector<int>>> sides;
    for (int i = 0; i < m; i++) {
        std::vector<std::vector<int>> newRow;
        for (int j = 0; j < n; j++) {
            newRow.emplace_back(std::vector{0, 0, 0, 0});
        }
        sides.emplace_back(newRow);
    }
    return sides;
}

void part1() {
    std::ifstream inputFile("Day12/input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }
    std::vector<std::string> grid;
    std::string nextLine;
    while (std::getline(inputFile, nextLine)) {
        grid.push_back(nextLine);
    }

    int total = 0;
    std::vector<int> areas{};
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (isUpperCase(grid[i][j])) {
                areas.push_back(calcArea(i, j, grid));
            }
        }
    }
    restoreGrid(grid);

    int pos = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (isUpperCase(grid[i][j])) {
                total += areas[pos] * calcPerimeter(i, j, grid);
                pos++;
            }
        }
    }

    std::cout << total << std::endl;
}

void part2() {
    std::ifstream inputFile("Day12/input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }
    std::vector<std::string> grid;
    std::string nextLine;
    while (std::getline(inputFile, nextLine)) {
        grid.push_back(nextLine);
    }

    int total = 0;
    std::vector<int> areas{};
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (isUpperCase(grid[i][j])) {
                areas.push_back(calcArea(i, j, grid));
            }
        }
    }
    restoreGrid(grid);

    int pos = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (isUpperCase(grid[i][j])) {
                int numSides = 0;
                auto sides = initSides(grid);
                calcNumSides(i, j, grid, sides, numSides);
                total += areas[pos] * numSides;
                pos++;
            }
        }
    }

    std::cout << total << std::endl;
}


int main() {
    part2();
    return 0;
}
