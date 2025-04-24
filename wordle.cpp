#include "wordle.h"
#include "dict-eng.h"
#include <set>
#include <map>
#include <string>

using namespace std;

void generateCandidates(set<string>& results, const string& in, const map<char, int>& float_counts, const set<string>& dict, string current, int pos) {
    if (pos == in.size()) {
        map<char, int> current_counts;
        for (char c : current) { // Count characters in the current candidate
            current_counts[c]++;
        }
        bool valid = true;
        for (const auto& pair : float_counts) { // Check against required floating counts
            if (current_counts[pair.first] < pair.second) {
                valid = false;
                break;
            }
        }
        if (valid && dict.find(current) != dict.end()) {
            results.insert(current);
        }
        return;
    }
    
    if (in[pos] != '-') { // Fixed character position
        current.push_back(in[pos]);
        generateCandidates(results, in, float_counts, dict, current, pos + 1);
        current.pop_back();
    } else { // Try all possible characters for non-fixed position
        for (char c = 'a'; c <= 'z'; ++c) {
            current.push_back(c);
            generateCandidates(results, in, float_counts, dict, current, pos + 1);
            current.pop_back();
        }
    }
}

set<string> wordle(
    const string& in,
    const string& floating,
    const set<string>& dict)
{
    set<string> results;
    map<char, int> float_counts;
    for (char c : floating) { // Build the floating character count map
        float_counts[c]++;
    }
    
    generateCandidates(results, in, float_counts, dict, "", 0);
    
    return results;
}