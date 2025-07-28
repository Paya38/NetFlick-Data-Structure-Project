#include "SplayTree.h"

SplayNode::SplayNode(MovieSeries movie):data(movie),left(nullptr),right(nullptr){}

SplayNode* SplayTree::rightRotate(SplayNode* x)
{
	SplayNode* y = x->left;
	x->left = y->right;
	y->right = x;
	return y;
}

SplayNode* SplayTree::leftRotate(SplayNode* x)
{
	SplayNode* y = x->right;
	x->right = y->left;
	y->left = x;
	return y;
}

SplayNode* SplayTree::splay(SplayNode* root, int id)
{
    if (!root || root->data.movieSeriesID == id)
        return root;

    if (id < root->data.movieSeriesID)
    {
        if (!root->left)
            return root;

        if (id < root->left->data.movieSeriesID)
        {
            root->left->left = splay(root->left->left, id);
            root = rightRotate(root);
        }
        else if (id > root->left->data.movieSeriesID)
        {
            root->left->right = splay(root->left->right, id);
            if (root->left->right)
                root->left = leftRotate(root->left);
        }
        return root->left ? rightRotate(root) : root;
    }
    else
    {
        if (!root->right)
            return root;

        if (id > root->right->data.movieSeriesID)
        {
            root->right->right = splay(root->right->right, id);
            root = leftRotate(root);
        }
        else if (id < root->right->data.movieSeriesID)
        {
            root->right->left = splay(root->right->left, id);
            if (root->right->left)
                root->right = rightRotate(root->right);
        }
        return root->right ? leftRotate(root) : root;
    }
}

SplayNode* SplayTree::deleteRoot(SplayNode* root)
{
    if (!root->left)
    {
        SplayNode* temp = root->right;
        delete root;
        return temp;
    }
    else if (!root->right)
    {
        SplayNode* temp = root->left;
        delete root;
        return temp;
    }
    else
    {
        SplayNode* temp = root->right;
        while (temp->left)
            temp = temp->left;

        temp->left = root->left;
        SplayNode* newRoot = root->right;
        delete root;
        return newRoot;
    }
}

void SplayTree::inOrderTravel(SplayNode* node)
{
    if (!node)
        return;
    inOrderTravel(node->left);
    node->data.printInfo();
    inOrderTravel(node->right);
}

SplayTree::SplayTree():root(nullptr){}

void SplayTree::insert(MovieSeries movie)
{
    if (!root)
    {
        root = new SplayNode(movie);
        return;
    }
    root = splay(root, movie.movieSeriesID);
    if (movie.movieSeriesID < root->data.movieSeriesID)
    {
        SplayNode* node = new SplayNode(movie);
        node->right = root;
        node->left = root->left;
        root->left = nullptr;
        root = node;
    }
    else if (movie.movieSeriesID > root->data.movieSeriesID)
    {
        SplayNode* node = new SplayNode(movie);
        node->left = root;
        node->right = root->right;
        root->right = nullptr;
        root = node;
    }
}

MovieSeries* SplayTree::search(int id)
{
    root = splay(root, id);
    if (root && root->data.movieSeriesID == id)
        return &root->data;
    return nullptr;
}

void SplayTree::remove(int id)
{
    if (!root)
        return;

    root = splay(root, id);

    if (root && root->data.movieSeriesID == id)
    {
        root = deleteRoot(root);
        cout << "Movie or series with ID " << id << " has been removed." << endl;
    }
    else
    {
        cout << "Movie or series with ID " << id << " not found." << endl;
    }
}

void SplayTree::showTree()
{
    cout << "All Movies and Series in inordertravel:" << endl;
    inOrderTravel(root);
}

vector<MovieSeries> SplayTree::bfsFirstThreeLevels()
{
    vector<MovieSeries> result;
    if (!root)
        return result;

    queue<pair<SplayNode*, int>> q;
    q.push(make_pair(root, 0)); // Use make_pair instead of structured bindings

    while (!q.empty())
    {
        pair<SplayNode*, int> front = q.front();
        q.pop();

        SplayNode* node = front.first;
        int level = front.second;

        if (level < 3)
            result.push_back(node->data);

        if (node->left)
            q.push(make_pair(node->left, level + 1));
        if (node->right)
            q.push(make_pair(node->right, level + 1));
    }
    RadixSort::radixSortByScore(result);
    return result;
}

string SplayTree::bfsMostFrequentGenreFirstThreeLevels()
{
    if (!root)
        return "No genres available.";

    vector<MovieSeries> movies;
    queue<pair<SplayNode*, int>> q;
    q.push(make_pair(root, 0));

    while (!q.empty())
    {
        pair<SplayNode*, int> front = q.front();
        q.pop();

        SplayNode* node = front.first;
        int level = front.second;

        if (level < 3)
            movies.push_back(node->data);

        if (node->left)
            q.push(make_pair(node->left, level + 1));
        if (node->right)
            q.push(make_pair(node->right, level + 1));
    }

    unordered_map<string, int> genreCount;
    for (const auto& movie : movies)
    {
        genreCount[movie.genre]++;
    }

    string mostFrequentGenre = "";
    int maxCount = 0;
    for (const auto& entry : genreCount)
    {
        if (entry.second > maxCount)
        {
            maxCount = entry.second;
            mostFrequentGenre = entry.first;
        }
    }

    return mostFrequentGenre;
}

vector<MovieSeries> SplayTree::sortMoviesByDistanceFromRoot(const vector<MovieSeries>& movies)
{
    unordered_map<int, int> distances;

    if (!root)
        return {};

    queue<pair<SplayNode*, int>> q;
    q.push(make_pair(root, 0));

    while (!q.empty())
    {
        pair<SplayNode*, int> front = q.front();
        q.pop();

        SplayNode* node = front.first;
        int distance = front.second;

        distances[node->data.movieSeriesID] = distance;

        if (node->left)
            q.push(make_pair(node->left, distance + 1));
        if (node->right)
            q.push(make_pair(node->right, distance + 1));
    }

    vector<MovieSeries> sortedMovies = movies;
    sort(sortedMovies.begin(), sortedMovies.end(), [&distances](const MovieSeries& a, const MovieSeries& b) {
        return distances[a.movieSeriesID] < distances[b.movieSeriesID];
        });

    return sortedMovies;
}



