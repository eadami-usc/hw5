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
    unsigned int index,
    unsigned int remainingDashes
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
    
    int initialDashes = 0;
    for (char c : in) {
        if (c == '-') {
            initialDashes++;
        }
    }
    
    wordleHelper(floatingCopy, dict, words, word, 0, initialDashes);
    return words;
}

// Define any helper functions here
void wordleHelper(
    std::string& floating,
    const std::set<std::string>& dict,
    std::set<std::string>& words,
    std::string& word,
    unsigned int index,
    unsigned int remainingDashes
) {
    if (remainingDashes < floating.length()) {
        return;
    }
    
    // base case
    if (index == word.length()) {
        if (floating.empty() && dict.find(word) != dict.end()) {
            words.insert(word);
        }
        return;
    }

    if (word[index] == '-') {
        remainingDashes--;
        for (char c = 'a'; c <= 'z'; c++) {
            word[index] = c;
            size_t pos = floating.find(c);
            if (pos != std::string::npos) {
                floating.erase(pos, 1);
                wordleHelper(floating, dict, words, word, index + 1, remainingDashes);
                floating.insert(pos, 1, c);
            } else {
                wordleHelper(floating, dict, words, word, index + 1, remainingDashes);
            }
        }
        word[index] = '-';
    } else {
        wordleHelper(floating, dict, words, word, index + 1, remainingDashes);
    }
}
