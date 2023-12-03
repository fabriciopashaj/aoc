#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <iterator>

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

#define issymbol(c) ((c) != EOF && (c) != '.' && !isalnum(c) && !isspace(c))

bool anySymbolsInRange(string const& str, int start, size_t len) {
    int low = max(0, start);
    len = min(len, str.size());
    for (size_t i = low; i < start + len; ++i) {
        if (issymbol(at(str, i))) {
            return true;
        }
    }
    return false;
}

int part1(istream& input) {
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
                issymbol(at(it->raw, info.col - 1)) ||
                issymbol(at(it->raw, info.col + info.len)) ||
                anySymbolsInRange((it + 1)->raw, info.col - 1, info.len + 2)
            ) {
                sum += info.val;
            }
        }
    }
    return sum;
}

size_t parseUintAround(string const& str, size_t offset) {
    size_t val = 0;
    for (; isdigit(at(str, offset - 1)); --offset) {}
    for (; isdigit(at(str, offset)); ++offset) {
        val = val * 10 + str[offset] - '0';
    }
    return val;
}

size_t parseUintBackward(string const& str, size_t offset) {
    size_t val = 0;
    for (int i = (int)offset, j = 1; isdigit(at(str, i)); --i, j *= 10) {
        val += (str[i] - '0') * j;
    }
    return val;
}

size_t parseUintForward(string const& str, size_t offset) {
    size_t val = 0;
    for (; isdigit(at(str, offset)); ++offset) {
        val = val * 10 + str[offset] - '0';
    }
    return val;
}

size_t adjacentsProduct(
    vector<string> const& lines,
    size_t line_num,
    size_t col
) {
    string const& prev_line = lines[line_num - 1];
    string const& curr_line = lines[line_num];
    string const& next_line = lines[line_num + 1];
    size_t nums[6] = {0};
    size_t n_nums = 0;

    if (isdigit(at(curr_line, col - 1))) {
        nums[n_nums] = parseUintBackward(curr_line, col - 1);
        ++n_nums;
    }

    if (isdigit(at(curr_line, col + 1))) {
        nums[n_nums] = parseUintForward(curr_line, col + 1);
        ++n_nums;
    }

    if (isdigit(at(prev_line, col))) {
        nums[n_nums] = parseUintAround(prev_line, col);
        ++n_nums;
    } else {
        if (isdigit(at(prev_line, col - 1))) {
            nums[n_nums] = parseUintBackward(prev_line, col - 1);
            ++n_nums;
        }
        if (isdigit(at(prev_line, col + 1))) {
            nums[n_nums] = parseUintForward(prev_line, col + 1);
            ++n_nums;
        }
    }

    if (isdigit(at(next_line, col))) {
        nums[n_nums] = parseUintAround(next_line, col);
        ++n_nums;
    } else {
        if (isdigit(at(next_line, col - 1))) {
            nums[n_nums] = parseUintBackward(next_line, col - 1);
            ++n_nums;
        }
        if (isdigit(at(next_line, col + 1))) {
            nums[n_nums] = parseUintForward(next_line, col + 1);
            ++n_nums;
        }
    }

    return n_nums == 2 ? nums[0] * nums[1] : 0;
}

int part2(istream& input) {
    size_t sum = 0;
    vector<string> lines;
    vector<pair<size_t, size_t>> positions;
    lines.push_back("");
    size_t line_num = 1;

    while (input.peek() != EOF) {
        string raw;
        raw.reserve(256);
        getline(input, raw);
        for (size_t col = 0; col < raw.size(); ++col) {
            if (raw[col] == '*') {
                positions.push_back(make_pair(line_num, col));
            }
        }
        lines.push_back(raw);
        ++line_num;
    }
    lines[0].resize(lines[1].size());
    fill(lines[0].begin(), lines[0].end(), ' ');
    lines.push_back(lines[0]);

    for (auto pos : positions) {
        size_t line_num = pos.first;
        size_t col = pos.second;
        size_t prod = adjacentsProduct(lines, line_num, col);
        sum += prod;
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