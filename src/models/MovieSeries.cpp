#include "MovieSeries.h"
int MovieSeries::id = 0;
MovieSeries::MovieSeries(string name, int y, int time, string _country, string _genre, string _language, float _score, string _summary)
{
	isMovie = true;
	movieSeriesID = ++id;
	movieSeriesName = name;
	year = y;
	minTime = time;
	country = _country;
	genre = _genre;
	language = _language;
	score.push_back(_score);
	summary = _summary;
	seasons = -1;
	episodes = -1;
}

MovieSeries::MovieSeries(string name, int y, int time, string _country, string _genre, string _language, float _score, string _summary, int _seasons, int _episodes)
{
	isMovie = false;
	movieSeriesID = ++id;
	movieSeriesName = name;
	year = y;
	minTime = time;
	country = _country;
	genre = _genre;
	language = _language;
	score.push_back(_score);
	summary = _summary;
	seasons = _seasons;
	episodes = _episodes;
}

MovieSeries::MovieSeries()
{
	movieSeriesID = -1;
	movieSeriesName = "";
	year = -1;
	minTime = -1;
	country = "";
	genre = "";
	language = "";
	//score = -1.0;
	summary = "";
	seasons = -1;
	episodes = -1;
}

float MovieSeries::getScore()const
{
	float sum = 0;
	for (int i = 0; i < score.size(); i++) {
		sum += score[i];
	}
	return (float)sum/score.size();
}

void MovieSeries::printInfo()
{
	if (isMovie)
		cout << "Movie Information:" << endl;
	else
	cout << "Series Information:" << endl;
	cout << "Name:" << movieSeriesName << endl;
	cout << "Year:" << year << endl;
	cout << "Time:" << minTime <<" Min"<< endl;
	cout << "Country:" << country << endl;
	cout << "Genre:" << genre << endl;
	cout << "Language:" << language << endl;
	cout << "Score:" << getScore() << endl;
	cout << "Summary:" << summary << endl;
	if (!isMovie)
		cout << "Seasons:" << seasons << endl << "Episodes:" << episodes << endl;
}

MovieSeries::MovieSeries(const MovieSeries& other)
{
	isMovie = other.isMovie;
	movieSeriesID = other.movieSeriesID;
	movieSeriesName = other.movieSeriesName;
	year = other.year;
	minTime = other.minTime;
	country = other.country;
	genre = other.genre;
	language = other.language;
	summary = other.summary;
	seasons = other.seasons;
	episodes = other.episodes;
	score = other.score;
}
