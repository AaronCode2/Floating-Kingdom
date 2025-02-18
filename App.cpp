#include "App.hpp"

void App::init() {

    SetConfigFlags(FLAG_WINDOW_ALWAYS_RUN);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    
    Image logo = LoadImage("../Assets/Logo/Logo.png");

    InitWindow(1440, 750, "Floating Kingdom");

    SetWindowIcon(logo);
    UnloadImage(logo);

    InitAudioDevice();

    MaximizeWindow();
    SetTargetFPS(60);

}

void App::run() {

    init();

    Game 🎮;
}