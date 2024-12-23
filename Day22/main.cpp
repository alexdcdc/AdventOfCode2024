#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <queue>
#include <sstream>
#include <regex>
#include <unordered_map>
long long prune = 16777216;
long long getRandom(long long num, int iterations) {
    for (int i = 0; i < iterations; i++) {
        num = (num ^ (num << 6)) % prune;
        num = (num ^ (num >> 5)) % prune;
        num = (num ^ (num << 11)) % prune;
    }
    return num;
}

std::vector<int> generateSequence(long long num, int iterations) {
    std::vector<int> seq = {};
    seq.push_back(num % 10);
    for (int i = 0; i < iterations; i++) {
        num = (num ^ (num << 6)) % prune;
        num = (num ^ (num >> 5)) % prune;
        num = (num ^ (num << 11)) % prune;
        seq.push_back(num % 10);
    }
    return seq;
}

std::string stringify(std::queue<int> q) {
    std::string s;
    while (!q.empty()) {
        s.append(std::to_string(q.front()));
        q.pop();
    }
    return s;
}

std::string stringifyNums(int a, int b, int c, int d) {
    std::string s = std::to_string(a) + std::to_string(b) + std::to_string(c) + std::to_string(d);
    return s;
}

std::unordered_map<std::string, int> mapOccurrences(std::vector<int> seq) {
    std::unordered_map<std::string, int> seen;
    std::queue<int> q;
    q.push(0);

    int i = 1;
    while (q.size() < 4) {
        q.push(seq[i] - seq[i - 1]);
        i++;
    }
    while (i < seq.size()) {
        q.pop();
        q.push(seq[i] - seq[i - 1]);
        std::string key = stringify(q);
        if (seen.find(key) == seen.end()) {
            seen[key] = seq[i];
        }
        i++;
    }
    return seen;
}


void part1() {
    std::ifstream inputFile("Day22/test_input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }

    std::vector<std::unordered_map<std::string, int>> maps;
    std::string nextLine;
    long long total = 0;
    while (std::getline(inputFile, nextLine)) {
        long long num = std::stoi(nextLine);
        total += getRandom(num, 2000);
    }



    std::cout << total;
}

void part2() {
    std::ifstream inputFile("Day22/input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }

    std::vector<std::unordered_map<std::string, int>> maps;
    std::unordered_map<std::string, int> totals;
    std::string nextLine;

    while (std::getline(inputFile, nextLine)) {
        long long num = std::stoi(nextLine);
        std::vector<int> seq = generateSequence(num, 2000);
        maps.push_back(mapOccurrences(seq));
    }

    long long maxTotal = 0;
    for (auto seq : maps) {
        for (auto [k, count] : seq) {
            if (totals.find(k) == totals.end()) {
                totals[k] == 0;
            }
            totals[k] += count;
            if (totals[k] > maxTotal) {
                maxTotal = totals[k];
            }
        }

    }

    std::cout << maxTotal << std::endl;
}


int main() {
    part2();
    return 0;
}