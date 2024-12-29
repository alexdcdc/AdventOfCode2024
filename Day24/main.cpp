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

long long makeOutput(std::unordered_map<std::string, int>& vars, std::string prefix) {
    std::string id = prefix + "00";
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

void printExpr(const std::vector<std::string>& expr) {
    std::cout << expr[0] << " " << expr[1] << " " << expr[2] << " -> " << expr[3] << std::endl;
}

void printExprTree(const std::string& result, std::unordered_map<std::string, std::vector<std::string>>& results) {
    std::queue<std::string> q;
    q.push(result);
    while (!q.empty()) {
        std::string var = q.front();
        q.pop();
        if (results.find(var) != results.end()) {
            auto expr = results[var];
            printExpr(expr);
            q.push(expr[0]);
            q.push(expr[2]);
        }
    }
}

std::string toBinaryString(long long n) {
    std::string bin;
    int i = 0;
    while (i < 64) {
        char c = '0' + n % 2;
        bin = c+bin;
        n = n >> 1;
        i++;
    }
    return bin;
}

std::string makeId(int n) {
    if (n >= 10) {
        return std::to_string(n);
    }
    return "0" + std::to_string(n);
}

std::string locateKey(std::unordered_map<std::string, std::vector<std::string>> exprs, std::string op, std::string var1, std::string var2) {
    for (auto [k, v] : exprs) {
        if (v[1] == op && ((v[0] == var1 && v[2] == var2) || (v[0] == var2 && v[2] == var1))) {
            return v[3];
        }
    }
    std::cerr << var1 << " " << op << " " << var2 << std::endl;
    exit(-1);
    //return "";
}

std::vector<std::string> validate(std::unordered_map<std::string, std::vector<std::string>> exprs) {
    int i = 0;
    std::unordered_map<std::string, std::string> rename;

    while (exprs.find("z" + makeId(i)) != exprs.end()) {
        std::cout << i << std::endl;
        if (i == 0) {
            rename["z00"] = locateKey(exprs, "XOR", "x00", "y00");
            rename["c00"] = locateKey(exprs, "AND", "x00", "y00");
        }
        else {
            std::string curId = makeId(i);
            std::string prevId = makeId(i - 1);
            rename["a" + curId] = locateKey(exprs, "XOR", "x" + curId, "y" + curId);
            rename["z" + curId] = locateKey(exprs, "XOR", rename["a" + curId], rename["c" + prevId]);
            rename["b" + curId] = locateKey(exprs, "AND", "x" + curId, "y" + curId);
            rename["d" + curId] = locateKey(exprs, "AND", rename["a" + curId], rename["c" + prevId]);
            rename["c" + curId] = locateKey(exprs, "OR", rename["b" + curId], rename["d" + curId]);
        }
        i++;
    }

    std::cout << i << std::endl;
    return {};
}

/*
void fix(int n, std::pair<std::string, std::string> pair) {

}
*/

void part1() {
    std::ifstream inputFile("Day24/input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
    }

    std::unordered_map<std::string, int> vars;
    std::unordered_map<std::string, std::vector<std::vector<std::string>>> exprs;
    std::unordered_map<std::string, std::vector<std::string>> results;

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
            results[out] = next;
            for (const auto& expr : exprs[out]) {
                todo.push(expr);
            }
        }
    }

    std::cout << makeOutput(vars, "z") << std::endl;
}

void part2() {
    std::ifstream inputFile("Day24/input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
    }

    std::unordered_map<std::string, int> vars;
    std::unordered_map<std::string, std::vector<std::vector<std::string>>> exprs;
    std::unordered_map<std::string, std::vector<std::string>> results;

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
            results[out] = next;
            for (const auto& expr : exprs[out]) {
                todo.push(expr);
            }
        }
    }

    printExprTree("z02", results);
    validate(results);
    //std::cout << toBinaryString(makeOutput(vars, "z") ^ (makeOutput(vars, "x") + makeOutput(vars, "y"))) << std::endl;
}


int main() {
    part2();
    return 0;
}