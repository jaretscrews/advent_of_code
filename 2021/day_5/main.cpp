#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include <list>

#define FILE_PATH "day_5.txt"

struct line {
    std::pair<int,int> start;
    std::pair<int,int> end;
    line(int x1, int y1, int x2, int y2) : start({x1,y1}), end({x2,y2}) {}
};

int part1() {
    std::fstream file(FILE_PATH);
    int intersections = 0;
    std::list<line> lines;
    int grid[1000][1000] = {};
    while(file) {
        std::string l;
        std::getline(file, l);
        if(l == "") continue;
        std::stringstream in(l);
        char temp;
        int x1, y1, x2, y2;
        in >> x1;
        in >> temp;
        in >> y1;
        in >> temp;
        in >> temp;
        in >> x2;
        in >> temp;
        in >> y2;
        if(x1 == x2 || y1 == y2) {
            lines.emplace_back(x1, y1, x2, y2);
        }
    }


    //draw lines
    for(const auto& l : lines) {
        if(l.start.first == l.end.first) {
            int start = std::min(l.start.second, l.end.second);
            int end = std::max(l.start.second, l.end.second);
            for(unsigned int i = start; i <= end; i++) {
                grid[i][l.start.first]++;
                if(grid[i][l.start.first] == 2) intersections++;
            }
        }
        else {
            int start = std::min(l.start.first, l.end.first);
            int end = std::max(l.start.first, l.end.first);
            for(unsigned int i = start; i <= end; i++) {
                grid[l.start.second][i]++;
                if(grid[l.start.second][i] == 2) intersections++;
            }
        }
    }

    return intersections;
}

int part2() {
    std::fstream file(FILE_PATH);
    int intersections = 0;
    std::list<line> lines;
    int grid[1000][1000] = {};
    while(file) {
        std::string l;
        std::getline(file, l);
        if(l == "") continue;
        std::stringstream in(l);
        char temp;
        int x1, y1, x2, y2;
        in >> x1;
        in >> temp;
        in >> y1;
        in >> temp;
        in >> temp;
        in >> x2;
        in >> temp;
        in >> y2;

        lines.emplace_back(x1, y1, x2, y2);
    }


    //draw lines
    for(const auto& l : lines) {
        //vertical
        if(l.start.first == l.end.first) {
            int start = std::min(l.start.second, l.end.second);
            int end = std::max(l.start.second, l.end.second);
            for(unsigned int i = start; i <= end; i++) {
                grid[l.start.first][i]++;
                if(grid[l.start.first][i] == 2) intersections++;
            }
        }
        //horizontal
        else if(l.start.second == l.end.second){
            int start = std::min(l.start.first, l.end.first);
            int end = std::max(l.start.first, l.end.first);
            for(unsigned int i = start; i <= end; i++) {
                grid[i][l.start.second]++;
                if(grid[i][l.start.second] == 2) intersections++;
            }
        }
        //45
        else {
            int startX = l.start.first;
            int startY = l.start.second;
            int endX = l.end.first;
            int endY = l.end.second;
            int deltaX = startX < endX ? 1 : -1;
            int deltaY = startY < endY ? 1 : -1;
            while(startX != endX) {
                grid[startX][startY]++;
                if(grid[startX][startY] == 2) intersections++;
                startX += deltaX;
                startY += deltaY;
            }
            grid[startX][startY]++;
            if(grid[startX][startY] == 2) intersections++;
        }
    }
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j<10; j++){
            std::cout << grid[j][i];
        }
        std::cout << std::endl;
    }
    return intersections;
}


int main() {
    std::cout << part2() << std::endl;
}