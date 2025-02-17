#include "utils.hpp"

Color utils::testColor = {255, 0, 0, 100};

Vector2 utils::getSize() {

    const float defaultSize = 50.0f;

    return {        
        (GetScreenWidth() / 1600.0f) * defaultSize,
        (GetScreenHeight() / 811.0f) * defaultSize,
    };
}

bool utils::mouseOver(Rectangle object) {

    if(CheckCollisionPointRec(GetMousePosition(), object))
        return true;

    return false;
}
