#pragma once
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

class CompressedTrie {
public:
    unordered_map<char, CompressedTrie*> nodes;
    string prefix;
    bool is_leaf;

    CompressedTrie(const string& prefix = "", bool is_leaf = false);

    tuple<string, string, string> match(const string& word);

    void inserts(const vector<string>& words);
    void insert(const string& word);
    bool find(const string& word);

    void similar_res(const string& word, vector<string>& result);
    void print_all(CompressedTrie* node, const string& prefix, int prefixInd, vector<string>& result);
};

