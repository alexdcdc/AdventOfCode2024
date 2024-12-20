#include <algorithm>
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <map>
#include <queue>
#include <sstream>
#include <regex>
#include <set>

typedef std::pair<int, int> i_pair;
typedef std::pair<i_pair, i_pair> loc_dir;
typedef std::pair<int, loc_dir> queue_pair;
typedef std::vector<std::string> char_grid;
#define INF ((1 << 31) - 1)

i_pair dirs[4] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

i_pair locate(const char_grid& grid, char c) {
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == c) {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}

bool isInBounds(int i, int j, const char_grid& grid) {
    return (i >= 0 && i < grid.size() && j >= 0 && j < grid.size());
}



std::pair<loc_dir, loc_dir> getPerpDirs(loc_dir start) {
    auto [loc, dir] = start;
    i_pair dir1 = {dir.second, dir.first};
    i_pair dir2 = {-dir.second, -dir.first};
    return {{loc, dir1}, {loc, dir2}};
}

std::vector<queue_pair> getNext(const char_grid& grid, loc_dir start) {
    auto [loc, dir] = start;
    loc_dir forward = {{loc.first + dir.first, loc.second + dir.second}, dir};
    auto [perp1, perp2] = getPerpDirs(start);

    std::vector<queue_pair> next;
    if (grid[loc.first + dir.first][loc.second + dir.second] != '#') {
        next.emplace_back(1, forward);
    }
    next.emplace_back(1000, perp1);
    next.emplace_back(1000, perp2);
    return next;
}

int calcMinPath(const char_grid& grid, i_pair start, i_pair end) {
    std::priority_queue<queue_pair, std::vector<queue_pair>, std::greater<>> pq;
    int n = 0;
    std::map<loc_dir, int> indexMap;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] != '#') {
                for (i_pair p : dirs) {
                    indexMap[{{i, j}, p}] = n;
                    n++;
                }
            }
        }
    }

    std::vector<int> distances(n, INF);
    distances[indexMap[{start, {0, 1}}]] = 0;
    pq.push({0, {start, {0, 1}}});
    while (!pq.empty()) {
        loc_dir cur = pq.top().second;
        pq.pop();
        if (cur.first == end) {
            return distances[indexMap[cur]];
        }
        for (auto [weight, nextLocDir] : getNext(grid, cur)) {
            if (distances[indexMap[cur]] + weight < distances[indexMap[nextLocDir]]) {
                distances[indexMap[nextLocDir]] = distances[indexMap[cur]] + weight;
                pq.emplace(distances[indexMap[nextLocDir]], nextLocDir);
            }
        }
    }
    return -1;
}

int getOptimalTiles(char_grid grid, i_pair start, i_pair end) {
    std::priority_queue<queue_pair, std::vector<queue_pair>, std::greater<>> pq;
    int n = 0;
    std::map<loc_dir, int> indexMap;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] != '#') {
                for (i_pair p : dirs) {
                    indexMap[{{i, j}, p}] = n;
                    n++;
                }
            }
        }
    }

    std::vector distances(n, INF);
    std::vector froms(n, std::vector<loc_dir>{});

    distances[indexMap[{start, {0, 1}}]] = 0;
    pq.push({0, {start, {0, 1}}});
    int minDist = -1;
    while (!pq.empty()) {
        loc_dir cur = pq.top().second;
        pq.pop();
        if (cur.first == end && minDist == -1) {
            minDist = distances[indexMap[cur]];
        }
        for (auto [weight, nextLocDir] : getNext(grid, cur)) {
            if (distances[indexMap[cur]] + weight < distances[indexMap[nextLocDir]]) {
                distances[indexMap[nextLocDir]] = distances[indexMap[cur]] + weight;
                pq.emplace(distances[indexMap[nextLocDir]], nextLocDir);
                froms[indexMap[nextLocDir]] = {cur};
            }
            else if (distances[indexMap[cur]] + weight == distances[indexMap[nextLocDir]]) {
                froms[indexMap[nextLocDir]].emplace_back(cur);
            }
        }
    }

    std::queue<loc_dir> todo;
    for (i_pair dir : dirs) {
        if (distances[indexMap[{end, dir}]] == minDist) {
            todo.emplace(end, dir);
        }
    }

    int count = 0;
    while (!todo.empty()) {
        auto [loc, dir] = todo.front();
        todo.pop();
        if (grid[loc.first][loc.second] != 'O') {
            grid[loc.first][loc.second] = 'O';
            count++;
        }

        for (auto p : froms[indexMap[{loc, dir}]]) {
            todo.push(p);
        }
    }

    return count;
}

void part1() {
    std::ifstream inputFile("Day16/test_input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }

    char_grid grid;
    std::string nextLine;
    while (std::getline(inputFile, nextLine)) {
        grid.push_back(nextLine);
    }

    std::cout << calcMinPath(grid, locate(grid, 'S'), locate(grid, 'E'));
}

void part2() {
    std::ifstream inputFile("Day16/input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }

    char_grid grid;
    std::string nextLine;
    while (std::getline(inputFile, nextLine)) {
        grid.push_back(nextLine);
    }

    std::cout << getOptimalTiles(grid, locate(grid, 'S'), locate(grid, 'E'));
}


int main() {
    part2();
    return 0;
}