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

std::vector idToChar = {'A', '<', 'v', '>', '^'};
std::unordered_map<char, int> charToId{
    {'A', 0},
    {'<', 1},
    {'v', 2},
    {'>', 3},
    {'^', 4}
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
        return {horizontal + "A"};
    }
    if (dj == 0) {
        return {vertical + "A"};
    }

    return {horizontal + vertical + "A", vertical + horizontal + "A"};
}

std::vector<std::string> moveDir(char start, char end) {
    std::vector<std::string> candidateMoves = move(start, end, directionalMap);
    std::vector<std::string> validMoves;
    for (std::string& move : candidateMoves) {
        if (isValidDirMove(move, start)) {
            validMoves.push_back(move);
        }
    }
    return validMoves;
}

std::vector<std::string> moveNum(char start, char end) {
    std::vector<std::string> candidateMoves = move(start, end, numericMap);
    std::vector<std::string> validMoves;
    for (std::string& move : candidateMoves) {
        if (isValidNumMove(move, start)) {
            validMoves.push_back(move);
        }
    }
    return validMoves;
}

long long getFinalMoveStringLength2(std::string code, int numBots) {
    long long dp[numBots][5][5] = {0};
    //least # of moves to move from i to j and press j w/ k robots ahead

    for (int j = 0; j < 5; j++) {
        for (int k = 0; k < 5; k++) {
            dp[0][j][k] = moveDir(idToChar[j], idToChar[k])[0].size();
        }
    }

    for (int i = 1; i < numBots; i++) {
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 5; k++) {
                auto strings = moveDir(idToChar[j], idToChar[k]);
                long long minLength = -1;
                for (std::string& s : strings) {
                    long long total = 0;
                    char prev = 'A';
                    for (char c : s) {
                        total += dp[i - 1][charToId[prev]][charToId[c]];
                        prev = c;
                    }
                    if (minLength == -1 || total < minLength) {
                        minLength = total;
                    }
                }
                dp[i][j][k] = minLength;
            }
        }
    }

    char prevNum = 'A';
    long long totalLength = 0;
    for (char curNum : code) {
        auto strings = moveNum(prevNum, curNum);
        long long minLength = -1;
        for (std::string& s : strings) {
            long long total = 0;
            char prev = 'A';
            for (char c : s) {
                total += dp[numBots - 1][charToId[prev]][charToId[c]];
                prev = c;
            }
            if (minLength == -1 || total < minLength) {
                minLength = total;
            }
        }
        totalLength += minLength;
        prevNum = curNum;
    }
    return totalLength;
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
    long long total = 0;
    while (std::getline(inputFile, nextLine)) {
        total += (getNumericPart(nextLine) * getFinalMoveStringLength2(nextLine, 2));
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
    long long total = 0;
    while (std::getline(inputFile, nextLine)) {
        total += (getNumericPart(nextLine) * getFinalMoveStringLength2(nextLine, 25));
    }
    std::cout << total;
}


int main() {
    part2();
    return 0;
}