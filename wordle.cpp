#include "wordle.h"
#include "dict-eng.h"
#include <set>
#include <array>
#include <string>

std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    std::set<std::string> results;
    int n = in.size();

    // count how many of each floating letter we still need
    std::array<int,26> need{};
    for (char c : floating) {
        if (c >= 'a' && c <= 'z')
            need[c - 'a']++;
    }

    // scan every word in the dictionary exactly once
    for (auto const& w : dict) {
        if ((int)w.size() != n) continue;

        // 0) skip anything with non-lowercase letters
        bool allLower = true;
        for (char c : w) {
            if (c < 'a' || c > 'z') { allLower = false; break; }
        }
        if (!allLower) continue;

        std::array<int,26> seen{};
        bool ok = true;

        // 1) check fixed positions and tally up letters
        for (int i = 0; i < n; ++i) {
            char wc = w[i];
            if (in[i] != '-' && in[i] != wc) {
                ok = false;
                break;
            }
            seen[wc - 'a']++;
        }
        if (!ok) continue;

        // 2) ensure we've seen each floating letter enough times
        for (int k = 0; k < 26; ++k) {
            if (seen[k] < need[k]) {
                ok = false;
                break;
            }
        }
        if (ok) results.insert(w);
    }

    return results;
}
