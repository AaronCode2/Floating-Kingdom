#pragma once
#include <raylib.h>

enum SoundEffect {

    CoinCollected = 0,
    FruitCollected,
    Jump,
    Hurt
};

struct MusicManager {

    public:

        void init() { PlayMusicStream(mainMusic); };
        void playMusic() { UpdateMusicStream(mainMusic); };
        void destroy() { UnloadMusicStream(mainMusic); };

        void playSoundEffect(SoundEffect soundEffect);

    private:

        Music mainMusic = LoadMusicStream("../Assets/music/Main.mp3");

        Sound coinCollected = LoadSound("../Assets/sounds/coin.wav");
        Sound fruitCollected = LoadSound("../Assets/sounds/fruit.wav");

        Sound jump = LoadSound("../Assets/sounds/jump.wav");
        Sound hurt = LoadSound("../Assets/sounds/hurt.wav");
};