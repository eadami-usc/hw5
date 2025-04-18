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
    const std::string& floating,
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
    wordleHelper(floating, dict, words, word, 0);
    return words;
}

// Define any helper functions here
void wordleHelper(
    const std::string& floating,
    const std::set<std::string>& dict,
    std::set<std::string>& words,
    std::string& word,
    unsigned int index
) {
    if (index == word.length()) {
        for (char f : floating) {
            int count = 0;
            for (char c : word) {
                if (c == f) {
                    count++;
                }
            }
            int floatingCount = 0;
            for (char f2 : floating) {
                if (f2 == f) {
                    floatingCount++;
                }
            }
            if (count < floatingCount) {
                return;
            }
        }
        if (dict.find(word) != dict.end()) {
            words.insert(word);
        }
        return;
    }

    if (word[index] == '-') {
        for (char c = 'a'; c <= 'z'; c++) {
            word[index] = c;
            wordleHelper(floating, dict, words, word, index + 1);
        }
        word[index] = '-';
    } else {
        wordleHelper(floating, dict, words, word, index + 1);
    }
}
