#pragma once
//#include "MovieSeries.h"
#include "RadixSort.h"
#include <unordered_map>
#include <queue>
struct SplayNode
{
    MovieSeries data;
    SplayNode* left, * right;
    SplayNode(MovieSeries movie);
};
class SplayTree
{
private:
    SplayNode* root;

    SplayNode* rightRotate(SplayNode* x);
    SplayNode* leftRotate(SplayNode* x);
    SplayNode* splay(SplayNode* root, int id);
    SplayNode* deleteRoot(SplayNode* root);
    void inOrderTravel(SplayNode* node);
public:
    SplayTree();
    void insert(MovieSeries movie);
    MovieSeries* search(int id);
    void remove(int id);
    void showTree();
    vector<MovieSeries> bfsFirstThreeLevels();
    string bfsMostFrequentGenreFirstThreeLevels();
    vector<MovieSeries> sortMoviesByDistanceFromRoot(const vector<MovieSeries>& movies);
};

