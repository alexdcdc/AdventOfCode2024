//
// Created by alexd on 12/5/2024.
//
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>

bool sameSign(int n1, int n2) {
    return n1 * n2 >= 0;
}

bool isMonotonic(std::vector<int> v) {
    int prevDiff = 0;
    for (int i = 1; i < v.size(); i++) {
        int diff = v[i] - v[i - 1];
        if (!sameSign(diff, prevDiff) || abs(diff) > 3 || abs(diff) < 1) {
            return false;
        }
        prevDiff = diff;
    }
    return true;
}

std::vector<int> makeNewList(std::vector<int> v, int to_exclude) {
    std::vector<int> new_vector{};
    for (int i = 0; i < v.size(); i++) {
        if (i != to_exclude) {
            new_vector.push_back(v[i]);
        }
    }
    return new_vector;
}

bool isMonotonic2(std::vector<int> v) {
    for (int i = 0; i < v.size(); i++) {
        if (isMonotonic(makeNewList(v, i))) {
            return true;
        }
    }
    return false;
}

void part1() {
    std::ifstream inputFile("Day2/input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }

    int safeCount = 0;
    std::string nextLine;
    while (std::getline(inputFile, nextLine)) {
        std::vector<int> nums{};
        std::stringstream s(nextLine);
        int nextNum;
        while (s >> nextNum) {
            nums.push_back(nextNum);
        }
        if (isMonotonic(nums)) {
            for (int n : nums) {
                std::cout << n << " ";
            }
            std::cout << std::endl;
            safeCount++;
        }
    }

    std::cout << safeCount << std::endl;

}

void part2() {
    std::ifstream inputFile("Day2/input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }

    int safeCount = 0;
    std::string nextLine;
    while (std::getline(inputFile, nextLine)) {
        std::vector<int> nums{};
        std::stringstream s(nextLine);
        int nextNum;
        while (s >> nextNum) {
            nums.push_back(nextNum);
        }
        if (isMonotonic2(nums)) {
            for (int n : nums) {
                std::cout << n << " ";
            }
            std::cout << std::endl;
            safeCount++;
        }
    }

    std::cout << safeCount << std::endl;
}


int main() {
    part2();
    return 0;
}
