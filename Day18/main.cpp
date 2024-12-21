#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <queue>
#include <sstream>
#include <regex>
#include <set>
typedef std::pair<int, int> i_pair;
typedef std::pair<int, i_pair> queue_pair;

std::vector<i_pair> dirs = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

bool isInBounds(const std::vector<std::string>& grid, i_pair pos) {
    return pos.first >= 0 && pos.first < grid.size() && pos.second >= 0 && pos.second < grid[0].size();
}

std::vector<i_pair> generateAdjacent(i_pair pos) {
    std::vector<i_pair> result;
    for (auto dir : dirs) {
        result.emplace_back(pos.first + dir.first, pos.second + dir.second);
    }
    return result;
}

int shortestPath(const std::vector<std::string>& grid) {
    i_pair dest = {grid.size() - 1, grid[0].size() - 1};
    std::queue<queue_pair> q;
    std::set<i_pair> seen;

    q.push({0, {0, 0}});
    while (!q.empty()) {
        auto [dist, pos] = q.front();
        q.pop();
        if (seen.find(pos) != seen.end()) {
            continue;
        }
        seen.insert(pos);
        if (pos == dest) {
            return dist;
        }

        for (auto next : generateAdjacent(pos)) {
            if (isInBounds(grid, next) && grid[next.first][next.second] == '.') {
                q.emplace(dist + 1, next);
            }
        }
    }

    return -1;
}

void part1() {
    std::ifstream inputFile("Day18/test_input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }

    const int width = 71;
    const int limit = 1024;
    std::vector grid(width, std::string(width, '.'));
    std::string nextLine;
    int numBytes = 0;
    while (std::getline(inputFile, nextLine) && numBytes < limit) {
        std::stringstream s(nextLine);
        int i;
        int j;
        char comma;
        s >> i;
        s >> comma;
        s >> j;
        grid[i][j] = '#';
        numBytes++;
    }

    std::cout << shortestPath(grid) << std::endl;
}

void part2() {
    std::ifstream inputFile("Day18/input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }

    const int width = 71;
    int i;
    int j;
    std::vector grid(width, std::string(width, '.'));
    std::string nextLine;
    while (std::getline(inputFile, nextLine) && shortestPath(grid) != -1) {
        std::stringstream s(nextLine);
        char comma;
        s >> i;
        s >> comma;
        s >> j;
        grid[i][j] = '#';
    }

    std::cout << i << "," << j << std::endl;
}


int main() {
    part2();
    return 0;
}