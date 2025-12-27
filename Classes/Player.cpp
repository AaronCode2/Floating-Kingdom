#include "Player.hpp"

Player::Player(
    Rectangle object, Vector2 frame, 
    std::vector<PlatFormTile> &tiles, 
    std::vector<Slime> &slimes
):
    Sprite(object, frame), 
    tiles(tiles), slimes(slimes)
{

    animationMap["Idle"] = {4, 0};
    animationMap["Run"] = {8, 3};
    animationMap["Hit"] = {4, 6};

    image[0] = LoadTexture("../Assets/sprites/knight.png");
    image[1] = LoadTexture("../Assets/sprites/knightLeft.png");

    srcRect.width = (float) image[direction].width / frame.x;
    srcRect.height = (float) image[direction].height / frame.y;
}

Player::~Player() {

#if !__linux__
    UnloadTexture(image[0]);
    UnloadTexture(image[1]);
#endif

}

void Player::update(MusicManager *musicManager) {

    velocity.x = 0;
    
    isOnGround = false;

    for(auto &tile : tiles) {

        if(!tile.isSolid()) continue;

        if(CheckCollisionRecs(tile.getHitBox(), hitBox)) {
            
            isOnGround = true;
            break;
        }
    }

    if(jumpKey() && isOnGround) {

        musicManager->playSoundEffect(Jump);
        if(IsWindowMaximized())
            velocity.y = -35;
        else velocity.y = -35 * (utils::getSize().y / 51);
    }

    const float speed = 6.5 * (utils::getSize().x / 51); 

    if(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) velocity.x = speed;
    else if(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) velocity.x = -speed;
    
    if(applyGravity() && (IsWindowResized() || IsWindowHidden())) musicManager->playSoundEffect(Hurt);

    move();
    draw();
}

void Player::activateResetPosition() {

    object.x = resetPosition.x * (utils::getSize().x / 50);
    object.y = resetPosition.y * (utils::getSize().y / 50);
}

void Player::move() {

    if(IsWindowResized() || IsWindowHidden()) return;

    object.x += velocity.x;
    checkCollisionX();

    object.y += velocity.y;
    checkCollisionY();
}

void Player::draw() {

    animate(frameEnd, 8);
    animationLogic();

    // The other Image Left Is Reversed, As The Frames Start At The End

    if(direction == Right) srcRect.x = srcRect.width * currentFrame;
    else srcRect.x = srcRect.width * (7 - currentFrame);

    DrawTexturePro(
        image[direction],
        srcRect, object,
        {0, 0}, 0, WHITE 
    );
}

bool Player::applyGravity() {

    if(
        object.y + object.height + velocity.y 
        <= GetScreenHeight() + (object.height + 10)
    ) velocity.y += 2;

    else {

        activateResetPosition();
        return true;
    }

    return false;
}

bool Player::jumpKey() {

    return (
        IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP) || 
        IsKeyPressed(KEY_SPACE)
    ); 
}

void Player::checkCollisionY() {

    updateHitBox();

    for(auto it = slimes.begin(); it < slimes.end(); it++) {

        if(CheckCollisionRecs(hitBox, it->getHitBox())) {

            it = slimes.erase(it);

        } else it++;
    }

    for(auto &tile : tiles) {

        if(!tile.isSolid()) continue;

        if(CheckCollisionRecs(hitBox, tile.getHitBox())) {

            if(velocity.y > 0) {
                
                velocity.y = 0;
                
                const float offset = hitBox.y - object.y + hitBox.height;
                
                object.y = tile.getHitBox().y - offset - adjust;
            }

            if(tile.getType() != Tile) continue;

            if(velocity.y < 0) {

                velocity.y = 0;

                const float offset = hitBox.y - object.y;

                object.y = tile.getHitBox().y + tile.getHitBox().height - offset + 0.01;
            }
        }
    }
}

void Player::checkCollisionX() {

    updateHitBox();

    for(auto slime : slimes) {

        if(CheckCollisionRecs(hitBox, slime.getHitBox())) {

            slime.setAnimation("Attack");
            setAnimation("Hit");
            activateResetPosition();
        }
    }

    for(auto &tile : tiles) {
        
        if(!tile.isSolid() || tile.getType() == PlatForm) continue;

        if(CheckCollisionRecs(hitBox, tile.getHitBox())) {
            
            if(velocity.x > 0) {
                
                const float offset = hitBox.x - object.x + hitBox.width;
                
                object.x = tile.getHitBox().x - offset - adjust;
            }
            
            if(velocity.x < 0) {
                
                const float offset = hitBox.x - object.x;
                
                object.x = tile.getHitBox().x + tile.getHitBox().width - offset + adjust;
            }

            velocity.x = 0;
        }
    }
}

void Player::updateHitBox() {

    if(IsWindowResized()) {

        object.width = utils::getSize().x * 2;
        object.height = utils::getSize().y * 2;
    }

    hitBox = {
        
        object.x + 33,
        object.y + 26,
        object.width - 65,
        object.height - 38
    };
}

void Player::animationLogic() {

    if(velocity.x == 0) 
        setAnimation("Idle");

    else {
        
        direction = (velocity.x > 0) ? Right : Left;
        setAnimation("Run");
    }
}

void Player::setAnimation(std::string animation) {
    
    if(frameEnd != animationMap[animation][0]) {
            
        currentFrame = 0;
        frameEnd = animationMap[animation][0];
        srcRect.y = srcRect.height * animationMap[animation][1];
    }
}