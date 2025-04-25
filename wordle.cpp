#include "wordle.h"

using namespace std;

void generate(string& current, size_t pos, const string& floating, unsigned used_floats, 
              int floats_left, int open_count, const set<string>& dict, set<string>& result) {
    if (floats_left > open_count) return;

    if (pos == current.size()) {
        if (floats_left == 0 && dict.count(current)) {
            result.insert(current);
        }
        return;
    }

    if (current[pos] != '-') {
        generate(current, pos + 1, floating, used_floats, floats_left, open_count, dict, result);
        return;
    }

    for (char c = 'a'; c <= 'z'; c++) {
        current[pos] = c;
        bool used_float = false;
        
        for (size_t i = 0; i < floating.size(); i++) {
            if (!(used_floats & (1 << i)) && floating[i] == c) {
                generate(current, pos + 1, floating, used_floats | (1 << i), 
                        floats_left - 1, open_count - 1, dict, result);
                used_float = true;
                break;
            }
        }
        
        if (!used_float) {
            generate(current, pos + 1, floating, used_floats, floats_left, open_count - 1, dict, result);
        }
    }
    current[pos] = '-';
}

set<string> wordle(const string& in, const string& floating, const set<string>& dict) {
    set<string> result;
    string current = in;
    int open_count = 0;
    unsigned used_floats = 0;
    int floats_left = floating.size();

    for (size_t i = 0; i < in.size(); i++) {
        if (in[i] == '-') {
            open_count++;
        } 
    }

    generate(current, 0, floating, used_floats, floats_left, open_count, dict, result);
    return result;
}