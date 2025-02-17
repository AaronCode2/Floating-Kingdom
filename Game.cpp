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

        if(startMainGame) 
            updateGame();

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

    
}

Game::~Game() {

    levelManager.destroy();
    musicManager.destroy();
}