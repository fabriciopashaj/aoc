#include <algorithm>
#include <array>
#include <bitset>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <queue>
#include <sstream>
#include <vector>

using namespace std;

// for 3 digit decimal numbers
constexpr const size_t N_BITS = 100;

size_t part1(istream& input) {
    string line;
    size_t sum = 0;

    line.reserve(256);

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

    return sum;
}

size_t part2(istream& input) {
    vector<size_t> match_counts;
    vector<size_t> n_instances;
    string line;
    line.reserve(256);
    match_counts.reserve(128);
    n_instances.reserve(128);

    while (getline(input, line)) {
        bitset<N_BITS> winning(0);
        istringstream ls(line);

        ls.ignore(numeric_limits<streamsize>::max(), ':');
        ls.ignore(1);

        while (ls.peek() != '|') {
            size_t val;
            ls>>val;
            winning.set(val);
            ls.ignore(1);
        }
        ls.ignore(1);

        size_t n_matches = 0;
        while (ls.peek() != EOF) {
            size_t val;
            ls>>val;
            if (winning.test(val)) {
            }
            n_matches += (size_t)winning.test(val);
            ls.ignore(1);
        }

        match_counts.push_back(n_matches);
    }

    n_instances.resize(match_counts.size());
    fill(n_instances.begin(), n_instances.end(), 1);

    for (size_t i = 0; i < n_instances.size(); ++i) {
        for (size_t j = i + 1; j <= i + match_counts[i]; ++j) {
            n_instances[j] += n_instances[i];
        }
    }

    size_t result = 0;

    for (size_t i = 0; i < n_instances.size(); ++i) {
        result += n_instances[i];
    }

    return result;
}

int main() {
    ifstream input("input.txt");
    cout<<"Part 1 ["<<part1(input)<<"]"<<endl;
    input.clear();
    input.seekg(0);
    cout<<"Part 2 ["<<part2(input)<<"]"<<endl;
    input.close();
    return 0;
}