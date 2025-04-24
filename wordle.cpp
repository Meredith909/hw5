#include "wordle.h"
#include "dict-eng.h"
#include <set>
#include <map>
#include <string>

using namespace std;

void generateWords(
    const string& in,
    const map<char, int>& floatCounts,
    const set<string>& dict,
    string& current,
    int pos,
    set<string>& results,
    map<char, int>& currCounts
) {
    if (pos == in.size()) {
        // Check if all floating letters are present
        for (const auto& pair : floatCounts) {
            if (currCounts[pair.first] < pair.second) return;
        }
        if (dict.find(current) != dict.end()) {
            results.insert(current);
        }
        return;
    }

    // Handle fixed characters
    if (in[pos] != '-') {
        char c = in[pos];
        current.push_back(c);
        currCounts[c]++;
        generateWords(in, floatCounts, dict, current, pos + 1, results, currCounts);
        currCounts[c]--;
        current.pop_back();
    } else {
        // Try all possible characters (loop occurs here)
        for (char c = 'a'; c <= 'z'; ++c) {
            current.push_back(c);
            currCounts[c]++;
            generateWords(in, floatCounts, dict, current, pos + 1, results, currCounts);
            currCounts[c]--;
            current.pop_back();
        }
    }
}

set<string> wordle(
    const string& in,
    const string& floating,
    const set<string>& dict
) {
    set<string> results;
    map<char, int> floatCounts;
    for (char c : floating) {
        floatCounts[c]++;
    }

    string current;
    map<char, int> currCounts;
    generateWords(in, floatCounts, dict, current, 0, results, currCounts);
    return results;
}