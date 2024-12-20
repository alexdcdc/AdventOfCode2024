#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <queue>
#include <sstream>
#include <regex>

#define GRID_WIDTH 101
#define GRID_HEIGHT 103

int countMaxContiguous(const std::vector<std::vector<int>>& grid) {
    int maxLength = 0;

    for (auto row : grid) {
        int prevOne = -1;
        int curLength = 0;
        for (int i = 0; i < row.size(); i++) {
            if (row[i] == 1) {
                if (i == prevOne + 1) {
                    curLength++;
                    if (curLength > maxLength) {
                        maxLength = curLength;
                    }
                }
                else {
                    curLength = 1;
                }
                prevOne = i;
            }
        }
    }

    return maxLength;
}

std::pair<int, int> parsePosition(std::string line) {
    std::regex exp(R"(p=(-?[0-9]+),(-?[0-9]+).*)");
    std::smatch match;
    if (std::regex_search(line, match, exp)) {
        return {std::stoi(match[1]), std::stoi(match[2])};
    }

    return {};
}

std::pair<int, int> parseVelocity(std::string line) {
    std::regex exp(R"(v=(-?[0-9]+),(-?[0-9]+))");
    std::smatch match;
    if (std::regex_search(line, match, exp)) {
        return {std::stoi(match[1]), std::stoi(match[2])};
    }

    return {};
}

int getQuadrant(std::pair<int, int> p) {
    int middleX = GRID_WIDTH / 2;
    int middleY = GRID_HEIGHT / 2;
    if (p.first > middleX && p.second > middleY) {
        return 0;
    }
    if (p.first > middleX && p.second < middleY) {
        return 1;
    }
    if (p.first < middleX && p.second > middleY) {
        return 2;
    }
    if (p.first < middleX && p.second < middleY) {
        return 3;
    }
    return 4;
}

int posMod(int a, int b) {
    return ((a % b) + b) % b;
}

std::pair<int, int> getFinalPosition(std::pair<int, int> p, std::pair<int, int> v, int t) {
    return {posMod(p.first + v.first * t, GRID_WIDTH), posMod(p.second + v.second * t, GRID_HEIGHT)};
}

std::vector<std::vector<int>> makeGrid(const std::vector<std::pair<int, int>>& positions, const std::vector<std::pair<int, int>>& velocities, int t) {
    std::vector<std::vector<int>> grid(GRID_HEIGHT, std::vector<int>(GRID_WIDTH, 0));
    /*
    for (int i = 0; i < GRID_WIDTH; i++) {
        for (int j = 0; j < GRID_HEIGHT; j++) {
            grid[i][j] = '.';
        }
    }
    */
    for (int i = 0; i < positions.size(); i++) {
        auto finalPosition = getFinalPosition(positions[i], velocities[i], t);
        grid[finalPosition.second][finalPosition.first] = 1;
    }
    /*
    for (auto & i : grid) {
        for (char j : i) {
            std::cout << j;
        }
        std::cout << std::endl;
    }
    */
    return grid;
}

void displayGrid(const std::vector<std::vector<int>>& grid) {
    for (auto& row : grid) {
        for (const auto n : row) {
            if (n == 1) {
                std::cout << 'O';
            }
            else {
                std::cout << '.';
            }
        }
        std::cout << std::endl;
    }
}

void part1() {
    std::ifstream inputFile("Day14/input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }

    int quadrants[5] = {0};
    std::string nextLine;
    while (std::getline(inputFile, nextLine)) {
        auto p = parsePosition(nextLine);
        auto v = parseVelocity(nextLine);
        auto final = getFinalPosition(p, v, 100);
        quadrants[getQuadrant(final)]++;
    }
    int total = 1;
    for (int i = 0; i < 4; i++) {
        total *= quadrants[i];
    }

    std::cout << total << std::endl;
}

void part2() {
    std::ifstream inputFile("Day14/input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }

    std::string nextLine;
    std::vector<std::pair<int, int>> positions, velocities;
    while (std::getline(inputFile, nextLine)) {
        positions.push_back(parsePosition(nextLine));
        velocities.push_back(parseVelocity(nextLine));
    }

    int i = 0;
    while (true) {
        auto grid = makeGrid(positions, velocities, i);
        if (countMaxContiguous(grid) >= 10) {
            displayGrid(grid);
            std::cout << i << std::endl;
            std::system("pause");
        }
        i++;
    }
}

int main() {
    part2();
    return 0;
}