#ifndef HASHCLASS_H
#define HASHCLASS_H

#include <vector>
#include <string>
#include <functional>
#include "MovieSeries.h"
using namespace std;

template <typename K, typename V>
class HashNode {
public:
    K Key;
    vector<V> val;
    HashNode* next;
    HashNode(K k, V v) :Key(k), next(nullptr) {
                val.push_back(v);
            }
};

template <typename K, typename V>
class HashTable {
private:
        HashNode<K, V>** table;
        int capacity;
        int size;
        int hash_fun(K k) {
            return static_cast<int>(hash<K>()(k) % capacity);
        }
    public:
        HashTable(int cap = 10) :capacity(cap), size(0) {
            table = new HashNode<K, V>* [capacity];
            for (int i = 0; i < capacity; i++)
            {
                table[i] = nullptr;
            }
        }
        ~HashTable() {
            for (int i = 0; i < capacity; i++)
            {
                HashNode<K, V>* temp = table[i];
                while (temp)
                {
                    HashNode<K, V>* flag = temp; temp = temp->next;
                    delete temp;
                }
            }
            delete[] table;
        }
        void insert(K k, V& v) {
            int i = hash_fun(k);
            if (!table[i])
            {
                table[i] = new HashNode<K, V>(k, v);
            }
            else {
                HashNode<K, V>* temp = table[i];
                while (temp)
                {
                    if (temp->Key==k)
                    {
                        temp->val.push_back(v); return;
                    }
                    if (!temp->next) break;
                    temp = temp->next;
               
                }
                temp->next = new HashNode<K, V>(k, v);
            }
            size++;
        }
        vector<V> search(K k) {
            int i = hash_fun(k);
            HashNode<K, V>* temp = table[i];
            while (temp)
            {
                if (temp->Key==k)
                {
                    return temp->val;
                }
                temp = temp->next;
            }
            return{};
        }
        void remove(const K& key, const V& movie) {
            int index = hash_fun(key); 
            HashNode<K, V>* temp = table[index];
            HashNode<K, V>* prev = nullptr;

            while (temp) {
                if (temp->Key == key) { 
                    auto& movies = temp->val;
                    for (auto it = movies.begin(); it != movies.end(); ++it) {
                        if (it->movieSeriesName == movie.movieSeriesName) { 
                            movies.erase(it);
                            //cout << "Movie \"" << movie.movieSeriesName << "\" removed from \"" << key << "\"." << endl;
                            if (movies.empty()) {
                                if (prev) {
                                    prev->next = temp->next;
                                }
                                else {
                                    table[index] = temp->next;
                                }
                                delete temp;
                            }
                            return;
                        }
                    }
                    cout << "Movie \"" << movie.movieSeriesName << "\" not found under key \"" << key << "\"." << endl;
                    return;
                }
                prev = temp;
                temp = temp->next;
            }

            cout << "Key \"" << key << "\" not found." << endl;
        }


        vector<V> searchGreaterOrEqual(const K&key) {
            vector<V> results;
    
            int startKey = stoi(key);
    
            for (int currentKey = startKey; currentKey <= 10; ++currentKey) {
                string currentKeyStr = to_string(currentKey); 
                int index = hash_fun(currentKeyStr);
                HashNode<K, V>* current = table[index];
    
                while (current) {
                    if (current->Key == currentKeyStr) {
                        results.insert(results.end(), current->val.begin(), current->val.end());
                    }
                    current = current->next;
                }
            }
    
            return results;
        }
        MovieSeries* searchByname(const string& name) {
            //vector<V> result;
            for (int i = 0; i < capacity; i++)
            {
                HashNode<K, V>* node = table[i];
                while (node)
                {
                    for (auto& m : node->val) {
                        if (m.movieSeriesName == name)
                        {
                            //result.push_back(m);
                            return &m;
                        }
                    }
                    node = node->next;
                }
            }
            return nullptr;
        }

    
};


//template <typename K, typename V>
//void HashTable<K, V>::insert(K k, V v);
//
//template <typename K, typename V>
//std::vector<V> HashTable<K, V>::search(K k);
//
//template <typename K, typename V>
//std::vector<V> HashTable<K, V>::searchGreaterOrEqual(const K& key);
#endif
