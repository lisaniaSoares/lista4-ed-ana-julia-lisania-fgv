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

void Trie::sortResults(std::vector<Game*>& games){
    // Ordena os jogos através do insertion sort
    for(int i = 1; i < games.size(); i++){
        // devo usar esse nome?
        Game* current = games[i];
        int j = i - 1;

        while(j >= 0){
            // Se a popularidade do current for maior que o anterior
            if(games[j]->getPopularity() < current->getPopularity()){
                games[j+1] = games[j];
                j--;
            }
            // Se as popularidades forem iguais
            else if(games[j]->getPopularity() == current->getPopularity()){
                // Comparamos os títulos por ordem alfabética
                std::string j_title = toSearchKey(games[j]->getTitle());
                std::string c_title = toSearchKey(current->getTitle());
                // Se o current vier antes alfabéticamente
                if(j_title > c_title){
                    games[j+1] = games[j];
                    j--;
                }
                // Se o current estiver no lugar certo alfabeticamente
                else{
                    break;
                }
            }
            // Se o current estiver no lugar certo por popularidade
            else{
                break;
            }
        }
        // Lugar correto do current após insertion sort 
        games[j + 1] = current;        
    }            
}


void Trie::collectGames(TrieNode* node, std::vector<Game*>& results){
    // Caso base
    if(node == nullptr){
        return;
    }
    else if(node->isEndOfTitle == true){
        results.push_back(node->game);
    }

    // Chamada recursiva
    for (int i = 0; i < TrieNode::ALPHABET_SIZE; i++){
        if(node->children[i] != nullptr){
            collectGames(node->children[i], results);
        }
    }
}


std::vector<Game*> Trie::autocomplete(std::string prefix, int k){

    if(k<= 0){
        return {};
    }

    TrieNode* current_node = root;
    
    // Converte o prefixo para chave de busca
    std::string search_key = toSearchKey(prefix);

    // Para cada caractere do prefix
    for(int i = 0; i < search_key.size(); i++){
        char c = search_key[i];
        int id = getCaracterIndex(c); // Pegando o index da tabela ASCII

        // Vemos se a sua posição com base na tabela ASCII está vazia
            if(current_node -> children[id] == nullptr){
                return {};
            }
            current_node = current_node -> children[id];
    }

    // Chegamos no último elemento do prefix na trie
    std::vector<Game*> results;

    // Coletamos todos os jogos que tem esse prefixo
    collectGames(current_node, results);

    // Ordenamos os jogos encontrados
    sortResults(results);

    // Retornamos os k primeiros elementos desse vetor
    std::vector<Game*> k_results;
    // Copia até o k-ésimo elemento de results se existir
    for(int i = 0; (i < k) && (i < results.size()); i++){
        k_results.push_back(results[i]);
    }

    return k_results;
}