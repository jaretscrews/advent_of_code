#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <utility>
#include <list>

#define FILE_PATH "day_4.txt"

struct bingo_cell {
    int value;
    bool called;
};

struct bingo_board {
    bingo_cell board[5][5] = {};
    bool won = false;
};

void mark(bingo_board* b, int value) {
    for(auto& row : b->board) {
        for(auto& cell : row) {
            if(cell.value == value)
                cell.called = true;
        }
    }
}

bool check_board(bingo_board b) {
    for(auto & i : b.board) {
        if(i[0].called &&
           i[1].called &&
           i[2].called &&
           i[3].called &&
           i[4].called) {
            return true;
        }
    }
    for(unsigned int i = 0; i < 5; i++) {
        if(b.board[0][i].called && b.board[1][i].called && b.board[2][i].called
            && b.board[3][i].called && b.board[4][i].called)
            return true;
    }
    return false;
}

int tally(bingo_board b, int call) {
    int sum = 0;
    for(const auto& row : b.board){
        for(const auto& cell : row) {
            if(!cell.called)
                sum += cell.value;
        }
    }
    return sum * call;
}

int part1() {
    int bingo_score = 0;
    std::vector<int> calls;
    std::vector<bingo_board> boards;
    std::fstream file(FILE_PATH);

    {
        std::string line;
        std::getline(file, line);
        std::stringstream in(line);
        std::string s;
        while (std::getline(in, s, ',')) {
            calls.push_back(std::stoi(s));
        }
    }

    int i = 0;
    bingo_board b;
    while(file) {
        if(i == 5)
        {
            i = 0;
            boards.push_back(b);
        }
        std::string line;
        std::getline(file, line);
        if(line.empty()) continue;
        std::stringstream in(line);

        in >> b.board[i][0].value >> b.board[i][1].value >> b.board[i][2].value
            >> b.board[i][3].value >> b.board[i][4].value;
        i++;
    }

    for(const auto& call : calls) {
        for(auto& board : boards) {
            mark(&board, call);
            if(check_board(board)) {
                bingo_score = tally(board, call);
                return bingo_score;
            }
        }
    }
    return bingo_score;
}

int part2() {
    int bingo_score = 0;
    std::vector<int> calls;
    std::list<bingo_board> boards;
    std::fstream file(FILE_PATH);

    {
        std::string line;
        std::getline(file, line);
        std::stringstream in(line);
        std::string s;
        while (std::getline(in, s, ',')) {
            calls.push_back(std::stoi(s));
        }
    }

    int i = 0;
    bingo_board b;
    while(file) {
        if(i == 5)
        {
            i = 0;
            boards.push_back(b);
        }
        std::string line;
        std::getline(file, line);
        if(line.empty()) continue;
        std::stringstream in(line);

        in >> b.board[i][0].value >> b.board[i][1].value >> b.board[i][2].value
           >> b.board[i][3].value >> b.board[i][4].value;
        i++;
    }

    for(const auto& call : calls) {
        for(auto& board : boards) {
            if(board.won) continue;
            mark(&board, call);
            if(check_board(board)) {
                bingo_score = tally(board, call);
                board.won = true;
            }
        }
    }
    return bingo_score;
}

int main() {
    std::cout << part2() << std::endl;
}