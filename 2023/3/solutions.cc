#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct NumInfo {
    size_t val;
    int col;
    size_t len;
};

struct LineInfo {
    string raw;
    vector<NumInfo> numbers;
};

int at(string const& str, int i) {
    if (i < 0 || i >= (int)str.size()) {
        return EOF;
    }
    return str[i];
}

#define issymbol(c) ((c) != '.' && !isalnum(c) && !isspace(c))

bool anySymbolsInRange_(string const& str, int start, size_t len) {
    int low = max(0, start);
    len = min(len, str.size());
    for (size_t i = low; i < start + len; ++i) {
        if (issymbol(at(str, i))) {
            return true;
        }
    }
    return false;
}

bool anySymbolsInRange(string const& str, int start, size_t len) {
    bool yes = anySymbolsInRange_(str, start, len);
    return yes;
}

int main() {
    ifstream input("input.txt");
    size_t sum = 0;
    vector<LineInfo> lines;
    lines.push_back(LineInfo { "", {} });
    while (input.peek() != EOF) {
        string raw;
        vector<NumInfo> numbers;
        raw.reserve(16);
        getline(input, raw);
        for (size_t i = 0; i < raw.size(); ++i) {
            if (isdigit(raw[i])) {
                size_t val = 0;
                int col = i;
                for (; i < raw.size() && isdigit(raw[i]); ++i) {
                    val = val * 10 + raw[i] - '0';
                }
                NumInfo number = { val, col, i - col };
                numbers.push_back(number);
            }
        }
        LineInfo line_info = { raw, numbers };
        lines.push_back(line_info);
    }
    lines[0].raw.resize(lines[1].raw.size());
    fill(lines[0].raw.begin(), lines[0].raw.end(), ' ');
    lines.push_back(lines[0]);
    for (auto it = lines.cbegin() + 1; it != lines.cend() - 1; ++it) {
        for (NumInfo info : it->numbers) {
            if (
                anySymbolsInRange((it - 1)->raw, info.col - 1, info.len + 2) ||
                anySymbolsInRange(it->raw, info.col - 1, info.len + 2) ||
                anySymbolsInRange((it + 1)->raw, info.col - 1, info.len + 2)
            ) {
                sum += info.val;
            }
        }
    }
    cout<<"Part 1 ["<<sum<<"]"<<endl;
    return 0;
}