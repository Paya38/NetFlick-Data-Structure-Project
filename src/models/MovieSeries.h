#pragma once
#include <iostream>
#include <vector>
using namespace std;
class MovieSeries
{
private:
	static int id;
public:
	int movieSeriesID;
	bool isMovie;
	string movieSeriesName;
	//string seriesName;
	int year;
	int minTime;
	string country;
	string genre;
	string language;
	vector<float> score;
	string summary;
	int seasons;
	int episodes;
	MovieSeries(string name, int y, int time, string _country, string _genre, string _language, float _score, string _summary);
	MovieSeries(string name, int y, int time, string _country, string _genre, string _language, float _score, string _summary,int _seasons,int _episodes);
	MovieSeries();
	float getScore()const;
	void printInfo();
	MovieSeries(const MovieSeries& other);
};

