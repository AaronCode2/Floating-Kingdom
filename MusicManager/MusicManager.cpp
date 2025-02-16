#include "MusicManager.hpp"

void MusicManager::playSoundEffect(SoundEffect soundEffect) {

    switch(soundEffect) {

        case CoinCollected: PlaySound(coinCollected);
            break;
        
        case FruitCollected: PlaySound(fruitCollected);
            break;

        case Jump: PlaySound(jump);
            break;

        case Hurt: PlaySound(hurt);
            break;
    }
}