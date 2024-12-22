#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <regex>
#include <unordered_map>
#include <unordered_set>

typedef std::pair<int, int> i_pair;

std::unordered_map<char, i_pair> directions{
    {'>', {0, 1}},
    {'v', {1, 0}},
    {'<',  {0, -1}},
    {'^', {-1, 0}}
};

std::unordered_map<char, i_pair> numericMap{
    {'A', {3, 2}},
    {'0', {3, 1}},
    {'1', {2, 0}},
    {'2', {2, 1}},
    {'3', {2, 2}},
    {'4', {1, 0}},
    {'5', {1, 1}},
    {'6', {1, 2}},
    {'7', {0, 0}},
    {'8', {0, 1}},
    {'9', {0, 2}}
};

std::unordered_map<char, i_pair> directionalMap{
    {'A', {0, 2}},
    {'^', {0, 1}},
    {'<', {1, 0}},
    {'v', {1, 1}},
    {'>', {1, 2}}
};

bool isValidNumMove(const std::string& move, char start) {
    auto [startI, startJ] = numericMap[start];
    for (int i = 0; i < move.size(); i++) {
        if (startI == 3 && startJ == 0) {
            return false;
        }
        auto [di, dj] = directions[move[i]];
        startI += di;
        startJ += dj;
    }
    return true;
}

bool isValidDirMove(const std::string& move, char start) {
    auto [startI, startJ] = directionalMap[start];
    for (int i = 0; i < move.size(); i++) {
        if (startI == 0 && startJ == 0) {
            return false;
        }
        auto [di, dj] = directions[move[i]];
        startI += di;
        startJ += dj;
    }
    return true;
}

//right up down left
std::vector<std::string> move(char start, char end, std::unordered_map<char, i_pair> map) {
    i_pair startPos = map[start];
    i_pair endPos = map[end];
    int di = endPos.first - startPos.first;
    int dj = endPos.second - startPos.second;

    std::string horizontal;
    std::string vertical;
    if (dj > 0) {
        horizontal.append(dj, '>');
    }
    if (di < 0) {
        vertical.append(-di, '^');
    }
    if (di > 0) {
        vertical.append(di, 'v');
    }
    if (dj < 0) {
        horizontal.append(-dj, '<');
    }

    if (di == 0) {
        return {horizontal};
    }
    if (dj == 0) {
        return {vertical};
    }

    return {horizontal + vertical, vertical + horizontal};
}

std::vector<std::string> getNumMoveString(std::string code) {
    char prev = 'A';
    std::vector<std::string> moves{""};
    for (char c : code) {
        auto nexts = move(prev, c, numericMap);
        std::vector<std::string> newMoves;
        for (std::string base : moves) {
            for (std::string next : nexts) {
                if (isValidNumMove(next, prev)) {
                    newMoves.push_back(base + next + "A");
                }
            }
        }
        moves = newMoves;
        prev = c;
    }
    return moves;
}

std::vector<std::string> getDirMoveString(std::string dirs) {
    char prev = 'A';
    std::vector<std::string> moves{""};
    for (char c : dirs) {
        auto nexts = move(prev, c, directionalMap);
        std::vector<std::string> newMoves;
        for (std::string base : moves) {
            for (std::string next : nexts) {
                if (isValidDirMove(next, prev)) {
                    newMoves.push_back(base + next + "A");
                }
            }
        }
        moves = newMoves;
        prev = c;
    }
    return moves;
}


std::string getFinalMoveString(std::string code) {
    std::vector<std::string> robotCommands1 = getNumMoveString(code);
    //inputs that the first robot must enter (radioactive room)
    std::vector<std::string> robotCommands2;
    for (std::string s : robotCommands1) {
        for (std::string next : getDirMoveString(s)) {
            robotCommands2.push_back(next);
        }
    }
    std::string minString(100, '.');
    for (std::string s : robotCommands2) {
        for (std::string next : getDirMoveString(s)) {
            if (next.size() < minString.size()) {
                minString = next;
            }
        }
    }
    return minString;
}

std::string getFinalMoveString2(std::string code) {
    std::vector<std::string> robotCommands1 = getNumMoveString(code);
    //inputs that the first robot must enter (radioactive room)

    for (int i = 0; i < 2; i++) {
        std::vector<std::string> nextCommands;
        for (std::string s : robotCommands1) {
            for (std::string next : getDirMoveString(s)) {
                if (nextCommands.empty() || next.size() == nextCommands[0].size()) {
                    nextCommands.push_back(next);
                }

                if (next.size() < nextCommands[0].size()) {
                    nextCommands = {next};
                }
            }
        }
        robotCommands1 = nextCommands;
    }

    std::string minString;
    for (std::string s : robotCommands1) {
        for (std::string next : getDirMoveString(s)) {
            if (minString.empty() || next.size() < minString.size()) {
                minString = next;
            }
        }
    }
    return minString;
}

int getNumericPart(std::string code) {
    return std::stoi(code.substr(0, code.size() - 1));
}


void part1() {
    std::ifstream inputFile("Day21/input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }
    std::string nextLine;
    int total = 0;
    while (std::getline(inputFile, nextLine)) {
        total += (getNumericPart(nextLine) * getFinalMoveString(nextLine).size());
    }
    std::cout << total;
}

void part2() {
    std::ifstream inputFile("Day21/input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }

    std::string nextLine;
    int total = 0;
    while (std::getline(inputFile, nextLine)) {
        total += (getNumericPart(nextLine) * getFinalMoveString2(nextLine).size());
    }
    std::cout << total;
}


int main() {
    //std::cout << getFinalMoveString("379A").size() << std::endl;
    //std::cout << getDirMoveString("^A<<^^A>>AvvvA") << " " << getDirMoveString(getDirMoveString("^A<<^^A>>AvvvA")).size() << std::endl;
    //std::cout << getDirMoveString("^A^^<<A>>AvvvA") << " " << getDirMoveString(getDirMoveString("^A^^<<A>>AvvvA")).size() << std::endl;
    //auto a = getDirMoveString("<vA");
    part2();
    return 0;
}