#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <regex>
#include <unordered_map>

long long calls = 0;
std::vector<long long> getNext(long long n) {
    if (n == 0) {
        return {1};
    }
    int numDigits = 0;
    long long nCopy = n;
    while (nCopy > 0) {
        nCopy = nCopy/10;
        numDigits++;
    }

    if (numDigits % 2 == 0) {
        numDigits/=2;
        int powerOfTen = 1;
        while (numDigits > 0) {
            powerOfTen *= 10;
            numDigits -= 1;
        }

        return {n/powerOfTen, n%powerOfTen};
    }

    return {n * 2024};
}

long long countRocksAfterIterations(const std::vector<long long> nums, int iterations, std::map<std::pair<long long, int>, long long>& memo) {
    calls++;
    if (iterations <= 0) {
        return nums.size();
    }

    long long total = 0;
    for (long long n : nums) {
        if (memo.find({n, iterations}) != memo.end()) {
            total += memo[{n, iterations}];
        }
        else {
            std::vector<long long> nextIteration = getNext(n);
            long long subTotal = countRocksAfterIterations(nextIteration, iterations - 1, memo);
            memo[{n, iterations}] = subTotal;
            total += subTotal;
        }
    }

    return total;
}

void part1() {
    std::ifstream inputFile("Day11/input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }

    std::vector<long long> nums{};
    std::string nextLine;
    std::getline(inputFile, nextLine);

    std::stringstream s(nextLine);
    int nextNum;
    while (s >> nextNum) {
        nums.push_back(nextNum);
    }
    std::map<std::pair<long long, int>, long long> memo;
    std::cout << countRocksAfterIterations(nums, 25, memo) << std::endl;

}

void part2() {
    std::ifstream inputFile("Day11/input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }

    std::vector<long long> nums{};
    std::string nextLine;
    std::getline(inputFile, nextLine);

    std::stringstream s(nextLine);
    int nextNum;
    while (s >> nextNum) {
        nums.push_back(nextNum);
    }
    std::map<std::pair<long long, int>, long long> memo;
    std::cout << countRocksAfterIterations(nums, 75, memo) << std::endl;
}


int main() {
    part2();
    std::cout << calls << std::endl;
    return 0;
}
