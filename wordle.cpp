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

    // 1) Count how many of each floating letter we need
    std::array<int,26> need{};
    for (char c : floating)                        // ← LOOP #1
        need[c - 'a']++;

    // 2) Scan each dictionary word once
    for (auto const& w : dict)                    // ← LOOP #2
    {
        if ((int)w.size() != n) continue;

        std::array<int,26> seen{};
        bool ok = true;

        // 3) One pass: 
        //    - reject non-lowercase
        //    - enforce fixed letters
        //    - tally seen counts
        for (int i = 0; i < n; ++i)                // ← LOOP #3
        {
            char wc = w[i];
            if (wc < 'a' || wc > 'z'         // non-lowercase?
             || (in[i] != '-' && in[i] != wc)) // fixed mismatch?
            {
                ok = false;
                break;
            }
            seen[wc - 'a']++;
        }
        if (!ok) continue;

        // 4) Make sure we saw all floating letters
        for (int k = 0; k < 26; ++k)             // ← LOOP #4
            if (seen[k] < need[k]) { ok = false; break; }

        if (ok) results.insert(w);
    }

    return results;
}
