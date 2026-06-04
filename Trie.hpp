#ifndef TRIE_HPP
#define TRIE_HPP

#include "Game.hpp"
#include <string>
#include <vector>

class TrieNode {

public:

    static const int ALPHABET_SIZE = 36;

    TrieNode* children[ALPHABET_SIZE];
    bool isEndOfTitle;
    Game* game;

    TrieNode();
    ~TrieNode();
};



class Trie {

private:

    TrieNode* root;

public:

    Trie();
    ~Trie();

    bool insert(Game* game);
    bool contains(std::string title);

    std::vector<Game*> autocomplete(std::string prefix, int k);

    std::string toSearchKey(std::string text);
    void sortResults(std::vector<Game*>& games);

    // Outros métodos auxiliares, se necessário
    int getCaracterIndex(char c);
    void collectGames(TrieNode* node, std::vector<Game*>& results);
};

#endif