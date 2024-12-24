#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <regex>
#include <unordered_map>
#include <unordered_set>

std::pair<std::string, std::string> parseLine(std::string line) {
    return {line.substr(0, 2), line.substr(3, 2)};
}

void addEdge(std::unordered_map<std::string, std::unordered_set<std::string>>& network, const std::string& v1, const std::string& v2) {
    if (network.find(v1) == network.end()) {
        network[v1] = std::unordered_set<std::string>{};
    }
    if (network.find(v2) == network.end()) {
        network[v2] = std::unordered_set<std::string>{};
    }
    network[v1].insert(v2);
    network[v2].insert(v1);
}

std::string stringify(std::vector<std::string> comps) {
    std::sort(comps.begin(), comps.end());
    std::string result;
    for (std::string& comp : comps) {
        result.append(comp);
    }
    return result;
}


void part1() {
    std::ifstream inputFile("Day23/input.txt");
    std::unordered_map<std::string, std::unordered_set<std::string>> network;
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }

    std::string nextLine;
    int count = 0;
    while (std::getline(inputFile, nextLine)) {
        auto [v1, v2] = parseLine(nextLine);
        addEdge(network, v1, v2);
        for (std::string v3 : network[v1]) {
            if (network[v2].find(v3) != network[v2].end() && (v1[0] == 't' || v2[0] == 't' || v3[0] == 't')) {
                count++;
            }
        }
    }

    std::cout << count << std::endl;
}

void part2() {
    std::ifstream inputFile("Day23/input.txt");
    std::unordered_map<std::string, std::unordered_set<std::string>> network;
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }

    std::string nextLine;
    std::vector<std::vector<std::vector<std::string>>> groups;
    std::vector<std::vector<std::string>> threeGroups;
    while (std::getline(inputFile, nextLine)) {
        auto [v1, v2] = parseLine(nextLine);
        addEdge(network, v1, v2);
        for (std::string v3 : network[v1]) {
            if (network[v2].find(v3) != network[v2].end() && (v1[0] == 't' || v2[0] == 't' || v3[0] == 't')) {
                threeGroups.push_back({v1, v2, v3});
            }
        }
    }
    groups.push_back(threeGroups);
    int n = 4;
    while (!groups[groups.size() - 1].empty()) {
        std::cout << n << std::endl;
        std::vector<std::vector<std::string>> next;
        std::unordered_set<std::string> seen;
        auto prev = groups[groups.size() - 1];
        for (std::vector group : prev) {
            for (std::string v : network[group[0]]) {
                bool allConnected = true;
                for (int i = 1; i < group.size(); i++) {
                    allConnected = allConnected && (network[group[i]].find(v) != network[group[i]].end());
                    if (!allConnected) {
                        break;
                    }
                }
                if (allConnected) {
                    auto longer = group;
                    longer.push_back(v);
                    std::string hash = stringify(longer);
                    if (seen.find(hash) == seen.end()) {
                        next.push_back(longer);
                        seen.insert(hash);
                    }
                }
            }
        }
        groups.push_back(next);
        n++;
    }

    auto final = groups[groups.size() - 2][0];
    std::sort(final.begin(), final.end());

    for (std::string s : final) {
        std::cout << s << ",";
    }
    std::cout << std::endl;

}


int main() {
    part2();
    return 0;
}