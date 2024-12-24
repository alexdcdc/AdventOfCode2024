#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <queue>
#include <sstream>
#include <regex>
#include <unordered_map>

std::pair<std::string, int> parseVal(std::string line) {
    std::regex exp(R"((.{3}): (0|1))");
    std::smatch match;
    if (std::regex_match(line, match, exp)) {
        std::string var = match[1];
        int val = std::stoi(match[2]);
        return {var, val};
    }
    return {"", -1};
}


std::vector<std::string> parseOp(std::string line) {
    std::regex exp(R"((.{3}) (AND|XOR|OR) (.{3}) -> (.{3}))");
    std::smatch match;
    if (std::regex_match(line, match, exp)) {
        std::string var1 = match[1];
        std::string op = match[2];
        std::string var2 = match[3];
        std::string result = match[4];
        return {var1, op, var2, result};
    }
    return {"", "", "", ""};
}

bool isEvalable(const std::vector<std::string>& expr, std::unordered_map<std::string, int>& vars) {
    return vars[expr[0]] != -1 && vars[expr[2]] != -1 && vars[expr[3]] == -1;
}

std::string eval(const std::vector<std::string>& expr, std::unordered_map<std::string, int>& vars) {
    int arg1 = vars[expr[0]];
    int arg2 = vars[expr[2]];
    if (expr[1] == "OR") {
        vars[expr[3]] = arg1 | arg2;
    }
    else if (expr[1] == "AND") {
        vars[expr[3]] = arg1 & arg2;
    }
    else if (expr[1] == "XOR") {
        vars[expr[3]] = arg1 ^ arg2;
    }
    return expr[3];
}

long long makeOutput(std::unordered_map<std::string, int>& vars) {
    std::string id = "z00";
    long long result = 0;
    int exp = 0;
    while (vars.find(id) != vars.end()) {
        result += (static_cast<long long>(vars[id]) << exp);
        exp++;
        id[2]++;
        if (id[2] > '9') {
            id[2] = '0';
            id[1]++;
        }
    }
    return result;
}

void part1() {
    std::ifstream inputFile("Day24/input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
    }

    std::unordered_map<std::string, int> vars;
    std::unordered_map<std::string, std::vector<std::vector<std::string>>> exprs;

    std::string nextLine;
    while (std::getline(inputFile, nextLine) && !nextLine.empty()) {
        auto [var, val] = parseVal(nextLine);
        vars[var] = val;
    }

    std::queue<std::vector<std::string>> todo;
    while (std::getline(inputFile, nextLine)) {
        auto expr = parseOp(nextLine);
        todo.push(expr);
        exprs[expr[0]].push_back(expr);
        exprs[expr[2]].push_back(expr);
        if (vars.find(expr[0]) == vars.end()) {
            vars[expr[0]] = -1;
        }
        if (vars.find(expr[2]) == vars.end()) {
            vars[expr[2]] = -1;
        }
        if (vars.find(expr[3]) == vars.end()) {
            vars[expr[3]] = -1;
        }
    }

    while (!todo.empty()) {
        std::vector<std::string> next = todo.front();
        todo.pop();
        if (isEvalable(next, vars)) {
            std::string out = eval(next, vars);
            for (const auto& expr : exprs[out]) {
                todo.push(expr);
            }
        }
    }

    std::cout << makeOutput(vars) << std::endl;
}

void part2() {
    std::ifstream inputFile("Day24/input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }
}


int main() {
    part1();
    return 0;
}