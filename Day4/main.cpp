//
// Created by alexd on 12/5/2024.
//
//
// Created by alexd on 12/5/2024.
//

//
// Created by alexd on 12/5/2024.
//
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <regex>

int checkDirection(const int i, const int j, const int di, const int dj, const std::string& str, const std::vector<std::string>& arr) {
    if (str.empty()) {
        return 1;
    }
    if (i < 0 || i >= arr.size() || j < 0 || j >= arr[0].size()) {
        return 0;
    }
    if (arr[i][j] != str[0]) {
        return 0;
    }
    return checkDirection(i + di, j + dj, di, dj, str.substr(1), arr);
}

int checkXmas(const int i, const int j, const std::vector<std::string>& arr) {
    std::vector<std::string> valid = {"MMASS", "SSAMM", "SMASM", "MSAMS"};
    const std::string toCompare{arr[i - 1][j - 1], arr[i - 1][j + 1], arr[i][j], arr[i + 1][j - 1], arr[i + 1][j + 1]};

    for (std::string& str : valid) {
        if (toCompare == str) {
            return 1;
        }
    }
    return 0;
}

void part1() {
    std::ifstream inputFile("Day4/input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }

    std::vector<std::string> v;
    std::string nextLine;
    while (std::getline(inputFile, nextLine)) {
        v.push_back(nextLine);
    }

    int count = 0;
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v[i].size(); j++) {
            for (int di = -1; di <= 1; di++) {
                for (int dj = -1; dj <= 1; dj++) {
                    count += checkDirection(i, j, di, dj, "XMAS", v);
                }
            }
        }
    }

    std::cout << count << std::endl;
}

void part2() {
    std::ifstream inputFile("Day4/input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }

    std::vector<std::string> v;
    std::string nextLine;
    while (std::getline(inputFile, nextLine)) {
        v.push_back(nextLine);
    }

    int count = 0;
    for (int i = 1; i < v.size() - 1; i++) {
        for (int j = 1; j < v[i].size() - 1; j++) {
                count += checkXmas(i, j, v);
            }
        }

    std::cout << count << std::endl;
}


int main() {
    part2();
    return 0;
}
