#include "Slime.hpp"

Texture2D Slime::image[2];

Slime::Slime(Rectangle object, SlimeType type):
    Sprite(object, {4, 3})
{
    
    this->type = type;

    animationMap["Idle"] = 0;
    animationMap["Attack"] = 1;
    animationMap["Hit"] = 2;

    srcRect.y = 0;
    srcRect.width = (float) image[type].width / 4;  
    srcRect.height = (float) image[type].height / 3;

}

void Slime::update() {

    updateHitBox();
    animate(4, 7);
    draw();
}

void Slime::setAnimation(std::string animation) {

    currentFrame = 0;
    srcRect.y = srcRect.height * animationMap[animation];
}

void Slime::draw() {

    srcRect.x = srcRect.width * currentFrame;

    DrawTexturePro(

        image[type],
        srcRect, object,
        {0, 0}, 0, WHITE
    );
}

void Slime::updateHitBox() {

    hitBox = {

        object.x + 10,
        object.y + 25,
        object.width - 20,
        object.height - 20
    };
}