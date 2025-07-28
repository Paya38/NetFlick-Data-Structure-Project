#include "FavoriteList.h"

bool FavoriteList::compareByName(const MovieSeries& a, const MovieSeries& b)
{
    return a.movieSeriesName < b.movieSeriesName;
}

void FavoriteList::addMovieSeries(const MovieSeries& movieSeries)
{
    movieSeriesList.push_back(movieSeries);
    sort(movieSeriesList.begin(), movieSeriesList.end(), compareByName);
}

bool FavoriteList::removeMovieSeriesByName(const string& name)
{
    auto it = find_if(movieSeriesList.begin(), movieSeriesList.end(), [&name](const MovieSeries& movieSeries) {
        return movieSeries.movieSeriesName == name;
        });

    if (it != movieSeriesList.end()) {
        movieSeriesList.erase(it);
        return true;
    }
    else {
        cout << "Movie/Series with name '" << name << "' not found.\n";
        return false;
    }
}

void FavoriteList::displayAll() 
{
    if (movieSeriesList.empty()) {
        cout << "The list is empty.\n";
        return;
    }

    cout << "Movie/Series List:\n";
    for ( auto& movieSeries : movieSeriesList) {
        movieSeries.printInfo();
        cout << "-----------------------------\n";
    }
}
