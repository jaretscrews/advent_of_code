#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>


#define FILE_PATH "day_8.txt"

struct compare {
    inline bool operator()(const std::string& first,
                           const std::string& second) const
    {
        return first.size() < second.size();
    }
};

void print_segments(const std::string& light) {
    bool segments[7] = {};
    for (const auto &c: light) {
        segments[c - 'a'] = true;
    }
    std::string line;
    segments[0] ? line = " aaaa " : line = " .... ";
    std::cout << line << std::endl;
    segments[1] ? line = "b    " : line = ".    ";
    segments[2] ? line += "c" : line += ".";
    std::cout << line << std::endl;
    std::cout << line << std::endl;
    segments[3] ? line = " dddd " : line = " .... ";
    std::cout << line << std::endl;
    segments[4] ? line = "e    " : line = ".    ";
    segments[5] ? line += "f" : line += ".";
    std::cout << line << std::endl;
    std::cout << line << std::endl;
    segments[6] ? line = " gggg " : line = " .... ";
    std::cout << line << std::endl << std::endl;
}

bool one_four_seven_or_eight(std::string& decoded) {
    std::sort(decoded.begin(), decoded.end());
    if(decoded == "cf" || decoded == "bcdf" || decoded == "acf" || decoded == "abcdefg") {
        return true;
    }
    return false;
}

int decoded_value(std::string& decoded) {
    std::sort(decoded.begin(), decoded.end());
    int value = 0;
    if(decoded == "abcefg") {
        value = 0;
    }
    else if(decoded == "cf") {
        value = 1;
    }
    else if(decoded == "acdeg") {
        value = 2;
    }
    else if(decoded == "acdfg") {
        value = 3;
    }
    else if(decoded == "bcdf") {
        value = 4;
    }
    else if(decoded == "abdfg") {
        value = 5;
    }
    else if(decoded == "abdefg") {
        value = 6;
    }
    else if(decoded == "acf") {
        value = 7;
    }
    else if(decoded == "abcdefg") {
        value = 8;
    }
    else if(decoded == "abcdfg") {
        value = 9;
    }
    else {
        std::cout << "couldn't find " << decoded << std::endl;
        throw std::runtime_error("we fucked up");
    }
    return value;
}

int part1() {
    std::fstream file(FILE_PATH);

    int result = 0;
    while(file) {
        std::vector<std::string> signal_information;
        std::vector<std::string> to_be_decoded;
        std::map<char, int> occurs;
        std::map<char, char> crossed;
        std::string l;
        std::getline(file, l);
        if(!file) break;
        std::stringstream in(l);
        std::string code;
        while (in >> code) {
            if (code == "|") break;
            signal_information.push_back(code);
        }
        while (in >> code) {
            to_be_decoded.push_back(code);
        }

        for (const auto &signal: signal_information) {
            for (const auto &seg: signal) {
                occurs[seg]++;
            }
        }

        for (auto const&[key, val]: occurs) {
            switch (val) {
                case 4:
                    crossed[key] = 'e';
                    break;
                case 6:
                    crossed[key] = 'b';
                    break;
                case 9:
                    crossed[key] = 'f';
                    break;
            }
        }


        compare c;
        std::sort(signal_information.begin(), signal_information.end(), c);

        auto one = signal_information[0];
        if (crossed.contains(one[0])) {
            auto x = crossed[one[0]];
            x == 'f' ? crossed[one[1]] = 'c' : crossed[one[1]] = 'f';
        } else {
            auto x = crossed[one[1]];
            x == 'f' ? crossed[one[0]] = 'c' : crossed[one[0]] = 'f';
        }

        for (auto const&[key, val]: occurs) {
            if (val == 8 && !crossed.contains(key))
                crossed[key] = 'a';
        }

        auto four = signal_information[2];
        for (const auto &c: four)
            if (!crossed.contains(c)) crossed[c] = 'd';

        for (char i = 'a'; i <= 'g'; i++)
            if (!crossed.contains(i)) crossed[i] = 'g';

        if(crossed.size() != 7) {
            std::cout << "Something went wrong" << std::endl;
            for (auto const&[key, val]: crossed) {
                std::cout << key        // string (key)
                          << " -> "
                          << val        // string's value
                          << std::endl;
            }
            throw std::runtime_error("we fucked up");

        }
//        for (auto const&[key, val]: crossed) {
//            std::cout << key        // string (key)
//                      << " -> "
//                      << val        // string's value
//                      << std::endl;
//        }

        for (const auto &decode_me: to_be_decoded) {
            std::string decoded;
            for (const auto &i: decode_me) {
                decoded += crossed[i];
//                print_segments(decoded);
            }
            if (one_four_seven_or_eight(decoded)) {
                result++;
            }
        }
    }
    return result;
}

int part2() {
    std::fstream file(FILE_PATH);

    int result = 0;
    while(file) {
        std::vector<std::string> signal_information;
        std::vector<std::string> to_be_decoded;
        std::map<char, int> occurs;
        std::map<char, char> crossed;
        std::string l;
        std::getline(file, l);
        if(!file) break;
        std::stringstream in(l);
        std::string code;
        while (in >> code) {
            if (code == "|") break;
            signal_information.push_back(code);
        }
        while (in >> code) {
            to_be_decoded.push_back(code);
        }

        for (const auto &signal: signal_information) {
            for (const auto &seg: signal) {
                occurs[seg]++;
            }
        }

        for (auto const&[key, val]: occurs) {
            switch (val) {
                case 4:
                    crossed[key] = 'e';
                    break;
                case 6:
                    crossed[key] = 'b';
                    break;
                case 9:
                    crossed[key] = 'f';
                    break;
            }
        }


        compare c;
        std::sort(signal_information.begin(), signal_information.end(), c);

        auto one = signal_information[0];
        if (crossed.contains(one[0])) {
            auto x = crossed[one[0]];
            x == 'f' ? crossed[one[1]] = 'c' : crossed[one[1]] = 'f';
        } else {
            auto x = crossed[one[1]];
            x == 'f' ? crossed[one[0]] = 'c' : crossed[one[0]] = 'f';
        }

        for (auto const&[key, val]: occurs) {
            if (val == 8 && !crossed.contains(key))
                crossed[key] = 'a';
        }

        auto four = signal_information[2];
        for (const auto &c: four)
            if (!crossed.contains(c)) crossed[c] = 'd';

        for (char i = 'a'; i <= 'g'; i++)
            if (!crossed.contains(i)) crossed[i] = 'g';

        if(crossed.size() != 7) {
            std::cout << "Something went wrong" << std::endl;
            for (auto const&[key, val]: crossed) {
                std::cout << key        // string (key)
                          << " -> "
                          << val        // string's value
                          << std::endl;
            }
            throw std::runtime_error("we fucked up");

        }
//        for (auto const&[key, val]: crossed) {
//            std::cout << key        // string (key)
//                      << " -> "
//                      << val        // string's value
//                      << std::endl;
//        }
        int value = 0;
        for (const auto &decode_me: to_be_decoded) {
            value *= 10;
            std::string decoded;
            for (const auto &i: decode_me) {
                decoded += crossed[i];
//                print_segments(decoded);
            }
            value += decoded_value(decoded);
        }
        result += value;
    }
    return result;
}

int main() {
    std::cout << part2() << std::endl;
}