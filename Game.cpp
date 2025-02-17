#include "Game.hpp"

Game::Game() {

    levelManager.init();
    musicManager.init();

    player.object.x = levelManager.playerResetPosition.x;
    player.object.y = levelManager.playerResetPosition.y;

    GameLoop();
}

void Game::GameLoop() {

    while(!WindowShouldClose()) {

        BeginDrawing();
        levelManager.clearBackground();

        if(startMainGame()) updateGame();

        EndDrawing();
    } 
    
    CloseWindow();
    CloseAudioDevice();
}

void Game::updateGame() {

    if(IsWindowResized()) {

        levelManager.tiles.clear();
        levelManager.items.clear();
        levelManager.slimes.clear();
        levelManager.readData();
        levelManager.makeBackgroundTiles();
    }

    musicManager.playMusic();
    levelManager.update(&player, &musicManager);
}

bool Game::startMainGame() {

    time += GetFrameTime();

    float yOffset = sin(time * 2.0) * 25;

    Rectangle src = {

        0, 
        playBtn.height / 2.0f, 
        (float) playBtn.width / 2,
        (float) playBtn.height / 2
    };

    Rectangle object = {

        (float) (GetScreenWidth() / 2) - 150, 
        (float) (GetScreenHeight() / 2),
        300,
        100
    };

    if(utils::mouseOver(object)) {
        src.x = src.width;

        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) startGame = true;
    }

    if(!startGame) {

        DrawTexturePro(
            playBtn,
            src, object,
            {0, 0}, 0, WHITE
        );

        DrawText(
            "Floating Kingdom", 
            (GetScreenWidth() / 2) - 400,
            ((GetScreenHeight() / 3) - 100) + yOffset,
            100,
            GOLD
        );
    }

    return startGame;
}

Game::~Game() {

    levelManager.destroy();
    musicManager.destroy();
}