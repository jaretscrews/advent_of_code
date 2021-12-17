#include <fstream>
#include <iostream>
#include <sstream>

#define FILE_PATH "day_2.txt"

int part1() {
    int distance = 0;
    int depth = 0;
    std::fstream file(FILE_PATH);
    while(file) {
        std::string line;
        std::getline(file, line);
        std::stringstream in(line);
        std::string command;
        int x;
        in >> command >> x;
        if(command == "forward") {
            distance += x;
        }
        else if(command == "down") {
            depth += x;
        }
        else if(command == "up") {
            depth -= x;
        }
    }
    std::cout << distance << " " << depth << std::endl;
    return distance * depth;
}

int part2() {
    int distance = 0;
    int depth = 0;
    int aim = 0;
    std::fstream file(FILE_PATH);
    while(file) {
        std::string line;
        std::getline(file, line);
        std::stringstream in(line);
        std::string command;
        int x;
        in >> command >> x;
        if(command == "forward") {
            distance += x;
            depth += (aim * x);
        }
        else if(command == "down") {
            aim += x;
        }
        else if(command == "up") {
            aim -= x;
        }
    }
    std::cout << distance << " " << depth << std::endl;
    return distance * depth;
}

int main() {
    std::cout << part1() << std::endl;
    std::cout << part2() << std::endl;
}
