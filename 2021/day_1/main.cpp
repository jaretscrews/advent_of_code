#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <string>

#define FILE_PATH "day_1.txt"


int part1() {
    std::ifstream infile(FILE_PATH);
    int curr = std::numeric_limits<int>::max();
    int prev = 0;
    int res = 0;
    while (infile)  
    {
        prev = curr;
        infile >> curr;

        if (prev < curr)
            res++;
    }

    return res;
}

int part2() {
    std::ifstream infile(FILE_PATH);
    std::vector<int> sums;
    int x, y, z;
    infile >> x >> y >> z;
    int res = 0;
    while (infile)  
    {
        int sum = x + y + z;
        sums.push_back(sum);
        sum -= x;
        x = y;
        y = z;
        infile >> z;
    }

    for(unsigned int i = 0; i < sums.size(); i++)
    {
        if (sums[i] < sums[i + 1])
            res++;
    }
    
    return res;
}


int main() {
    std::cout << part1() << std::endl;
    std::cout << part2() << std::endl;
}
