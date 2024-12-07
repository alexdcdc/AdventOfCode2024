
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <regex>

bool canBeMade(long long target, const std::vector<int>& nums, int i) {
    if (i == 0) {
        return (nums[i] == target);
    }

    int curNum = nums[i];
    int result = false;

    if (curNum != 0 && target % curNum == 0) {
        result = canBeMade(target/curNum, nums, i - 1);
    }

    result = result || canBeMade(target - curNum, nums, i - 1);

    return result;
}

long long cutSuffix(long long num, int suffix) {
    if (suffix > num) return -1;
    while (suffix > 0) {
        if (num % 10 != suffix % 10) {
            return -1;
        }
        num = num/10;
        suffix = suffix/10;
    }

    return num;
}

bool canBeMade2(long long target, const std::vector<int>& nums, int i) {
    if (i == 0) {
        return (nums[i] == target);
    }

    int curNum = nums[i];
    int result = false;

    if (target % curNum == 0) {
        result = canBeMade2(target/curNum, nums, i - 1);
    }

    long long suffixResult = cutSuffix(target, curNum);
    if (suffixResult != -1) {
        result = result || canBeMade2(suffixResult, nums, i - 1);
    }

    result = result || canBeMade2(target - curNum, nums, i - 1);

    return result;
}

void part1() {
    std::ifstream inputFile("Day7/input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }

    std::string nextLine;
    long long total;

    while (std::getline(inputFile, nextLine)) {
        std::stringstream s(nextLine);
        long long target;
        char c;
        s >> target;
        s >> c;

        int nextNum;
        std::vector<int> nums{};

        while (s >> nextNum) {
            nums.push_back(nextNum);
        }

        if (canBeMade(target, nums, nums.size() - 1)) {
            total += target;
        }
    }

    std::cout << total << std::endl;


}

void part2() {
    std::ifstream inputFile("Day7/input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }

    std::string nextLine;
    long long total;

    while (std::getline(inputFile, nextLine)) {
        std::stringstream s(nextLine);
        long long target;
        char c;
        s >> target;
        s >> c;

        int nextNum;
        std::vector<int> nums{};

        while (s >> nextNum) {
            nums.push_back(nextNum);
        }

        if (canBeMade2(target, nums, nums.size() - 1)) {
            total += target;
        }
    }

    std::cout << total << std::endl;
}


int main() {
    part2();
    return 0;
}
