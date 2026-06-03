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


int Trie::getCaracterIndex(char c){
    int id;

    if (c >= '0' && c <= '9'){
        id = (c - '0') + 26;

    } else { // Já que os títulos terão apenas letras e números
        id = (c - 'a');
    }

    return id;
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
            int id = getCaracterIndex(c); // Pegando o index da tabela ASCII

            // Vemos se a sua posição com base na tabela ASCII está vazia
            if(current_node -> children[id] == nullptr){
                current_node -> children[id] = new TrieNode();
            }

            current_node = current_node -> children[id];
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

    for (int i = 0; i < search_key.length(); i++){
        
        char c = search_key[i];
        int id = getCaracterIndex(c);

        // Se alguma letra da key não existir em nosso Trie
        if(current -> children[id] == nullptr){
            return false;
        }

        current = current -> children[id];
    }

    // Se o titulo inteiro existir em nossa Trie, checamos se é o fim de um título
    // e se existe um jogo associado
    return (current->isEndOfTitle && current->game != nullptr);
}