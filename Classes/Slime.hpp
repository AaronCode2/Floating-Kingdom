#pragma once
#include <map>
#include <iostream>
#include <raylib.h>
#include "Sprite.hpp"
#include "../utils.hpp"

enum SlimeType {
    
    Green,
    Purple
};

class Slime : public Sprite {

    public:

        Slime(Rectangle object, SlimeType type);

        void update();
        void setAnimation(std::string animation);

        SlimeType getType() { return type; };

        static Texture2D image[2];

        Rectangle getHitBox() { return hitBox; };

    private:

        std::map<std::string, int> animationMap;

        Rectangle hitBox;

        SlimeType type;

        void draw();
        void updateHitBox();
};