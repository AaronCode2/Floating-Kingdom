#include "Tile.hpp"

Texture2D PlatFormTile::image[2];

PlatFormTile::PlatFormTile(Rectangle object, TileType tileType, Vector2 frame, bool isSolidTile) {

    this->object = object;
    this->tileType = tileType;
    this->frame = frame;
    this->isSolidTile = isSolidTile;

    if(tileType == PlatForm) {

        srcRect.width = (float) image[tileType].width / 4;
        srcRect.height = (float) image[tileType].height / 4;
    } else {

        srcRect.width = (float) image[tileType].width / 16;
        srcRect.height = (float) image[tileType].height / 16; 
    }
}

void PlatFormTile::update() {

    if(tileType == PlatForm) {

        hitBox = {

            object.x,
            object.y,
            object.width,
            object.height - 45
        };
    } else {
        
        hitBox = {

            object.x,
            object.y,
            object.width,
            object.height
        };
    }

    draw();
}

void PlatFormTile::draw() {

    srcRect.x = srcRect.width * frame.x;
    srcRect.y = srcRect.height * frame.y;

    DrawTexturePro(
        image[tileType],
        srcRect, object,
        {0, 0}, 0, WHITE
    );
}