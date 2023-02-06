#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "Tokenizer.h"

void Tokenizer::setTokens( vector<string> tok ) {
    tokens = tok;
};

vector<string> Tokenizer::getTokens() {
    return this->tokens;
}

string Tokenizer::getNextToken() {
    string next = this->tokens.front();
    tokens.erase(tokens.begin());
    return next;
}

vector<string> Tokenizer::tokenize(const string &str) {

    string next;
    vector<string> result;

    for (string::const_iterator it = str.begin(); it != str.end(); it++) {
        if ((*it == ' ') || (*it == '\t'))  {
            if (!next.empty()) {
                result.push_back(next);
                next.clear();
            }
        } else if (*it == ';') {
            if (!next.empty()) {
                result.push_back(next);
                result.push_back(";");
                next.clear();
            }
        } else {
            next += *it;
        }
    }
    if (!next.empty())
        result.push_back(next);
    return result;
}