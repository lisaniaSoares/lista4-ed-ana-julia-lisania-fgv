#include <iostream>
#include "Trie.hpp"
#include "Game.hpp"
#include "GamesDatabase.hpp"
using namespace std;

int main(int argc, char* argv[]){
 
    // 1. Verificar se os argumentos foram informados corretamente
    if(argc != 3){
        cout << "Usage: ./app k prefix" << endl;
        return 1;
    }

    // 2. Converter o argumento k para inteiro
    int k = atoi(argv[1]);
    string prefix = argv[2];

    // 3. Criar uma Trie
    Trie trie;

    // 4. Inserir todos os jogos da lista inicial na Trie
    for(int i = 0; i < numberOfGames; i++){
        trie.insert(&games[i]);
    }

    // 5. Chamar o método autocomplete
    vector<Game*> results = trie.autocomplete(prefix, k);
 
    // 6. Exibir os jogos retornados
    if(results.size() == 0){
        cout << "No results found" << endl;
        return 0;
    }
 
    for(int i = 0; i < results.size(); i++){
        cout << results[i]->getTitle() << " | " 
             << results[i]->getShortDescription() << " | " 
             << results[i]->getPopularity() << endl;
    }
 
    return 0;
}