#pragma once
#include <raylib.h>

class Sprite {

    public:

        Sprite(Rectangle object, Vector2 frame);
    
        void update();
    
        Rectangle object;
        Texture2D image = {0};

    protected:

        Rectangle srcRect;
        Vector2 frame;
        
        int currentFrame = 0;
        int elapsedFrame = 0;

        void draw();
        void animate(int maxFrame, int bufferFrame = 6);
};