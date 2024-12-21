#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <regex>
#include <unordered_set>

bool canBeMade(std::string towel, std::unordered_set<std::string> stripes) {
    bool validSubstr[towel.size() + 1]; //validSubstr[i] represents whether towel[i:] can be made
    validSubstr[towel.size()] = true;
    for (int i = towel.size() - 1; i >= 0; i--) {
        validSubstr[i] = false;
        for (int j = 1; j <= towel.size() - i; j++) { //fr. index i + 1 to index towel.size() max substr length is towel.size() - i
            std::string toFind = towel.substr(i, j);
            if (stripes.find(toFind) != stripes.end() && validSubstr[i + j]) {
                validSubstr[i] = true;
                break;
            }
        }
    }
    return validSubstr[0];
}

long long countWaysToMake(std::string towel, std::unordered_set<std::string> stripes) {
    std::vector<long long> validSubstr(towel.size() + 1, 0);
    //validSubstr[i] represents whether towel[i:] can be made
    validSubstr[towel.size()] = 1;
    for (int i = towel.size() - 1; i >= 0; i--) {
        for (int j = 1; j <= towel.size() - i; j++) { //fr. index i + 1 to index towel.size() max substr length is towel.size() - i
            std::string toFind = towel.substr(i, j);
            if (stripes.find(toFind) != stripes.end()) {
                validSubstr[i] += validSubstr[i + j];
            }
        }
    }

    return validSubstr[0];
}

void part1() {
    std::ifstream inputFile("Day19/input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }

    std::string nextLine;
    std::unordered_set<std::string> stripes;

    std::getline(inputFile, nextLine);
    std::stringstream s(nextLine);
    std::string token;
    while (s >> token) {
        if (token[token.size() - 1] == ',') {
            token = token.substr(0, token.size() - 1); //strip trailing comma
        }
        stripes.insert(token);
    }

    std::getline(inputFile, nextLine); //skip blank line

    int count = 0;
    while (std::getline(inputFile, nextLine)) {
        if (canBeMade(nextLine, stripes)) {
            count++;
        }
    }

    std::cout << count << std::endl;

}

void part2() {
    std::ifstream inputFile("Day19/input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }

    std::string nextLine;
    std::unordered_set<std::string> stripes;

    std::getline(inputFile, nextLine);
    std::stringstream s(nextLine);
    std::string token;
    while (s >> token) {
        if (token[token.size() - 1] == ',') {
            token = token.substr(0, token.size() - 1); //strip trailing comma
        }
        stripes.insert(token);
    }

    std::getline(inputFile, nextLine); //skip blank line

    long long count = 0;
    while (std::getline(inputFile, nextLine)) {
        count += countWaysToMake(nextLine, stripes);
    }

    std::cout << count << std::endl;
}


int main() {
    part2();
    return 0;
}