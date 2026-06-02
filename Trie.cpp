#include "Trie.hpp"

TrieNode::TrieNode(){

    for (int i = 0; i < ALPHABET_SIZE; i++){
        children[i] = nullptr;
    }

    this -> isEndOfTitle = false;
    this -> game = nullptr;
}

TrieNode::~TrieNode(){
    for (int i = 0; i < ALPHABET_SIZE; i++){
        if(children[i] != nullptr){
            delete children[i];
        }
    }
}

Trie::Trie(){
    this -> root = new TrieNode();
}

Trie::~Trie(){
    if(root != nullptr){
        delete this -> root;
    }
}


std::string Trie::toSearchKey(std::string text){

    std::string text_converted = "";
    for(int i = 0; i < text.length(); i++){

        if(text[i] != ' '){ // Se o caracter não for vazio (um espaço)
            char c = text[i];
            
            if(c >= 'A' && c <= 'Z'){ // Se a letra for maiúscula
                c += 32; 
                // transformamos em sua correspondente minúscula
            }

            text_converted += c;
        }
    }

    return text_converted;
}


bool Trie::insert(Game* game){
    
    if(game == nullptr){
        return false;
    }

    std::string search_key = toSearchKey(game->getTitle());

    try {
        // Começamos a percorrer pela raiz
        TrieNode* current_node = root;

        // Para cada caracter do titulo
        for (int i = 0; i < search_key.length(); i ++){
            char c = search_key[i];

            // Vemos se a sua posição com base na tabela ASCI está vazia
            if(current_node -> children[c - 'a'] == nullptr){
                current_node -> children[c - 'a'] = new TrieNode();
            }

            current_node = current_node -> children[c - 'a'];
        }

        // Após incluir todo o título
        current_node -> isEndOfTitle = true;
        current_node -> game = game;

        return true; 

    } catch (...) {
        // Caso algo dê errado na inserção
        return false;
    }
    
}

bool Trie::contains(std::string title){

    std::string search_key = toSearchKey(title);
    TrieNode* current = root;

    // for (int i = 0; i < search_key.length(); i++){
    //     char c = search_key[i];

    //     if(search_key[i] != current -> children[c - 'a']){

    //     }
    // }
}