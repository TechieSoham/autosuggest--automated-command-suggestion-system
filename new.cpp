#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>
#include <algorithm>
#include <cctype> // For tolower function

using namespace std;

class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord;

    TrieNode() : isEndOfWord(false) {}
};

class Trie {
public:
    TrieNode* root;

    Trie() {
        root = new TrieNode();
    }

    // Convert string to lowercase
    string toLowerCase(const string& str) {
        string result = str;
        transform(result.begin(), result.end(), result.begin(), 
                  [](unsigned char c) { return tolower(c); });
        return result;
    }

    void insert(const string& word) {
        // Convert to lowercase before inserting
        string lowercaseWord = toLowerCase(word);
        TrieNode* node = root;
        for (char c : lowercaseWord) {
            if (!node->children[c]) {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
        }
        node->isEndOfWord = true;
    }

    void search(TrieNode* node, const string& prefix, vector<string>& suggestions, 
                const vector<pair<string, string>>& originalCommands) {
        if (node->isEndOfWord) {
            // Find the original command (with original case) that matches this lowercase prefix
            auto it = find_if(originalCommands.begin(), originalCommands.end(), 
                [this, &prefix](const pair<string, string>& cmd) {
                    return toLowerCase(cmd.first) == prefix;
                });
            if (it != originalCommands.end()) {
                suggestions.push_back(it->first); // Use original case
            } else {
                suggestions.push_back(prefix); // Fallback to lowercase
            }
        }
        for (auto it : node->children) {
            search(it.second, prefix + it.first, suggestions, originalCommands);
        }
    }

    vector<string> getSuggestions(const string& prefix, const vector<pair<string, string>>& originalCommands) {
        // Convert to lowercase for searching
        string lowercasePrefix = toLowerCase(prefix);
        TrieNode* node = root;
        vector<string> suggestions;
        for (char c : lowercasePrefix) {
            if (!node->children[c]) {
                return suggestions;
            }
            node = node->children[c];
        }
        search(node, lowercasePrefix, suggestions, originalCommands);
        return suggestions;
    }
};

vector<pair<string, string>> loadCommands(const string& filename) {
    ifstream file(filename);
    vector<pair<string, string>> commands;
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string command, description;
        if (getline(iss, command, ':') && getline(iss, description)) {
            commands.emplace_back(command, description);
        }
    }
    return commands;
}

int main() {
    vector<pair<string, string>> commands = loadCommands("commands.txt");

    Trie trie;

    for (const auto& cmd : commands) {
        trie.insert(cmd.first);
    }

    string input;
    cout << "Enter command prefix: ";
    getline(cin, input);

    vector<string> suggestions = trie.getSuggestions(input, commands);

    if (!suggestions.empty()) {
        cout << "Did you mean:\n";
        for (const auto& suggestion : suggestions) {
            auto it = find_if(commands.begin(), commands.end(), [&suggestion](const pair<string, string>& cmd) {
                return cmd.first == suggestion;
            });
            if (it != commands.end()) {
                cout << "  - " << suggestion << " : " << it->second << '\n';
            }
        }
    } else {
        cout << "No suggestions found.\n";
    }

    return 0;
}