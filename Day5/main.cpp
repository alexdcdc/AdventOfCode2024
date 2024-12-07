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
#include <unordered_map>
#include <unordered_set>

bool isValid(const std::vector<int>& nums, std::unordered_map<int, std::unordered_set<int>>& map) {
    for (int i = nums.size() - 1; i >= 0; i--) {
        for (int j = i - 1; j >= 0; j--) {
            if (map[nums[i]].find(nums[j]) != map[nums[i]].end()) {
                return false;
            }
        }
    }
    return true;
}

void sortSequence(std::vector<int>& nums, std::unordered_map<int, std::unordered_set<int>>& map) {
    int i = nums.size() - 1;
    while (i >= 0) {
        bool correct = true;
        for (int j = 0; j < i; j++) {
            if (map[nums[i]].find(nums[j]) != map[nums[i]].end()) {
                correct = false;
                int tmp = nums[i];
                nums[i] = nums[j];
                nums[j] = tmp;
            }
        }
        if (correct) {
            i--;
        }
    }
}

void part1() {
    std::ifstream inputFile("Day5/input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
    }

    std::unordered_map<int, std::unordered_set<int>> map;

    std::string nextLine;
    int key;
    int val;
    char pipe;
    while (std::getline(inputFile, nextLine)) {
        if (nextLine.empty()) {
            break;
        }
        std::stringstream s(nextLine);
        s >> key >> pipe >> val;
        if (map.find(key) == map.end()) {
            map[key] = std::unordered_set<int>{val};
        }
        else {
            map[key].insert(val);
        }
    }

    int total = 0;
    while (std::getline(inputFile, nextLine)) {
        std::vector<int> nums{};
        int nextNum;
        std::stringstream s(nextLine);
        char comma;
        while (s >> nextNum) {
            nums.push_back(nextNum);
            s >> comma;
        }

        if (isValid(nums, map)) {
            total += nums[nums.size()/2];
        }
    }

    std::cout << total << std::endl;

}

void part2() {
    std::ifstream inputFile("Day5/input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
    }

    std::unordered_map<int, std::unordered_set<int>> map;

    std::string nextLine;
    int key;
    int val;
    char pipe;
    while (std::getline(inputFile, nextLine)) {
        if (nextLine.empty()) {
            break;
        }
        std::stringstream s(nextLine);
        s >> key >> pipe >> val;
        if (map.find(key) == map.end()) {
            map[key] = std::unordered_set<int>{val};
        }
        else {
            map[key].insert(val);
        }
    }

    int total = 0;
    while (std::getline(inputFile, nextLine)) {
        std::vector<int> nums{};
        int nextNum;
        std::stringstream s(nextLine);
        char comma;
        while (s >> nextNum) {
            nums.push_back(nextNum);
            s >> comma;
        }

        if (!isValid(nums, map)) {
            sortSequence(nums, map);
            total += nums[nums.size()/2];
        }
    }

    std::cout << total << std::endl;
}


int main() {
    part2();
    return 0;
}
