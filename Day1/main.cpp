//
// Created by alexd on 12/5/2024.
//
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

void part1() {
    std::ifstream inputFile("Day1/input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }

    std::vector<int> list1{};
    std::vector<int> list2{};

    int num1;
    int num2;

    while (inputFile >> num1 >> num2) {
        list1.push_back(num1);
        list2.push_back(num2);
    }

    std::sort(list1.begin(), list1.end());
    std::sort(list2.begin(), list2.end());

    long totalDistance = 0;
    for (int i = 0; i < list1.size(); i++) {
        totalDistance += std::abs(list1[i] - list2[i]);
    }

    std::cout << totalDistance << std::endl;
}

void part2() {
    std::ifstream inputFile("Day1/input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }

    std::vector<int> list1{};
    std::vector<int> list2{};

    int num1;
    int num2;

    while (inputFile >> num1 >> num2) {
        list1.push_back(num1);
        list2.push_back(num2);
    }

    std::map<int, int> counter;
    for (int i : list2) {
        counter[i] = (counter.find(i) != counter.end()) ? counter[i] + 1 : 1;
    }

    int similarity = 0;
    for (int i : list1) {
        int count = (counter.find(i) != counter.end()) ? counter[i] : 0;
        std::cout << count << " " << i << std::endl;
        similarity += i * count;
    }

    std::cout << similarity << std::endl;
}


int main() {
    part2();
    return 0;
}
