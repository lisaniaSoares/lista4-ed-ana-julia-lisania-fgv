#ifndef GAME.HPP
#define GAME.HPP

class Game {

private:
    std::string title;
    std::string shortDescription;
    int popularity;

public:

    Game();
    Game(std::string title, std::string shortDescription, int popularity);
    ~Game();

    std::string getTitle();
    std::string getShortDescription();
    int getPopularity();
};

#endif