#include "wordle.h"


using namespace std;

void generate(string& current, size_t pos, string float_copy, int open_count, const set<string>& dict, set<string>& result) {
    if (float_copy.size() > open_count) {
        return;
    }

    if (pos == current.size()) {
        if (float_copy.empty() && dict.count(current)) {
            result.insert(current);
        }
        return;
    }

    if (current[pos] != '-') {
        generate(current, pos + 1, float_copy, open_count, dict, result);
        return;
    }

    for (char c = 'a'; c <= 'z'; c++) {
        current[pos] = c;
        size_t found = float_copy.find(c);
        if (found != string::npos) {
            string new_float = float_copy;
            new_float.erase(found, 1);
            generate(current, pos + 1, new_float, open_count - 1, dict, result);
        } else {
            generate(current, pos + 1, float_copy, open_count - 1, dict, result);
        }
    }
    current[pos] = '-';
}

set<string> wordle(const string& in, const string& floating, const set<string>& dict) {
    set<string> result;
    string current = in;
    string float_copy = floating;
    int open_count = 0;

    for (size_t i = 0; i < in.size(); i++) {
        if (in[i] == '-') {
            open_count++;
        } 
    }

    generate(current, 0, float_copy, open_count, dict, result);
    return result;
}