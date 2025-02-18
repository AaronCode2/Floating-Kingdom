#pragma once
#include <cmath>
#include <raylib.h>
#include "utils.hpp"
#include "Classes/Sprite.hpp"
#include "Classes/Player.hpp"
#include "MusicManager/MusicManager.hpp"
#include "LevelManager/LevelManager.hpp"

class Game {

    public:

        Game();
        ~Game();

    private:
       
        Texture2D playBtn = LoadTexture("../Assets/sprites/Play.png");
              
        LevelManager levelManager;
        MusicManager musicManager;

        float time = 0;
        bool startGame = false;

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
        bool startMainGame();
};