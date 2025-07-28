#include "CompressedTrie.h"

CompressedTrie::CompressedTrie(const string& prefix, bool is_leaf)
    : prefix(prefix), is_leaf(is_leaf) {}

tuple<string, string, string> CompressedTrie::match(const string& word) {
    size_t x = 0;
    for (size_t i = 0; i < prefix.size() && i < word.size(); ++i) {
        if (prefix[i] != word[i]) break;
        x++;
    }
    return { prefix.substr(0, x), prefix.substr(x), word.substr(x) };
}

void CompressedTrie::inserts(const vector<string>& words) {
    for (const auto& word : words) {
        insert(word);
    }
}

void CompressedTrie::insert(const string& word) {
    if (prefix == word && !is_leaf) {
        is_leaf = true;
        return;
    }

    if (nodes.find(word[0]) == nodes.end()) {
        nodes[word[0]] = new CompressedTrie(word, true);
        return;
    }

    CompressedTrie* incoming_node = nodes[word[0]];
    tuple<string, string, string> result = incoming_node->match(word);
    string matching_string = std::get<0>(result);
    string remaining_prefix = std::get<1>(result);
    string remaining_word = std::get<2>(result);

    if (remaining_prefix.empty()) {
        incoming_node->insert(remaining_word);
    }
    else {
        incoming_node->prefix = remaining_prefix;

        CompressedTrie* aux_node = nodes[matching_string[0]];
        nodes[matching_string[0]] = new CompressedTrie(matching_string, false);
        nodes[matching_string[0]]->nodes[remaining_prefix[0]] = aux_node;

        if (remaining_word.empty()) {
            nodes[matching_string[0]]->is_leaf = true;
        }
        else {
            nodes[matching_string[0]]->insert(remaining_word);
        }
    }
}

bool CompressedTrie::find(const string& word) {
    auto it = nodes.find(word[0]);
    if (it == nodes.end()) return false;

    tuple<string, string, string> result = it->second->match(word);
    string matching_string = get<0>(result);
    string remaining_prefix = get<1>(result);
    string remaining_word = get<2>(result);

    if (!remaining_prefix.empty())
        return false;

    if (remaining_word.empty())
        return it->second->is_leaf;

    return it->second->find(remaining_word);
}

void CompressedTrie::similar_res(const string& word, vector<string>& result) {
    CompressedTrie* node = this;
    string prefix_match = "";
    int curIndex = 0;
    int prefixInd = 0;
    while (curIndex < word.length()) {
        for (int i = 0; i < node->prefix.length() && curIndex < word.length(); i++) {
            if (node->prefix[i] != word[curIndex]) {
                cout << "No matching words found for ' " << prefix_match << " '" << endl;
                return;
            }
            prefix_match += word[curIndex];
            curIndex++;
            prefixInd = i;
        }
        if (curIndex >= word.length())
            break;
        if (curIndex < word.length() && node->nodes.find(word[curIndex]) != node->nodes.end())
            node = node->nodes[word[curIndex]];
        else if (node->nodes.find(word[curIndex]) == node->nodes.end())
            return;
    }
    print_all(node, prefix_match, prefixInd + 1, result);
}

void CompressedTrie::print_all(CompressedTrie* node, const string& prefix, int prefixInd, vector<string>& result) {
    string word = prefix;
    if (node->is_leaf) {
        // word += prefix;
        for (int i = prefixInd; i < node->prefix.length(); i++) {
            word += node->prefix[i];
        }
        result.push_back(word);
    }

    for (const auto& pair : node->nodes) {
        print_all(pair.second, word + pair.second->prefix, pair.second->prefix.length(), result);
    }
}
