#pragma once
#include <raylib.h>
#include "Classes/Sprite.hpp"
#include "Classes/Player.hpp"
#include "MusicManager.hpp"
#include "LevelManager/LevelManager.hpp"

class Game {

    public:

        Game();
        ~Game();

    private:

        LevelManager levelManager;
        MusicManager musicManager;


        Player player = Player(
            {
                325,
                750,
                100,
                100
            },
            {8, 8},
            levelManager.tiles,
            levelManager.slimes
        );

        void GameLoop();
        void updateGame();
};