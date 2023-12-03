#include <iostream>
#include <fstream>
#include <sstream>
#include <climits>

using namespace std;

int part1(istream& input) {
#define MAX_R 12
#define MAX_G 13
#define MAX_B 14

    string line;
    line.reserve(128);
    int sum = 0;

    while (getline(input, line)) {
        int n = 0;
        int r = 0;
        int g = 0;
        int b = 0;
        stringstream ls(line);

        ls.ignore(sizeof("Game ") - 1);
        ls>>n;
        while (ls.peek() != EOF) {
            ls.ignore(2);
            int val;
            ls>>val;
            ls.ignore(1);

            switch (ls.peek()) {
                case 'r':
                    r = max(r, val);
                    ls.ignore(3);
                    break;
                case 'g':
                    g = max(g, val);
                    ls.ignore(5);
                    break;
                case 'b':
                    b = max(b, val);
                    ls.ignore(4);
                    break;
                default:
                    throw runtime_error("invalid input");
            }
        }
        if (r <= MAX_R && g <= MAX_G && b <= MAX_B) {
            sum += n;
        }
    }
    return sum;
}

int part2(istream& input) {
    string line;
    line.reserve(128);
    int sum = 0;
    while (getline(input, line)) {
        int n = 0;
        int r = 0;
        int g = 0;
        int b = 0;
        stringstream ls(line);
        ls.ignore(sizeof("Game ") - 1);
        ls>>n;
        while (ls.peek() != EOF) {
            ls.ignore(2);
            int val;
            ls>>val;
            ls.ignore(1);
            switch (ls.peek()) {
                case 'r':
                    r = max(r, val);
                    ls.ignore(3);
                    break;
                case 'g':
                    g = max(g, val);
                    ls.ignore(5);
                    break;
                case 'b':
                    b = max(b, val);
                    ls.ignore(4);
                    break;
                default:
                    throw runtime_error("invalid input");
            }
        }
        sum += r * g * b;
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