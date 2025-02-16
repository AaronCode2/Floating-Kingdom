#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <array>
#include <raylib.h>
#include "Sprite.hpp"
#include "Slime.hpp"
#include "../utils.hpp"
#include "../LevelManager/Tile.hpp"
#include "../MusicManager/MusicManager.hpp"

enum Direction {

    Right = 0,
    Left,
};

class Player : public Sprite {

    public:

        Player(
            Rectangle object, Vector2 frame, 
            std::vector<PlatFormTile> &tiles,
            std::vector<Slime> &slimes
        );

        ~Player();

        void update(MusicManager *musicManager);
        void activateResetPosition();
        void setAnimation(std::string animation);

        Rectangle getHitBox() { return hitBox; };
        
        Vector2 resetPosition;

    private:  
        
        std::map<std::string, std::array<int, 2>> animationMap;

        std::vector<PlatFormTile> &tiles;
        std::vector<Slime> &slimes;

        Vector2 velocity;
        Rectangle hitBox;
        Texture2D image[2];

        int frameEnd;
        
        const float adjust = 0.01;

        bool isOnGround = false;

        void move();

        bool applyGravity();
        bool jumpKey();

        void checkCollisionY();
        void checkCollisionX();
        void updateHitBox();

        void draw();
        void animationLogic();

        Direction direction = Right;
};