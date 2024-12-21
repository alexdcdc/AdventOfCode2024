#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <regex>

typedef std::pair<int, int> i_pair;

bool isInBounds(const std::vector<std::string>& grid, i_pair pos) {
    return pos.first >= 0 && pos.first < grid.size() && pos.second >= 0 && pos.second < grid[0].size();
}

i_pair locate(const std::vector<std::string>& grid, char c) {
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == c) {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}

std::vector<i_pair> getMoveRange(int distance, i_pair pos) {
    std::vector<i_pair> positions;
    auto [i, j] = pos;
    for (int di = 0; di < distance; di++) {
        int dj = distance - di;
        positions.emplace_back(i + di, j + dj);
        positions.emplace_back(i - dj, j + di);
        positions.emplace_back(i - di, j - dj);
        positions.emplace_back(i + dj, j - di);
    }
    return positions;
}

int countCheats(const std::vector<std::string>& grid) {
    auto [i, j] = locate(grid, 'E');
    int distance = 0;
    int numCheats = 0;
    std::vector finishDistances(grid.size(), std::vector(grid[0].size(), -1));
    bool done = false;
    while (!done) {
        finishDistances[i][j] = distance;
        for (auto [cheatI, cheatJ] : getMoveRange(2, {i, j})) {
            if (isInBounds(grid, {cheatI, cheatJ}) && finishDistances[cheatI][cheatJ] != -1 && finishDistances[i][j] - finishDistances[cheatI][cheatJ] - 2 >= 100) {
                numCheats++;
            }
        }
        if (grid[i][j] == 'S') {
            done = true;
        }
        else {
            for (auto [nextI, nextJ] : getMoveRange(1, {i, j})) {
                if (isInBounds(grid, {nextI, nextJ}) && grid[nextI][nextJ] != '#' && finishDistances[nextI][nextJ] == -1) {
                    i = nextI;
                    j = nextJ;
                }
            }
        }
        distance++;
    }
    return numCheats;
}


int countCheats2(const std::vector<std::string>& grid) {
    auto [i, j] = locate(grid, 'E');
    int distance = 0;
    int numCheats = 0;
    std::vector finishDistances(grid.size(), std::vector(grid[0].size(), -1));
    bool done = false;
    while (!done) {
        finishDistances[i][j] = distance;
        for (int range = 2; range <= 20; range++) {
            for (auto [cheatI, cheatJ] : getMoveRange(range, {i, j})) {
                if (isInBounds(grid, {cheatI, cheatJ}) && finishDistances[cheatI][cheatJ] != -1 && finishDistances[i][j] - finishDistances[cheatI][cheatJ] - range >= 100) {
                    //std::cout << i << "," << j << "->" << cheatI << "," << cheatJ << std::endl;
                    numCheats++;
                }
            }
        }

        if (grid[i][j] == 'S') {
            done = true;
        }
        else {
            for (auto [nextI, nextJ] : getMoveRange(1, {i, j})) {
                if (isInBounds(grid, {nextI, nextJ}) && grid[nextI][nextJ] != '#' && finishDistances[nextI][nextJ] == -1) {
                    i = nextI;
                    j = nextJ;
                }
            }
        }
        distance++;
    }
    return numCheats;
}



void part1() {
    std::ifstream inputFile("Day20/input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }

    std::string nextLine;
    std::vector<std::string> grid;

    while (std::getline(inputFile, nextLine)) {
        grid.push_back(nextLine);
    }

    std::cout << countCheats(grid) << std::endl;

}

void part2() {
    std::ifstream inputFile("Day20/input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }

    std::string nextLine;
    std::vector<std::string> grid;

    while (std::getline(inputFile, nextLine)) {
        grid.push_back(nextLine);
    }

    std::cout << countCheats2(grid) << std::endl;
}


int main() {
    part2();
    return 0;
}