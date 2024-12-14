#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <regex>
#include <set>

typedef long long xlong;
#define NO_SOL {0, 0};

std::pair<xlong, xlong> solveSystem(xlong x1, xlong y1, xlong c1, xlong x2, xlong y2, xlong c2) {
    xlong oldX1 = x1;
    xlong oldY1 = y1;
    xlong oldC1 = c1;

    while (x1 != 0) {
        xlong newX1 = x2 % x1;
        xlong factor = (x2 - newX1)/x1;
        xlong newY1 = y2 - factor * y1;
        xlong newC1 = c2 - factor * c1;
        x2 = x1;
        y2 = y1;
        c2 = c1;
        x1 = newX1;
        y1 = newY1;
        c1 = newC1;
    }

    if (c1 % y1 != 0) {
        return NO_SOL;
    }

    xlong bSol = c1/y1;
    if ((oldC1 - oldY1 * bSol) % oldX1 != 0) {
        return NO_SOL;
    }
    xlong aSol = (oldC1 - oldY1 * bSol)/oldX1;

    return {aSol, bSol};

}

xlong calcScore(std::pair<xlong, xlong> vecs) {
    return 3 * vecs.first + vecs.second;
}

xlong calcTokens(std::pair<xlong, xlong> buttonA, std::pair<xlong, xlong> buttonB, std::pair<xlong, xlong> result) {
    auto solution = solveSystem(buttonA.first, buttonB.first, result.first, buttonA.second, buttonB.second, result.second);
    return calcScore(solution);
}



std::pair<xlong, xlong> parseButton(std::string line) {
    std::smatch matches;
    std::regex buttonExp (R"([^0-9]+([0-9]+)[^0-9]+([0-9]+))");

    if (std::regex_match(line, matches, buttonExp)) {
        return {std::stoi(matches[1]), std::stoi(matches[2])};
    }
    std::cerr << "bruh." << std::endl;
    return {};
}

void part1() {
    std::ifstream inputFile("Day13/input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }


    std::vector<std::pair<xlong, xlong>> aPairs, bPairs, resultPairs;

    std::string lineA, lineB, linePrize, lineBlank;
    while (std::getline(inputFile, lineA)) {
        std::getline(inputFile, lineB);
        std::getline(inputFile, linePrize);
        std::getline(inputFile, lineBlank);
        aPairs.push_back(parseButton(lineA));
        bPairs.push_back(parseButton(lineB));
        resultPairs.push_back(parseButton(linePrize));
    }
    xlong total = 0;

    for (xlong i = 0; i < aPairs.size(); i++) {
        total += calcTokens(aPairs[i], bPairs[i], resultPairs[i]);
    }

    std::cout << total << std::endl;

}

void part2() {
        std::ifstream inputFile("Day13/input.txt");

        if (!inputFile.is_open()) {
            std::cerr << "Error: Unable to open the file." << std::endl;
            return;
        }


        std::vector<std::pair<xlong, xlong>> aPairs, bPairs, resultPairs;

        std::string lineA, lineB, linePrize, lineBlank;
        while (std::getline(inputFile, lineA)) {
            std::getline(inputFile, lineB);
            std::getline(inputFile, linePrize);
            std::getline(inputFile, lineBlank);
            aPairs.push_back(parseButton(lineA));
            bPairs.push_back(parseButton(lineB));
            auto origPair = parseButton(linePrize);
            origPair.first += 10000000000000;
            origPair.second += 10000000000000;
            resultPairs.push_back(origPair);
        }
        xlong total = 0;

        for (xlong i = 0; i < aPairs.size(); i++) {
            total += calcTokens(aPairs[i], bPairs[i], resultPairs[i]);
        }

        std::cout << total << std::endl;
}


int main() {
    //auto solution = solveSystem(94, 22, 8400, 34, 67, 5400);
    //std::cout << solution.first << " " << solution.second << std::endl;
    part2();
    return 0;
}
