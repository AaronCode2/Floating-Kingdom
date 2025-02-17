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

    DrawText(
        "Floating Kingdom", 
        (GetScreenWidth() / 2) - 400,
        ((GetScreenHeight() / 3) - 100) + yOffset,
        100,
        GOLD
    );

    Rectangle src = {

        0, 
        src.height, 
        (float) playBtn.width / 2,
        (float) playBtn.height / 2
    };

    Rectangle dest = {

        340, 
        280,
        300,
        100
    };

    DrawTexturePro(
        playBtn,
        src, dest,
        {0, 0}, 0, WHITE
    );

    return false;
}

Game::~Game() {

    levelManager.destroy();
    musicManager.destroy();
}