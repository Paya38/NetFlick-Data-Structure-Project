#pragma once
#include "MovieSeries.h"
class RadixSort
{
public:
	static void radixSortByScore(vector<MovieSeries>& movies);
private:
	static float getMaxScore( vector<MovieSeries>& movies);
	static void countingSort(vector<MovieSeries>& movies, int exp);
};

class SortByYear {
public:
	static void radixSortByYear(vector<MovieSeries>& movies);

private:
	static int getMaxYear(const vector<MovieSeries>& movies);
	static void countingSort(vector<MovieSeries>& movies, int exp);
};

