#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int part1(istream& input) {
    string line;
    line.reserve(32);
    int sum = 0;
    while (getline(input, line)) {
        int first = -1;
        int last = -1;
        for (
            int i = 0, j = line.size() - 1;
            first == -1 || last == -1;
            ++i, --j
        ) {
            if (first == -1 && isdigit(line[i])) {
                first = line[i] - '0';
            }
            if (last == -1 && isdigit(line[j])) {
                last = line[j] - '0';
            }
        }
        if (first == -1) {
            continue;
        }
        int val = first * 10 + last;
        sum += val;
    }
    return sum;
}

int digitFromName(string& str, int offset) {
    if (str.compare(offset, 3, "one") == 0) {
        return 1;
    }
    if (str.compare(offset, 3, "two") == 0) {
        return 2;
    }
    if (str.compare(offset, 5, "three") == 0) {
        return 3;
    }
    if (str.compare(offset, 4, "four") == 0) {
        return 4;
    }
    if (str.compare(offset, 4, "five") == 0) {
        return 5;
    }
    if (str.compare(offset, 3, "six") == 0) {
        return 6;
    }
    if (str.compare(offset, 5, "seven") == 0) {
        return 7;
    }
    if (str.compare(offset, 5, "eight") == 0) {
        return 8;
    }
    if (str.compare(offset, 4, "nine") == 0) {
        return 9;
    }
    return -1;
}

int part2(istream& input) {
    string line;
    line.reserve(32);
    int sum = 0;
    while (getline(input, line)) {
        int first = digitFromName(line, 0);
        int last = -1;
        for (
            int i = 0, j = line.size() - 1;
            first == -1 || last == -1;
            ++i, --j
        ) {
            if (first == -1) {
                first =
                    isdigit(line[i])
                    ? line[i] - '0'
                    : digitFromName(line, i + 1);
            }
            if (last == -1) {
                if (j + i < (int)line.size()) {
                    last = digitFromName(line, j);
                }
                if (last == -1 && isdigit(line[j])) {
                    last = line[j] - '0';
                }
            }
        }
        int val = first * 10 + last;
        sum += val;
    }
    return sum;
}

int main() {
    ifstream input("input.txt");
    cout<<"Part 1 ["<<part1(input)<<"]"<<endl;
    input.clear();
    input.seekg(0);
    cout<<"Part 2 ["<<part2(input)<<"]"<<endl;
    return 0;
}