#include <fstream>
#include <iostream>
#include <list>
#include <bitset>

#define FILE_PATH "day_3.txt"

int part1() {
    std::fstream file(FILE_PATH);
    int ones[12] = {};
    std::string line;
    while(file >> line) {
        for(unsigned int i = 0; i < 12; i++) {
            ones[i] += int(line[i] - '0');
        }
    }

    int gamma = 0;
    int epsilon = 0;

    for(unsigned int i = 0; i < 12; i++) {
        int x = ones[i];
        int bitPower = static_cast<int>(pow(2, 11 - i));
        x >= 500 ? gamma += bitPower : epsilon += bitPower;
    }
    return gamma * epsilon;
}

struct check {
    unsigned int pos;
    bool operator() (const std::bitset<12>& value) const {
        return value[pos];
    }
};
struct check_not {
    unsigned int pos;
    bool operator() (const std::bitset<12>& value) const {
        return !value[pos];
    }
};

int part2() {
    const int bits = 12;
    std::fstream file(FILE_PATH);
    std::list<std::bitset<bits>> oxy_diagnostics;
    std::list<std::bitset<bits>> co2_diagnostics;
    std::string line;
    while (file >> line){
        oxy_diagnostics.emplace_back(std::bitset<bits>(line));
        co2_diagnostics.emplace_back(std::bitset<bits>(line));
    }

    for(unsigned int i = bits - 1; i >= 0; i--) {
        if(oxy_diagnostics.size() == 1) break;
        int ones = 0;
        for(const auto& x : oxy_diagnostics){
            ones += x[i];
        }
        float half = static_cast<float>(oxy_diagnostics.size()) / 2.0f;
        if(static_cast<float>(ones) >= half){
            check_not p{};
            p.pos = i;
            oxy_diagnostics.remove_if(p);
        }
        else {
            check p{};
            p.pos = i;
            oxy_diagnostics.remove_if(p);
        }
    }

    for(unsigned int i = bits - 1; i >= 0; i--) {
        if(co2_diagnostics.size() == 1) break;
        int ones = 0;
        for(const auto& x : co2_diagnostics){
            ones += x[i];
        }
        float half = static_cast<float>(co2_diagnostics.size()) / 2.0f;
        if(static_cast<float>(ones) < half){
            check_not p{};
            p.pos = i;
            co2_diagnostics.remove_if(p);
        }
        else {
            check p{};
            p.pos = i;
            co2_diagnostics.remove_if(p);
        }
    }
    int oxy = static_cast<int>(oxy_diagnostics.front().to_ulong());
    int co2 = static_cast<int>(co2_diagnostics.front().to_ulong());
    std::cout << oxy << " " << co2 << std::endl;
    return oxy * co2;
}

int main()
{
    std::cout << part2() << std::endl;
}