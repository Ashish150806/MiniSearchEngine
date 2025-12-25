#include "../include/tokenizer.h"
#include <fstream>
#include <sstream>
#include <cctype>

using namespace std;

void Tokenizer::loadStopwords(const string& filepath) {
    ifstream file(filepath);
    string word;
    while (file >> word) {
        stopwords.insert(word);
    }
}

string Tokenizer::cleanToken(string token) {
    string clean;
    for (char c : token) {
        if (isalnum(c)) {
            clean += tolower(c);
        }
    }
    return clean;
}

vector<string> Tokenizer::tokenize(const string& text) {
    vector<string> tokens;
    stringstream ss(text);
    string word;

    while (ss >> word) {
        string cleaned = cleanToken(word);
        if (!cleaned.empty() && stopwords.count(cleaned) == 0) {
            tokens.push_back(cleaned);
        }
    }
    return tokens;
}
