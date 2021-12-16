#include <iostream>
#include <fstream>
#include <limits>

int main(){
    std::ifstream infile("input.txt");
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

    std::cout << res << std::endl;
}
