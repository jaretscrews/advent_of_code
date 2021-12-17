#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <boost/multiprecision/cpp_int.hpp>
using namespace boost::multiprecision;
#define FILE_PATH "day_6.txt"

#define NUMBER_OF_DAYS 80

struct lantern_fish {
    int timer = 8;
    lantern_fish(int x) : timer(x) {}
};

void doDay(std::vector<lantern_fish>& fishes) {
    int fish_spawned = 0;
    for(auto& fish : fishes) {
        if(fish.timer == 0) {
            fish_spawned++;
            fish.timer = 6;
        }
        else {
            fish.timer--;
        }
    }
    for(unsigned int i = 0; i < fish_spawned; i++)
    {
        fishes.emplace_back(8);
    }
}

int part1() {
    std::vector<lantern_fish> fishes;
    fishes.reserve(300);
    std::fstream file(FILE_PATH);
    std::string line;
    std::getline(file, line);
    std::stringstream in(line);
    int t;
    char comma;
    while(in >> t >> comma) {
        fishes.emplace_back(t);
    }
    fishes.emplace_back(t);
    for(unsigned int i = 0; i < NUMBER_OF_DAYS; i++) {
        std::cout << "Day: " << i << std::endl;
        doDay(fishes);
    }
    return fishes.size();
}

cpp_int part2() {
    cpp_int fish_on_day[9] = {};

    cpp_int total = 0;

    std::fstream file(FILE_PATH);
    std::string line;
    std::getline(file, line);
    std::stringstream in(line);
    int t;
    char comma;
    while(in >> t >> comma) {
        fish_on_day[t]++;
    }
    fish_on_day[t]++;

    for(unsigned int day = 0; day < 256; day++) {
        cpp_int fish_to_spawn = fish_on_day[0];
        for(unsigned int i = 0; i < 8; i++) {
            fish_on_day[i] = fish_on_day[i + 1];
        }
        fish_on_day[6] += fish_to_spawn;
        fish_on_day[8] = fish_to_spawn;
    }
    for(const auto& day : fish_on_day) {
        total += day;
    }

    return total;
}

int main() {
    std::cout << part2() << std::endl;
}