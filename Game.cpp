#include "Game.hpp"
#include <string>

Game::Game(std::string title, std::string shortDescription, int popularity){
    this -> title = title;
    this -> shortDescription = shortDescription;
    this -> popularity = popularity;
}

Game::~Game(){
    // Não há nenhuma estrutura que precise ser liberada de memória manualmente
}

std::string Game::getTitle(){
    return this -> title;
}

std::string Game::getShortDescription(){
    return this -> shortDescription;
}

int Game::getPopularity(){
    return this -> popularity;
}