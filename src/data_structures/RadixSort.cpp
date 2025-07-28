
#include "RadixSort.h"

void RadixSort::radixSortByScore(vector<MovieSeries>& movies)
{
    const int BASE = 10;
    int maxScore = static_cast<int>(getMaxScore(movies) * 100);

    for (int exp = 1; maxScore / exp > 0; exp *= BASE) {
        countingSort(movies, exp);
    }
}

float RadixSort::getMaxScore( vector<MovieSeries>& movies)
{
    float maxScore = 0;
    for ( auto& movie : movies) {
        if (movie.getScore() > maxScore) {
            maxScore = movie.getScore();
        }
    }
    return maxScore;
}

void RadixSort::countingSort(vector<MovieSeries>& movies, int exp)
{
    vector<MovieSeries> output(movies.size());
    int count[10] = { 0 };

    for ( auto& movie : movies) {
        int digit = static_cast<int>(movie.getScore() * 100) / exp % 10;
        count[digit]++;
    }

    for (int i = 8; i >= 0; i--) {
        count[i] += count[i + 1];
    }

    for (int i = movies.size() - 1; i >= 0; i--) {
        int digit = static_cast<int>(movies[i].getScore() * 100) / exp % 10;
        output[count[digit] - 1] = movies[i];
        count[digit]--;
    }

    movies = output;
}


void SortByYear::radixSortByYear(vector<MovieSeries>& movies) {
    const int BASE = 10;
    int maxYear = getMaxYear(movies);

    for (int exp = 1; maxYear / exp > 0; exp *= BASE) {
        countingSort(movies, exp);
    }
}

int SortByYear::getMaxYear(const vector<MovieSeries>& movies) {
    int maxYear = 0;
    for (const auto& movie : movies) {
        if (movie.year > maxYear) {
            maxYear = movie.year;
        }
    }
    return maxYear;
}

void SortByYear::countingSort(vector<MovieSeries>& movies, int exp) {
    vector<MovieSeries> output(movies.size());
    int count[10] = { 0 };


    for (const auto& movie : movies) {
        int digit = (movie.year / exp) % 10;
        count[digit]++;
    }

    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }


    for (int i = movies.size() - 1; i >= 0; i--) {
        int digit = (movies[i].year / exp) % 10;
        output[count[digit] - 1] = movies[i];
        count[digit]--;
    }
    movies = output;
}
