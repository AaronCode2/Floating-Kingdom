#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include "../utils.hpp"
#include "../Classes/Item.hpp"
#include "../Classes/Slime.hpp"
#include "../Classes/Player.hpp"
#include "Tile.hpp"
#include "../MusicManager/MusicManager.hpp"


struct LevelManager {


    public:

        int level = 1;

        Vector2 playerResetPosition;

        std::vector<Item> items;
        std::vector<Slime> slimes;
        std::vector<PlatFormTile> tiles;

        void init();
        void destroy();

        void update(Player *player, MusicManager *musicManger);
        void clearBackground();
        void makeBackgroundTiles();

        void readData();

    private:

        const int adjust = 48;

        void createItem(
            float y, float &tileCounter,     
            std::string line, size_t x
        );

        void createSlime(
            float y, float &tileCounter,     
            std::string line, size_t x
        );

        void createTiles(
            float y, float &tileCounter, 
            std::string line, size_t x
        );
};