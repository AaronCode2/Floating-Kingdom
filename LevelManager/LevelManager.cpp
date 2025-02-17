#include "LevelManager.hpp"

void LevelManager::init() {
    
    
    Slime::image[0] = LoadTexture("../Assets/sprites/SlimeGreen.png");
    Slime::image[1] = LoadTexture("../Assets/sprites/SlimePurple.png");

    Item::image[0] = LoadTexture("../Assets/sprites/coin.png");
    Item::image[1] = LoadTexture("../Assets/sprites/fruit.png");

    PlatFormTile::image[0] = LoadTexture("../Assets/sprites/platforms.png");
    PlatFormTile::image[1] = LoadTexture("../Assets/sprites/TileSet.png");

    std::cout << "\033[31mImportant!: " 
    << "It is Recommand to set the window Width to 1600\n"

    << "and Height to 811 to get the best Experience\n\033[0m";

    playerResetPosition = {325, 420};
    
    readData();
    makeBackgroundTiles();
}

void LevelManager::update(Player *player, MusicManager *musicManager) {

    for(auto it = items.begin(); it != items.end(); ) {

        it->update();

        if(CheckCollisionRecs(player->getHitBox(), it->object)) {

            if(it->getType() == Coin) 
                musicManager->playSoundEffect(CoinCollected);
            else musicManager->playSoundEffect(FruitCollected);

            it = items.erase(it);
        }
        else it++;
    }

    for(auto &slime : slimes) {

        slime.update();
    }

    for(auto &tile : tiles) {
        
        // This if check for background tiles

        if(tile.getFrame().y >= 9) continue;

        tile.update();

        // This is for the CheckPoint

        if(
            (tile.getFrame().x == 8 && tile.getFrame().y == 3)
            && CheckCollisionRecs(tile.getHitBox(), player->getHitBox())
        ) 
        {
            level++;

            tiles.clear();
            items.clear();

            readData();
            makeBackgroundTiles();
            player->activateResetPosition();

            break;
        }
    }

    switch(level) {

        case 1:
            playerResetPosition = {325, 420};
            break;
        
        case 2:
            playerResetPosition = {1521, 350};
            break;
        
        case 3:
            playerResetPosition = {225, 502};
            break;
    }

    player->resetPosition = playerResetPosition;
    player->update(musicManager);
}

void LevelManager::clearBackground() {

    for(auto &tile : tiles) {

        if(tile.getFrame().y >= 9) tile.update();
    }
}

void LevelManager::destroy() {

    UnloadTexture(PlatFormTile::image[0]);
    UnloadTexture(PlatFormTile::image[1]);

    UnloadTexture(Item::image[0]);
    UnloadTexture(Item::image[1]);
}

void LevelManager::readData() {

    std::ifstream file("../LevelManager/Levels/LevelDemo.txt");

    if(!file.is_open())
        std::cerr << "\033[31mCould Not Open Level File\n\033[0m";

    std::string line;
    float y = 0.0f;
    float tileCounter = 0.0f;

    bool levelFound = false;

    // For the Y-axis it has to be 16 Lines
    // For the X-axis it has to be 128 Columns

    while(std::getline(file, line)) {

        tileCounter = 0.0f;

        if(line.find("#Level " + std::to_string(level)) != std::string::npos)
            levelFound = true;
        else if(
            line.find("#Level " + std::to_string(level + 1))  
            != std::string::npos
        ) levelFound = false;

        if(!levelFound) continue;

        for(size_t x = 0; x < line.length(); x++) {

            switch(line[x]) {
                
                case '/': tileCounter++; 
                    break;

                case 'T':
                case 'P':
                case 'S':

                    createTiles(y, tileCounter, line, x);
                    break;
                
                case 'p':
                case 'g':

                    createSlime(y, tileCounter, line, x);
                    break;

                case 'C':
                case 'F':

                    createItem(y, tileCounter, line, x);
                    break;
            }
        } if(line.find('#') == std::string::npos) y++;
    }

    file.clear();
    file.seekg(0, std::ios::beg);
    y = 0.0f;
    tileCounter = 0.0f;
}

void LevelManager::makeBackgroundTiles() {
    
    float yFrame = 11.0f;

    const float width = 32;
    const float height = 17.22;

    for(float x = 0; x < width; x++) {
        for(float y = 0; y < height; y++) {
            
            if(y == 4) yFrame = 12.0f;
            if(y >= 5) yFrame = 13.0f;

            if(y == 10) yFrame = 14.0f;
            if(y >= 11) yFrame = 15.0f;

            tiles.push_back(PlatFormTile(
                {
                    x * utils::getSize().x,
                    y * utils::getSize().y,
                    utils::getSize().x, 
                    utils::getSize().y
                }, Tile, {0, yFrame}
            ));
        }

        yFrame = 11.0f;
    }
}

void LevelManager::createItem(
    float y, float &tileCounter,     
    std::string line, size_t x
) 
{

    bool skip = false;

    Rectangle object = {

        tileCounter * utils::getSize().x, 
        y * utils::getSize().y,
        utils::getSize().x, 
        utils::getSize().y 
    };

    if(line[x] == 'F') object.y -= 10;

    for(auto &item : items) {

        if(item.object.x == object.x && item.object.y == object.y) {
            
            skip = true;
            break;
        }
    }

    if(!skip) {
        items.push_back(Item(

            object, 
            {
                (float) line[x + 1] - adjust,
                (float) line[x + 2] - adjust
            }, 
            (line[x] == 'F') ? Fruit : Coin
        ));
    }
    
    tileCounter++;
}

void LevelManager::createSlime(
    float y, float &tileCounter, 
    std::string line, size_t x
) 
{

    bool skip = false;

    Rectangle object = {

        tileCounter * utils::getSize().x, 
        y * utils::getSize().y,
        utils::getSize().x, 
        utils::getSize().y 
    };

    for(auto &slime : slimes) {

        if(slime.object.x == object.x && slime.object.y == object.y) {

            skip = true;
            break;
        }
    }

    if(!skip) {

        slimes.push_back(Slime(

            object, 
            (line[x] == 'g') ? Green : Purple 
        ));
    }

    tileCounter++;
}

void LevelManager::createTiles(
    float y, float &tileCounter, 
    std::string line, size_t x
) 
{

    bool skip = false;

    // Screen Width Default: 1600 Screen Height Default: 811

    Rectangle object = {

        tileCounter * utils::getSize().x, 
        y * utils::getSize().y,
        utils::getSize().x, 
        utils::getSize().y 
    };

    for(auto &tile : tiles) {

        if(tile.object.x == object.x && tile.object.y == object.y) {

            skip = true;
            break;
        }
    }

    if(!skip) {

        tiles.push_back(PlatFormTile(
            object, 
            (line[x] == 'P') ? PlatForm : Tile,
            {
                (float) line[x + 1] - adjust,
                (float) line[x + 2] - adjust,
            },
            (line[x] != 'T') ? true : false  
        ));
    }

    tileCounter++;
}