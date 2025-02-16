#pragma once
#include <raylib.h>
#include <cmath>
#include <iostream>
#include "Sprite.hpp"

enum ItemType {

    Coin = 0,
    Fruit
};

class Item : public Sprite {

    public:

        Item(Rectangle object, Vector2 frame, ItemType itemType);

        ItemType getType() { return itemType; };

        static Texture2D image[2];

        void update();

    private:

        float time = 0.0f;

        void draw();

        ItemType itemType;
};