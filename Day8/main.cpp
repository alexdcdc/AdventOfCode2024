#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <regex>
#include <unordered_map>

std::pair<int, int> extend(std::pair<int, int> start, std::pair<int, int> end) {
    return std::pair{2 * end.first - start.first, 2 * end.second - start.second};
}

std::pair<int, int> extend2(std::pair<int, int> start, std::pair<int, int> end, int n) {
    return std::pair{end.first + n * (end.first - start.first), end.second + n * (end.second - start.second)};
}

bool isInBounds(std::pair<int, int> loc, int m, int n) {
    return loc.first >= 0 && loc.first < m && loc.second >= 0 && loc.second < n;
}

std::unordered_map<char, std::vector<std::pair<int, int>>> mapLocations(const std::vector<std::string>& grid) {
    std::unordered_map<char, std::vector<std::pair<int, int>>> result;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            char c = grid[i][j];
            if (c == '.') {
                continue;
            }
            std::pair location{i, j};
            if (result.find(c) != result.end()) {
                result[c].push_back(location);
            }
            else {
                result[c] = std::vector{location};
            }
        }
    }
    return result;
}

int countValidLocations(std::unordered_map<char, std::vector<std::pair<int, int>>> map, int m, int n) {
    int antinodes[m][n]{0};
    int nodeCount = 0;

    for (auto k : map) {
        std::vector<std::pair<int, int>> locs = k.second;
        for (int i = 0; i < locs.size(); i++) {
            for (int j = 0; j < locs.size(); j++) {
                if (i == j) continue;
                std::pair antinode = extend(locs[i], locs[j]);
                if (isInBounds(antinode, m, n) && antinodes[antinode.first][antinode.second] == 0) {
                    antinodes[antinode.first][antinode.second] = 1;
                    nodeCount++;
                }
            }
        }
    }

    return nodeCount;

}

int countValidLocations2(std::unordered_map<char, std::vector<std::pair<int, int>>> map, int m, int n) {
    int antinodes[m][n]{0};
    int nodeCount = 0;

    for (auto p : map) {
        std::vector<std::pair<int, int>> locs = p.second;
        for (int i = 0; i < locs.size(); i++) {
            for (int j = 0; j < locs.size(); j++) {
                if (i == j) continue;
                int k = 0;
                std::pair antinode = extend2(locs[i], locs[j], k);
                while (isInBounds(antinode, m, n)) {
                    if (antinodes[antinode.first][antinode.second] == 0) {
                        antinodes[antinode.first][antinode.second] = 1;
                        nodeCount++;
                    }
                    k++;
                    antinode = extend2(locs[i], locs[j], k);
                }
            }
        }
    }

    return nodeCount;

}

void part1() {
    std::ifstream inputFile("Day8/input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }

    std::vector<std::string> grid;
    std::string nextLine;

    while (std::getline(inputFile, nextLine)) {
        grid.push_back(nextLine);
    }

    std::unordered_map<char, std::vector<std::pair<int, int>>> locations = mapLocations(grid);
    int count = countValidLocations(locations, grid.size(), grid[0].size());

    std::cout << count << std::endl;

}

void part2() {
    std::ifstream inputFile("Day8/input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }

    std::vector<std::string> grid;
    std::string nextLine;

    while (std::getline(inputFile, nextLine)) {
        grid.push_back(nextLine);
    }

    std::unordered_map<char, std::vector<std::pair<int, int>>> locations = mapLocations(grid);
    int count = countValidLocations2(locations, grid.size(), grid[0].size());

    std::cout << count << std::endl;
}


int main() {
    part2();
    return 0;
}
