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
        ClearBackground(GRAY);
        updateGame();
        EndDrawing();
    } 
    
    CloseWindow();
    CloseAudioDevice();
}

void Game::updateGame() {

    levelManager.clearBackground();
    musicManager.playMusic();

    if(IsKeyDown(KEY_Q)) {

        levelManager.readData();
        levelManager.makeBackgroundTiles();
    }

    if(IsWindowResized()) {

        levelManager.tiles.clear();
        levelManager.items.clear();
        levelManager.slimes.clear();
        levelManager.readData();
        levelManager.makeBackgroundTiles();
    }
    
    if(IsKeyDown(KEY_C)) {

        levelManager.tiles.clear();
        levelManager.items.clear();
        levelManager.slimes.clear();
    }

    levelManager.update(&player, &musicManager);
    player.update(&musicManager);
}

Game::~Game() {

    levelManager.destroy();
    musicManager.destroy();
}