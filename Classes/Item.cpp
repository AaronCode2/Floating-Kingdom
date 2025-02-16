#include "Item.hpp"

Texture2D Item::image[2];

Item::Item(Rectangle object, Vector2 frame, ItemType itemType):
    Sprite(object, {0, 0}) 
{
    this->itemType = itemType;

    if(itemType == Coin) {

        srcRect.y = 0;
        srcRect.width = image[itemType].width / 12;
        srcRect.height = image[itemType].height;
    } else {

        srcRect.width = image[itemType].width / 4;
        srcRect.height = image[itemType].height / 4;

        srcRect.x = srcRect.width * frame.x;
        srcRect.y = srcRect.height * frame.y;
    }
}

void Item::update() {

    draw();
    if(itemType == Coin) {

        srcRect.x = currentFrame * srcRect.width;
        animate(12);
    } else {

        time += GetFrameTime();
        float yOffset = sin(time * 2.5f) * 0.2f;

        object.y += yOffset;
    }
}

void Item::draw() {

    DrawTexturePro(
        image[itemType],
        srcRect, object,
        {0, 0}, 0, WHITE
    );
}
