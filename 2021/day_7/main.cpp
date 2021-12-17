#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <limits>
#define FILE_PATH "day_7.txt"

int part1() {
    int fuel = std::numeric_limits<int>::max();
    std::vector<int> positions;
    std::fstream file(FILE_PATH);
    std::string line;
    std::getline(file, line);
    std::stringstream in(line);
    int x;
    char comma;
    while(in >> x >> comma)
        positions.push_back(x);
    positions.push_back(x);
    int max = *std::max_element(positions.begin(), positions.end());
    for(int i = 0; i < max; i++) {
        int fuel_used = 0;
        for(const auto& pos : positions) {
            if(fuel_used > fuel) break;
            fuel_used += abs(pos - i);
        }
        fuel = std::min(fuel_used, fuel);
    }
    return fuel;
}

int part2() {
    int fuel = std::numeric_limits<int>::max();
    std::vector<int> positions;
    std::fstream file(FILE_PATH);
    std::string line;
    std::getline(file, line);
    std::stringstream in(line);
    int x;
    char comma;
    while(in >> x >> comma)
        positions.push_back(x);
    positions.push_back(x);
    int max = *std::max_element(positions.begin(), positions.end());
    for(int i = 0; i < max; i++) {
        int fuel_used = 0;
        for(const auto& pos : positions) {
            if(fuel_used > fuel) break;
            auto distance = abs(pos - i);
            int move_fuel = 0;
            int j = 1;
            while(distance > 0) {
                move_fuel += j++;
                distance--;
            }
            fuel_used += move_fuel;
        }
        fuel = std::min(fuel_used, fuel);
    }
    return fuel;
}

int main() {
    std::cout << part2() << std::endl;
}