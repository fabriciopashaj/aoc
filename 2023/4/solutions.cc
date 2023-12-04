#include <iostream>
#include <fstream>
#include <sstream>
#include <bitset>
#include <limits>

using namespace std;

int main() {
    // for 3 digit decimal numbers
    constexpr const size_t N_BITS = 100;
    ifstream input("input.txt");
    string line;
    size_t sum = 0;

    line.reserve(128);

    for (size_t i = 0; getline(input, line); ++i) {
        bitset<N_BITS> winning(0);
        istringstream ls(line);
        size_t n_matches = 0;

        ls.ignore(numeric_limits<streamsize>::max(), ':');
        ls.ignore(1); // the space after `:`

        while (ls.peek() != '|') {
            int val;
            ls>>val;
            winning.set(val);
            ls.ignore(1);
        }
        ls.ignore(1);

        while (ls.peek() != EOF) {
            ls.ignore(1);
            int val;
            ls>>val;
            n_matches += (size_t)winning.test(val);
        }

        sum += n_matches == 0 ? 0 : (1 << (n_matches - 1));
    }

    cout<<"Part 1 ["<<sum<<"]"<<endl;
    return 0;
}