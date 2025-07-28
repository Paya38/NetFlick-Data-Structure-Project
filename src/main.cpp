#include "HashClass.h"
#include "SplayTree.h"
#include "FavoriteList.h"
#include "UserManagement.h"
#include "CompressedTrie.h"
#include <unordered_map>
vector<MovieSeries> filterByYear(const vector<MovieSeries>& movies, int minYear, int maxYear) {
	vector<MovieSeries> filteredMovies;

	for (const auto& movie : movies) {
		if ((minYear == -1 || movie.year >= minYear) && (maxYear == -1 || movie.year <= maxYear)) {
			filteredMovies.push_back(movie);
		}
	}
	return filteredMovies;
}

vector<MovieSeries> filterByCountry(const vector<MovieSeries>& movies, const string& country) {
	vector<MovieSeries> filteredMovies;

	for (const auto& movie : movies) {
		if (country.empty() || movie.country == country) {
			filteredMovies.push_back(movie);
		}
	}
	return filteredMovies;
}

vector<MovieSeries> filterByLanguage(const vector<MovieSeries>& movies, const string& language) {
	vector<MovieSeries> filteredMovies;

	for (const auto& movie : movies) {
		if (language.empty() || movie.language == language) {
			filteredMovies.push_back(movie);
		}
	}
	return filteredMovies;
}

vector<MovieSeries> filterBygenre(const vector<MovieSeries>& movies, const string& genre) {
	vector<MovieSeries> filteredMovies;

	for (const auto& movie : movies) {
		if (genre.empty() || movie.genre == genre) {
			filteredMovies.push_back(movie);
		}
	}
	return filteredMovies;
}

vector<MovieSeries> filterByScore(const vector<MovieSeries>& movies, float minScore) {
	vector<MovieSeries> filteredMovies;

	for (const auto& movie : movies) {
		if (movie.getScore() >= minScore) {
			filteredMovies.push_back(movie);
		}
	}
	return filteredMovies;
}
//levenshtein algorithm
int levenshtein_distance(const string& st1, const string& st2) {
	int st1_len = st1.size();
	int st2_len = st2.size();
	vector<vector<int>> matris(st1_len + 1, vector<int>(st2_len + 1));
	for (int i = 0; i <= st1_len; i++)
	{
		matris[i][0] = i;
	}for (int j = 0; j <= st2_len; j++)
	{
		matris[0][j] = j;

	}
	for (int i = 1; i <= st1_len; i++)
	{
		for (int j = 1; j <= st2_len; j++)
		{
			if (st1[i - 1] == st2[j - 1])
			{
				matris[i][j] = matris[i - 1][j - 1];
			}
			else
				matris[i][j] = min({ matris[i][j - 1] + 1,matris[i - 1][j] + 1,matris[i - 1][j - 1] + 1 });
		}
	}
	return matris[st1_len][st2_len];
}
vector<string> findword(const string& porpose, const vector<string>words) {
	vector<string> result;
	for (const auto& item : words)
	{
		if (levenshtein_distance(porpose, item) <= 3)
		{
			result.push_back(item);

		}
	}
	return result;
}

int main() {
	SplayTree sTree;
	CompressedTrie trie;
	vector<string> movieSeriesName;
	HashTable<string, MovieSeries> genreTable(100);
	HashTable<string, MovieSeries> countryTable(100);
	HashTable<string, MovieSeries> languageTable(100);
	HashTable<string, MovieSeries> yearTable(100);
	HashTable<string, MovieSeries> scoreTable(100);
	UserManagement users;
	unordered_map<string, FavoriteList>  usersFavoriteList;
	int status=0;
	while(status!=3) {
		cout << "1.Log In" << endl << "2.Sign Up" << endl << "3.Exit" << endl << "What do you want to do:";
		cin >> status;
		if (status == 2) {
			string username, password;
			cout << "Type Username:";
			cin >> username;
			cout << "Type Password:";
			cin >> password;
			if (users.addUser(username, password)) {
				FavoriteList list;
				usersFavoriteList[username] = list;
			}
		}
		else if (status == 1) {
			string username, password;
			cout << "Username:";
			cin >> username;
			cout << "Password:";
			cin >> password;
			if (users.getPassword(username) != password&&users.getPassword(username)!="%")
				cout << "Password is incorrect" << endl;
			else if (username == "admin" && password == "admin") {
				cout << "ADMIN:" << endl;
				int s=0;
				while (s != 4) {
					cout << "1.Add Movie" << endl << "2.Add Series" << endl << "3.Delete Movie or Series" << endl<<"4.Exit"<<endl<<"Type Num :";
					cin >> s;
					if (s == 1) {
						string name, country, genre, language, summary;
						int  year, minTime;
						float score;
						std::cin.ignore(1, '\n');
						cout << "Name:";
						getline(cin, name);
						cout << "Year:";
						cin >> year;
						cout << "Time:";
						cin >> minTime;
						cout << "Country:";
						cin >> country;
						cout << "Genre:";
						cin >> genre;
						cout << "Lnaguage:";
						cin >> language;
						cout << "Score:";
						cin >> score;
						cout << "Summary:";
						std::cin.ignore(1, '\n');
						getline(cin, summary);
						MovieSeries film(name, year, minTime, country, genre, language, score, summary);
						sTree.insert(film);
						trie.insert(name);
						movieSeriesName.push_back(name);
						genreTable.insert(film.genre, film);
						countryTable.insert(film.country, film);
						languageTable.insert(film.language, film);
						yearTable.insert(to_string(film.year), film);
						scoreTable.insert(to_string(static_cast<int>(film.getScore())), film);
						cout << "Movie Created successfully" << endl;
					}
					else if (s == 2) {
						string name, country, genre, language, summary;
						int  year, minTime,episodes,seasons;
						float score;
						cout << "Name:";
						std::cin.ignore(1, '\n');
						getline(cin, name);
						cout << "Year:";
						cin >> year;
						cout << "Time:";
						cin >> minTime;
						cout << "Country:";
						cin >> country;
						cout << "Genre:";
						cin >> genre;
						cout << "Lnaguage:";
						cin >> language;
						cout << "Score:";
						cin >> score;
						cout << "Episodes:";
						cin >> episodes;
						cout << "Seasons:";
						cin >> seasons;
						cout << "Summary:";
						std::cin.ignore(1, '\n');
						getline(cin, summary);
						MovieSeries film(name, year, minTime, country, genre, language, score, summary,seasons,episodes);
						sTree.insert(film);
						trie.insert(name);
						movieSeriesName.push_back(name);
						genreTable.insert(film.genre, film);
						countryTable.insert(film.country, film);
						languageTable.insert(film.language, film);
						yearTable.insert(to_string(film.year), film);
						scoreTable.insert(to_string(static_cast<int>(film.getScore())), film);
						cout << "Series Created successfully" << endl;
					}
					else if (s == 3) {
						cout << "Type name of movie or series that you want to delete:";
						string searchStr;
						std::cin.ignore(1, '\n');
						getline(cin, searchStr);
						vector <string> names;
						vector <MovieSeries> finded;
						trie.similar_res(searchStr, names);
						for (int i = 0; i < names.size(); i++) {
						    MovieSeries*f = genreTable.searchByname(names[i]);
							if (f)
								finded.push_back(*f);
						}
						if (finded.empty()) {
							cout << "Movie or Series Not Found" << endl;
						}
						else {
							SortByYear::radixSortByYear(finded);
							for (int i = 0; i < finded.size(); i++)
							{
								cout << "Name:" << finded[i].movieSeriesName << endl;
								cout << "Year:" << finded[i].year << endl;
							}
							cout << "Select one and type its name:";
							//std::cin.ignore(1, '\n');
							getline(cin, searchStr);
							for (int i = 0; i < finded.size(); i++) {
								if (searchStr == finded[i].movieSeriesName) {
									auto it = std::find(movieSeriesName.begin(), movieSeriesName.end(), finded[i].movieSeriesName);
									movieSeriesName.erase(it);
									sTree.remove(finded[i].movieSeriesID);
									genreTable.remove(finded[i].genre, finded[i]);
									countryTable.remove(finded[i].country, finded[i]);
									languageTable.remove(finded[i].language, finded[i]);
									yearTable.remove(to_string(finded[i].year), finded[i]);
									scoreTable.remove(to_string(static_cast<int>(finded[i].getScore())), finded[i]);
									cout << "Movie '" << finded[i].movieSeriesName << "' deleted successfully" << endl;
								}
							}
						}
					}
				}
			}
			else if (users.getPassword(username) == password) {
				cout << "USER:" << username << endl;
				int s = 0;
				while (s != 9) {
					cout << "1.All information of movies and series" << endl << "2.Search" << endl << "3.Filtering" << endl << "4.Advanced Search" << endl
						<< "5.Add Movie or Series to FavoriteList" << endl << "6.Manage FavoriteList" << endl << "7.Suggestions" << endl
						<< "8.Scoring to Movie Or Series" << endl<<"9.Exit"<<endl<<"Type Num:";
					cin >> s;
					if (s == 1) {
						sTree.showTree();
					}
					else if (s == 2) {
						cout << "Type the name of Movie or Series:";
						string searchStr;
						cin.ignore(1, '\n');
						getline(cin, searchStr);
						vector<string> answers;
						trie.similar_res(searchStr, answers);
						for (int i = 0; i < answers.size(); i++) {
							MovieSeries* movie = genreTable.searchByname(answers[i]);
							if (movie) {
								sTree.search(movie->movieSeriesID);
								movie->printInfo();
							}
						}
					}
					else if (s == 3) {
						int filter = 0;
						bool isFirst = true;
						bool isScore = false;
						vector<MovieSeries> result;
						while (filter != 6) {
							cout << "What filter do you want to apply?" << endl << "1.Genre" << endl << "2.Score" << endl << "3.Year" << endl
								<< "4.Country" << endl << "5.Language" <<endl<< "6.Apply filters" << endl << "Type num:";
							cin >> filter;
							string k;
							if (filter == 1) {
								cout << "Type Genre:";
								cin >> k;
								if (isFirst) {
									result = genreTable.search(k);
									isFirst = false;
								}
								else {
									result = filterBygenre(result, k);
								}
							}
							else if (filter == 2) {
								isScore = true;
								cout << "Type Score:";
								cin >> k;
								if (isFirst) {
									result = scoreTable.searchGreaterOrEqual(k);
									isFirst = false;
								}
								else {
									result = filterByScore(result,stof( k));
								}
							}
							else if (filter == 3) {
								cout << "Type Year:";
								cin >> k;
								if (isFirst) {
									result = yearTable.search(k);
									isFirst = false;
								}
								else {
									result = filterByYear(result, stoi(k),stoi(k));
								}
							}
							else if (filter == 4) {
								cout << "Type Country";
								cin >> k;
								if (isFirst) {
									result = countryTable.search(k);
									isFirst = false;
								}
								else {
									result = filterByCountry(result, k);
								}
							}
							else if (filter == 5) {
								cout << "Type Language:";
								cin >> k;
								if (isFirst) {
									result = languageTable.search(k);
									isFirst = false;
								}
								else {
									result = filterByLanguage(result, k);
								}
							}

						}
						if (isScore)
							RadixSort::radixSortByScore(result);
						for (int i = 0; i < result.size(); i++) {
							result[i].printInfo();
						}
					}
					else if (s == 4) {
						string movieName;
						cout << "Type the Movie or Series name:";
						cin.ignore(1, '\n');
						getline(cin, movieName);
						vector<string> names;
						names = findword(movieName, movieSeriesName);
						vector <MovieSeries> answers;
						for (int i = 0; i < names.size(); i++) {
							MovieSeries* movie = genreTable.searchByname(names[i]);
							if (movie) {
								answers.push_back(*movie);
							}
						}
						answers = sTree.sortMoviesByDistanceFromRoot(answers);
						cout << "Movie or Series Based on distance from root:" << endl;
						for (int i = 0; i < answers.size(); i++) {
							answers[i].printInfo();
						}
					}
					else if (s == 5) {
						cout << "Type the Movie or Series name to add to your FavoriteList:";
						cin.ignore(1, '\n');
						string name;
						getline(cin, name);
						MovieSeries* movie= genreTable.searchByname(name);
						if (movie) {
							usersFavoriteList[username].addMovieSeries(*movie);
							cout << "Movie/Series added successfully to FvaoriteList" << endl;
						}
					}
					else if (s == 6) {
						string name;
						cout << "Dispaly of FavoriteList:" << endl;
						usersFavoriteList[username].displayAll();
						cout << "Type Movie or Series name To Delete or type 0 to Exit:";
						cin.ignore(1, '\n');
						getline(cin, name);
						if (name != "0") {
							if (usersFavoriteList[username].removeMovieSeriesByName(name))
								cout << "Deleted Successfully" << endl;
						}
					}
					else if (s == 7) {
						string genre = sTree.bfsMostFrequentGenreFirstThreeLevels();
						cout << "Movies and series in genre '" << genre << "' that searched more than others:" << endl;
						vector<MovieSeries> movies = genreTable.search(genre);
						for (int i = 0; i < movies.size(); i++) {
							movies[i].printInfo();
						}
					}
					else if (s == 8) {
						string name;
						cout << "Type the name of Movie or Series that you want to Score:";
						cin.ignore(1, '\n');
						getline(cin, name);
						MovieSeries* movie = genreTable.searchByname(name);
						if (movie) {
							float s;
							cout << "Scoring Movie or Series:";
							cin >> s;
							MovieSeries* sMovie = sTree.search(movie->movieSeriesID);
							sMovie->score.push_back(s);
							MovieSeries* movie1= yearTable.searchByname(name);
							MovieSeries* movie2 = countryTable.searchByname(name);
							MovieSeries* movie3 = scoreTable.searchByname(name);
							MovieSeries* movie4 = languageTable.searchByname(name);
							movie->score.push_back(s);
							movie1->score.push_back(s);
							movie2->score.push_back(s);
							movie3->score.push_back(s);
							movie4->score.push_back(s);
						}
					}
				}
			}
		}
		
	}
}