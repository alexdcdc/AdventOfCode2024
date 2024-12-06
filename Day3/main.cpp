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

void part1() {
    std::ifstream inputFile("Day3/input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }


    std::stringstream buff;
    buff << inputFile.rdbuf();

    std::smatch matches;
    std::string text = buff.str();
    std::regex exp ("mul\\(([1-9][0-9]*),([1-9][0-9]*)\\)");

    int total = 0;
    while (std::regex_search(text, matches, exp)) {
        std::string match = matches[0];
        std::string s1 = matches[1];
        std::string s2 = matches[2];
        int n1 = stoi(s1);
        int n2 = stoi(s2);
        total += n1 * n2;
        text = matches.suffix().str();
        std::cout << match << " " << n1 << "," << n2 << std::endl;
    }

    std::cout << total << std::endl;

}

void part2() {
    std::ifstream inputFile("Day3/input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }


    std::stringstream buff;
    buff << inputFile.rdbuf();

    std::smatch matches;
    std::string text = buff.str();
    std::regex doExp (R"(do\(\))");
    std::regex dontExp (R"(don't\(\))");
    std::regex mulExp (R"(mul\(([1-9][0-9]*),([1-9][0-9]*)\))");
    //std::regex exp (R"((?:do\(\)).{1,9}mul\(([1-9][0-9]*),([1-9][0-9]*)\))");

    int total = 0;
    bool enabled = true;
    auto continuous = std::regex_constants::match_continuous;
    while (!text.empty()) {
        if (std::regex_search(text, matches, doExp, continuous)) {
            enabled = true;
            text = matches.suffix().str();

        }
        else if (std::regex_search(text, matches, dontExp, continuous)) {
            enabled = false;
            text = matches.suffix().str();

        }
        else if (std::regex_search(text, matches, mulExp, continuous)) {
            if (enabled) {
                total += (stoi(matches[1]) * stoi(matches[2]));
            }
            text = matches.suffix().str();
        }
        else {
            text = text.substr(1);
        }

    }

    std::cout << total << std::endl;
}


int main() {
    part2();
    return 0;
}
