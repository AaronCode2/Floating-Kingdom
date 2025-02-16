#include "Sprite.hpp"

Sprite::Sprite(Rectangle object, Vector2 frame) {

    this->object = object;
    this->frame = frame;
}

void Sprite::update() {
    
    draw();
    animate(frame.x);
}

void Sprite::draw() {

    srcRect = {

        (float) srcRect.width * currentFrame, 
        0,
        (float) image.width / frame.x,
        (float) image.height / frame.y
    };

    DrawTexturePro(
        image,
        srcRect, object,
        {0, 0}, 0, WHITE
    );
}

void Sprite::animate(int maxFrame, int bufferFrame) {

    elapsedFrame++;

    if(elapsedFrame % bufferFrame == 0) {

        if(currentFrame < maxFrame - 1) currentFrame++;
        else currentFrame = 0;
    }
}