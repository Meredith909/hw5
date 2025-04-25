#include "wordle.h"
#include <set>
#include <string>

// Ensure the candidate contains only lowercase letters
bool isAllLowercase(const std::string& word) {
    for(char c : word) {
        if(c < 'a' || c > 'z') return false;
    }
    return true;
}

bool isValidCandidate(const std::string& pattern, std::string floatLetters, const std::string& candidate) {
    for(size_t i = 0; i < pattern.size(); ++i) {
        if(pattern[i] != '-' && candidate[i] != pattern[i]) {
            return false;
        }
        if(pattern[i] == '-') {
            auto it = floatLetters.find(candidate[i]);
            if(it != std::string::npos) {
                floatLetters.erase(it, 1);
            }
        }
    }
    return floatLetters.empty();
}

std::set<std::string> wordle(
    const std::string& pattern,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    std::set<std::string> results;

    int numDashes = 0;
    for(char c : pattern) {
        if(c == '-') numDashes++;
    }

    if(floating.size() > numDashes) {
        return results;
    }

    for(const std::string& word : dict) {
        if(word.length() != pattern.length()) continue;
        if(!isAllLowercase(word)) continue;

        std::string floatCopy = floating;
        if(isValidCandidate(pattern, floatCopy, word)) {
            results.insert(word);
        }
    }

    return results;
}
