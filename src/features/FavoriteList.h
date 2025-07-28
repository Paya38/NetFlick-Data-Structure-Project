#pragma once
#include "MovieSeries.h"
#include <algorithm>
class FavoriteList
{
private:
    vector<MovieSeries> movieSeriesList;
    static bool compareByName(const MovieSeries& a, const MovieSeries& b);
public:
    void addMovieSeries(const MovieSeries& movieSeries);
    bool removeMovieSeriesByName(const string& name);
    void displayAll() ;
};

