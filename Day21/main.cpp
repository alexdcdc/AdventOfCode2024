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

//right up down left
std::string move(char start, char end, std::unordered_map<char, i_pair> map) {
    i_pair startPos = map[start];
    i_pair endPos = map[end];
    int di = endPos.first - startPos.first;
    int dj = endPos.second - startPos.second;

    std::string moveString;
    if (dj > 0) {
        moveString.append(dj, '>');
    }
    if (di < 0) {
        moveString.append(-di, '^');
    }
    if (di > 0) {
        moveString.append(di, 'v');
    }
    if (dj < 0) {
        moveString.append(-dj, '<');
    }
    return moveString;
}

std::string getNumMoveString(std::string code) {
    char prev = 'A';
    std::string moves;
    for (char c : code) {
        moves += move(prev, c, numericMap);
        moves += 'A';
        prev = c;
    }
    return moves;
}

std::string getDirMoveString(std::string dirs) {
    char prev = 'A';
    std::string moves;
    for (char c : dirs) {
        moves += move(prev, c, directionalMap);
        moves += 'A';
        prev = c;
    }
    return moves;
}


std::string getFinalMoveString(std::string code) {
    std::string robotCommands1 = getNumMoveString(code);
    //inputs that the first robot must enter (radioactive room)
    std::string robotCommands2 = getDirMoveString(robotCommands1);
    //inputs that the second robot must enter (-40 degree room)
    return getDirMoveString(robotCommands2);//optimal
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
}


int main() {
    std::cout << getFinalMoveString("379A").size() << std::endl;
    std::cout << getDirMoveString("^A<<^^A>>AvvvA") << " " << getDirMoveString(getDirMoveString("^A<<^^A>>AvvvA")).size() << std::endl;
    std::cout << getDirMoveString("^A^^<<A>>AvvvA") << " " << getDirMoveString(getDirMoveString("^A^^<<A>>AvvvA")).size() << std::endl;

    //part1();
    return 0;
}