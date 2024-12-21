#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <queue>
#include <sstream>
#include <regex>

long long registers[3];
long long& a = registers[0];
long long& b = registers[1];
long long& c = registers[2];
int ir = 0;
int arg;
std::queue<int> output;

long long decodeCombo(int n) {
    if (n < 4) {
        return n;
    }
    return registers[n - 4];
}

void adv() {
    a = a >> decodeCombo(arg);
}
void bxl() {
    b = b ^ arg;
}
void bst() {
    b = decodeCombo(arg) % 8;
}
void jnz() {
    if (a != 0) {
        ir = arg - 2;
    }
}
void bxc() {
    b = b ^ c;
}
void out() {
    output.push(decodeCombo(arg) % 8);
}
void bdv() {
    b = a >> decodeCombo(arg);
}
void cdv() {
    c = a >> decodeCombo(arg);
}

std::function<void()> isa[8] = {adv, bxl, bst, jnz, bxc, out, bdv, cdv};

int parseInt(const std::string& line) {
    std::regex exp(R"([^0-9]+(-?[0-9]+))");
    std::smatch match;
    if (std::regex_search(line, match, exp)) {
        return std::stoi(match[1]);
    }

    return -101;
}

std::string parseList(const std::string& line) {
    std::regex exp(R"([^0-9]+(-?[0-9,]+))");
    std::smatch match;
    if (std::regex_search(line, match, exp)) {
        return match[1];
    }

    return "";
}

void execute(const std::vector<int>& prog) {
    while (ir < prog.size()) {
        auto op = isa[prog[ir]];
        arg = prog[ir + 1];
        op();
        ir += 2;
    }
}

bool compareOutput(const std::vector<int>& prog) {
    int i = 0;
    while (!output.empty() && i < prog.size() && output.front() == prog[i]) {
        i++;
        output.pop();
    }
    if (!output.empty()) {
        std::queue<int> empty;
        output.swap(empty);
        return false;
    }
    return i == prog.size();
}

void printOutput() {
    while (!output.empty()) {
        std::cout << output.front();
        output.pop();
        if (!output.empty()) {
            std::cout << ",";
        }
    }
    std::cout << std::endl;
}

long long constructSolution(const std::vector<int>& sequence, const int index, const long long stem) {
    if (index < 0) {
        return stem;
    }
    int start = (index == sequence.size() - 1) ? 1 : 0;
    for (int i = start; i < 8; i++) {
        long long newNum = (stem << 3) + i;
        if ((i ^ ((newNum >> (i ^ 3)) % 8) ^ 6) == sequence[index]) {
            long long attemptedSol = constructSolution(sequence, index - 1, (stem << 3) + i);
            if (attemptedSol != -1) {
                return attemptedSol;
            }
        }
    }
    return -1;
}

void part1() {
    std::ifstream inputFile("Day17/input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }
    std::string nextLine;
    std::vector<int> prog;

    std::getline(inputFile, nextLine);
    registers[0] = parseInt(nextLine);
    std::getline(inputFile, nextLine);
    registers[1] = parseInt(nextLine);
    std::getline(inputFile, nextLine);
    registers[2] = parseInt(nextLine);

    std::getline(inputFile, nextLine);
    std::getline(inputFile, nextLine);
    nextLine = parseList(nextLine);
    std::stringstream s(nextLine);
    int next;
    char comma;
    while (s >> next) {
        prog.push_back(next);
        s >> comma;
    }
    execute(prog);
    printOutput();
}



void part2() {
    std::ifstream inputFile("Day17/input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }
    std::string nextLine;
    std::vector<int> prog;

    std::getline(inputFile, nextLine);
    registers[0] = parseInt(nextLine);
    std::getline(inputFile, nextLine);
    registers[1] = parseInt(nextLine);
    std::getline(inputFile, nextLine);
    registers[2] = parseInt(nextLine);

    std::getline(inputFile, nextLine);
    std::getline(inputFile, nextLine);
    nextLine = parseList(nextLine);
    std::stringstream s(nextLine);
    int next;
    char comma;
    while (s >> next) {
        prog.push_back(next);
        s >> comma;
    }

    std::cout << constructSolution(prog, prog.size() - 1, 0);
}


int main() {
    part2();
    return 0;
}

