#include "App.hpp"

void App::run() {

    SetConfigFlags(FLAG_WINDOW_ALWAYS_RUN);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(1440, 750, "Floating Kingdom");
    InitAudioDevice();

    
    MaximizeWindow();
    SetTargetFPS(60);


    Game 🎮;
}