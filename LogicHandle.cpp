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

void resetScoreAndFrameCounter(long long &Score, int &Fcounter) {
    Score =0;
    Fcounter = 0;
}

void renderText(const bool &playing, const bool &menu, Font &scoreFont, Font &Title, Font &TellScore,const long long &Score, const long long &currScore, const long long &HighScore, Graphics &graphics) {    if (!playing && menu) {
        Title.render(graphics.renderer, "Hollow Knight", titlePosX, titlePosY, titleScale, titleScale);
    } else if (playing && menu) {  // **Pause Menu**
        Title.render(graphics.renderer, "Game Paused", gamePausedPosX, gamePausedPosY, gamePausedScale, gamePausedScale);
    } else if (!playing && !menu) {
        if(currScore<HighScore) {
            Title.render(graphics.renderer, "Game Over!", gameOverPosX, gameOverPosY, gameOverScale, gameOverScale);
            TellScore.render(graphics.renderer, "Your Score: " + std::to_string(currScore) , yourScorePosX, yourScorePosY, yourScoreScale, yourScoreScale);
            TellScore.render(graphics.renderer, "High Score: " + std::to_string(HighScore), highScorePosX, highScorePosY, highScoreScale, highScoreScale);

        } else {
            Title.render(graphics.renderer, "Congratulation!", congratulationPosX, congratulationPosY, congratulationScale, congratulationScale);
            TellScore.render(graphics.renderer, "New High Score: " + std::to_string(currScore) , NewHighPosX, NewHighPosY, NewHighScale, NewHighScale);
        }
    } else if(playing && !menu) {
        std::string scoreText = GetPresentScore(Score);
        scoreFont.render(graphics.renderer, scoreText, ScoreTextPosX, ScoreTextPosY, ScoreTextScale, ScoreTextScale);
        scoreFont.render(graphics.renderer, "High Score: " + std::to_string(HighScore),highScorePlayingPosX, highScorePlayingPosY, highScorePlayingScale, highScorePlayingScale);
    }
}

void updateSpeed(double &SPD, const long long &Score) {
    SPD = SPD0 + sqrt(static_cast<double>(Score)) / DeltaSpeed;
}

void updateScore(long long &Score) {
    Score += DeltaScore;
}

void lockFPS(const long long Tick0) {
    long long Tick = SDL_GetTicks();
    if (Tick - Tick0 < 1000 / FPS) {
        SDL_Delay(1000 / FPS - (Tick - Tick0));
    }
}

void freeResources(Background &bg, std::vector<SDL_Texture*> &GroundV, std::vector<SDL_Texture*> &EnemiesV, std::vector<SDL_Texture*> &PlayerV, std::vector<SDL_Texture*> &buttonTexs, Font &scoreFont, Font &Title, Font &TellScore, Graphics &graphics) {

    for (auto tex : GroundV) SDL_DestroyTexture(tex);
    for (auto tex : EnemiesV) SDL_DestroyTexture(tex);
    for (auto tex : PlayerV) SDL_DestroyTexture(tex);
    for (auto tex : buttonTexs) SDL_DestroyTexture(tex);

    SDL_DestroyTexture(bg.menuKnight);
    SDL_DestroyTexture(bg.BloodScreen);
    SDL_DestroyTexture(bg.blur);
    SDL_DestroyTexture(bg.leftForest);
    SDL_DestroyTexture(bg.rightForest);
    SDL_DestroyTexture(bg.sky);
    SDL_DestroyTexture(bg.top);

    scoreFont.close();
    Title.close();
    TellScore.close();
    TTF_Quit();  // Tắt hệ thống font



    Mix_HaltMusic();
    Mix_FreeMusic(MenuMusic);
    Mix_FreeMusic(LowScore);
    Mix_FreeMusic(MediumScore);
    Mix_FreeMusic(MHighScore);
    Mix_FreeMusic(Champion);
    Mix_FreeMusic(YouTried);
    Mix_FreeChunk(Click);
    Mix_FreeChunk(GetHit);
    Mix_CloseAudio();

    graphics.quit();
    SDL_Quit();
}

std::string GetPresentScore(long long score) {
    std::string scoreText;
    scoreText = score%100==0 ? "Score: " + std::to_string(score) : scoreText = "Score: " + std::to_string(score-50);
    return scoreText;
}

