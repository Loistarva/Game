#include <SDL.h>

#include "LogicHandle.h"

void HandleKey(SDL_Keycode key, bool &playing, bool &menu, bool &quit, Player &player) {
    if (key == SDLK_ESCAPE) { // Bấm ESC để thoát về menu
        if (!playing && menu) {
            quit = true;
        } else {
            menu = !menu;
        }
    }
    if (key == SDLK_LEFT || key == SDLK_a) {
        player.moveLeft();
    }
    if (key == SDLK_RIGHT || key == SDLK_d) {
        player.moveRight();
    }
}

void HandleButton(std::vector<Button> &buttons,const SDL_Event& event, bool &quit, bool &playing, bool & menu) {
    if (!playing && menu) {  // **menu chính**
        buttons[playButtonMenu].handleEvent(event, quit, playing, menu);
        buttons[exitButtonMenu].handleEvent(event, quit, playing, menu);
    } else if (playing && menu) {  // **Pause menu**
        buttons[playButtonPause].handleEvent(event, quit, playing, menu);
        buttons[homeButtonPause].handleEvent(event, quit, playing, menu);
        buttons[exitButtonPause].handleEvent(event, quit, playing, menu);
    } else if(!playing && !menu) {  // **Game Over**
        buttons[playButtonOver].handleEvent(event, quit, playing, menu);
        buttons[homeButtonOver].handleEvent(event, quit, playing, menu);
        buttons[exitButtonOver].handleEvent(event, quit, playing, menu);
    } else if (playing && !menu) { // **playing**
        buttons[stopButtonPlaying].handleEvent(event, quit, playing, menu);
    }
}

void HandleMusic(Mix_Music *&currMusic, const bool &playing, const bool &menu, const long long &currScore, const long long &HighScore) {
    if (!playing && menu) {
        if (Mix_PlayingMusic() == 0 || currMusic != MenuMusic) {
            Mix_PlayMusic(MenuMusic, -1);
            currMusic = MenuMusic;
        }
    } else if (!playing && !menu) {
        if(currScore<HighScore) {
            if (Mix_PlayingMusic() == 0 || (currMusic != YouTried && currMusic != Champion)) {
                Mix_PlayMusic(YouTried, -1);
                currMusic = YouTried;
            }
        } else {
            if (Mix_PlayingMusic() == 0 || currMusic != Champion) {
                Mix_PlayMusic(Champion, -1);
                currMusic = Champion;
            }
        }
    } else {
        if (currScore <= 72600) {
            if (Mix_PlayingMusic() == 0 || currMusic != LowScore) {
                Mix_PlayMusic(LowScore, -1);
                currMusic = LowScore;
            }
        } else if (currScore <= 265000) {
            if (Mix_PlayingMusic() == 0 || currMusic != MediumScore) {
                Mix_PlayMusic(MediumScore, -1);
                currMusic = MediumScore;
            }
        } else {
            if (Mix_PlayingMusic() == 0 || currMusic != MHighScore) {
                Mix_PlayMusic(MHighScore, -1);
                currMusic = MHighScore;
            }
        }
    }
}

void HandleCollision(bool& playing, bool& menu, int& HurtFrame, Player& player, std::vector<Enemy>& enemies, long long& currScore,const long long& Score, long long& HighScore) {
    HurtFrame = 6;
    player.Heart--;
    enemies.erase(std::remove_if(enemies.begin(),enemies.end(),[&] (const Enemy& enemy){ return player.laneIndex==enemy.type; }),enemies.end());
    if(player.Heart<=0) {
        playing = false;
        menu = false;
        currScore = Score;

        if(currScore > HighScore) {
            saveHighScore("HighScore.txt",currScore);
            HighScore = currScore;
        }
    } else Mix_PlayChannel(-1, GetHit, 0);
}

std::string GetPresentScore(long long score) {
    std::string scoreText;
    scoreText = score%100==0 ? "Score: " + std::to_string(score) : scoreText = "Score: " + std::to_string(score-50);
    return scoreText;
}

