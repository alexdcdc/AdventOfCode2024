#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <regex>

void part1() {
    std::ifstream inputFile("Day9/input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }

    std::string line;
    std::getline(inputFile, line);

    std::vector<int> mem{};
    bool empty = false;
    int id = 0;

    for (int i = 0; i < line.size(); i++) {
        for (int j = 0; j < (line[i] - '0'); j++) {
            mem.push_back(empty ? -1 : id);
        }
        empty = !empty;
        if (!empty) {
            id++;
        }
    }

    int left = 0;
    int right = mem.size() - 1;

    while (left < right) {
        while (mem[right] < 0 && right > left) {
            right--;
        }
        while (mem[left] >= 0 && left < right) {
            left++;
        }

        if (left == right) break;

        mem[left] = mem[right];
        mem[right] = -1;
    }
/*
    for (int n : mem) {
        std::cout << n << " ";
    }
    std::cout << std::endl;*/

    long long checksum = 0;
    for (int i = 0; i < mem.size(); i++) {
        if (mem[i] < 0) {
            break;
        }
        checksum += (mem[i] * i);
    }
    std::cout << checksum << std::endl;

}

void part2() {
    std::ifstream inputFile("Day9/input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }

    std::string line;
    std::getline(inputFile, line);

    std::vector<std::pair<int, int>> free_list{};
    std::vector<std::pair<int, int>> block_list{};

    bool empty = false;
    int size = 0;

    for (int i = 0; i < line.size(); i++) {
        if (empty) {
            free_list.emplace_back(std::pair{size, line[i] - '0'});
        }
        else {
            block_list.emplace_back(std::pair{size, line[i] - '0'});
        }
        size += line[i] - '0';
        empty = !empty;
    }

    for (int i = block_list.size() - 1; i >= 0; i--) {
        for (int j = 0; j < free_list.size() && free_list[j].first < block_list[i].first; j++) {
            if (free_list[j].second >= block_list[i].second) {
                block_list[i].first = free_list[j].first;
                free_list[j].second -= block_list[i].second;
                free_list[j].first += block_list[i].second;
            }
        }
    }


    long long checksum = 0;
    for (int i = 0; i < block_list.size(); i++) {
        int start = block_list[i].first;
        int length = block_list[i].second;
        long long totalAddition = ((start + start + length - 1) * length)/2;
        checksum += (i * totalAddition);
    }

    std::cout << checksum << std::endl;
}


int main() {
    part2();
    return 0;
}
