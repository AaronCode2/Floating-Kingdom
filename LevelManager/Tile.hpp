#pragma once
#include <raylib.h>
#include "../utils.hpp"

enum TileType {

    PlatForm = 0,
    Tile
};

class PlatFormTile {
    
    public:

        PlatFormTile(
            Rectangle object, TileType tileType, 
            Vector2 frame, bool isSolidTile = false
        );
        
        void update();

        Rectangle getHitBox() { return hitBox; };
        bool isSolid() { return isSolidTile; };
        TileType getType() { return tileType; };
        Vector2 getFrame() { return frame; };


        Rectangle object;
        static Texture2D image[2];

    private:

        void draw();

        bool isSolidTile;

        TileType tileType;
        Rectangle srcRect;
        Rectangle hitBox;
        Vector2 frame;
};