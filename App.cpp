#include "App.hpp"

void App::init() {

    SetConfigFlags(FLAG_WINDOW_ALWAYS_RUN);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    
    logo = LoadImage("../Assets/Logo/Logo.png");

    InitWindow(1440, 750, "Floating Kingdom");
    InitAudioDevice();

    SetWindowIcon(logo);
    UnloadImage(logo);

    MaximizeWindow();
    SetTargetFPS(60);

}

void App::run() {

    init();

    Game 🎮;
}