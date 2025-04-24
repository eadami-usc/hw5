#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;

// Add prototypes of helper functions here
void wordleHelper(
    std::string& floating,
    const std::set<std::string>& dict,
    std::set<std::string>& words,
    std::string& word,
    unsigned int index
);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict
) {
    std::set<std::string> words;
    std::string word = in;
    std::string floatingCopy = floating;
    wordleHelper(floatingCopy, dict, words, word, 0);
    return words;
}

// Define any helper functions here
void wordleHelper(
    std::string& floating,
    const std::set<std::string>& dict,
    std::set<std::string>& words,
    std::string& word,
    unsigned int index
) {
    // base case
    if (index == word.length()) {
        if (floating.empty() && dict.find(word) != dict.end()) {
            words.insert(word);
        }
        return;
    }

    if (word[index] == '-') {
        for (char c = 'a'; c <= 'z'; c++) {
            word[index] = c;
            size_t pos = floating.find(c);
            if (pos != std::string::npos) {
                floating.erase(pos, 1);
                wordleHelper(floating, dict, words, word, index + 1);
                floating.insert(pos, 1, c);
            } else {
                wordleHelper(floating, dict, words, word, index + 1);
            }
        }
        word[index] = '-';
    } else {
        wordleHelper(floating, dict, words, word, index + 1);
    }
}
