#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <random>
#include <algorithm>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "graphics.h"
#include "Font.h"
#include "Defs.h"
#include "background.h"
#include "Enemy.h"
#include "Player.h"
#include "Button.h"
#include "Media.h"
#include "LogicHandle.h"


int main(int argc, char* argv[]) {
    Graphics graphics;
    graphics.init();
    Font scoreFont;
    Font Title;
    Font TellScore;
    if (!initFonts(scoreFont, Title, TellScore)) return -1;
    Background bg = loadBackground(graphics);
    std::vector<SDL_Texture*> GroundV = loadGroundTextures(graphics);
    std::vector<SDL_Texture*> EnemiesV = loadEnemies(graphics);
    std::vector<SDL_Texture*> PlayerV = loadPlayer(graphics);
    std::vector<SDL_Texture*> buttonTexs = loadButton(graphics);
    std::vector<Button> buttons;
    initButtons(buttons, buttonTexs);
    InitMedia();
    int Tick1, Tick2;
    bool quit = false;
    bool Playing = false;  // Chưa chơi
    bool Menu = true;      // Đang ở menu
    SDL_Event event;
    double SPD, SPD0 = 2;
    long long Score = 0;
    long long currScore = 0;
    long long HighScore = loadHighScore("HighScore.txt");
    int BSFrames = 0;
    Mix_Music* currMusic = nullptr;
    Player player(580);
    Mix_PlayMusic(MenuMusic,-1);
    currMusic = MenuMusic;
    while (!quit) {
        Tick1 = SDL_GetTicks();
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    HandleKey(event.key.keysym.sym, Playing, Menu, quit, player);
                    break;
            }
            HandleButton(buttons, event, quit, Playing, Menu);
        }
        SDL_RenderClear(graphics.renderer);
        if (!Playing && Menu) {  // **Hiển thị menu chính**
            Score=0;
            enemies.clear();
            player.reset();
            graphics.renderTexture(bg.menuKnight,menuKnightPosX, menuKnightPosY, menuKnightW, menuKnightH);
            Title.render(graphics.renderer, "Hollow Knight", titlePosX, titlePosY, titleScale, titleScale);
        }
        else if (Playing && Menu) {  // **Pause Menu**
            Title.render(graphics.renderer, "Game Paused", gamePausedPosX, gamePausedPosY, gamePausedScale, gamePausedScale);
        }
        else if (!Playing && !Menu) {  // **Game Over**
            if(currScore<HighScore) {
                Title.render(graphics.renderer, "Game Over!", gameOverPosX, gameOverPosY, gameOverScale, gameOverScale);
                TellScore.render(graphics.renderer, "Your Score: " + std::to_string(currScore) , yourScorePosX, yourScorePosY, yourScoreScale, yourScoreScale);
                TellScore.render(graphics.renderer, "High Score: " + std::to_string(HighScore), highScorePosX, highScorePosY, highScoreScale, highScoreScale);

            } else {
                Title.render(graphics.renderer, "Congratulation!", congratulationPosX, congratulationPosY, congratulationScale, congratulationScale);
                TellScore.render(graphics.renderer, "New High Score: " + std::to_string(currScore) , NewHighPosX, NewHighPosY, NewHighScale, NewHighScale);
            }
            Score=0;
            enemies.clear();
            player.reset();
        }
        else {  // **Gameplay**
            Score += 50;
            SPD = SPD0 + sqrt(static_cast<double>(Score)) / 30;
            UpdateEnemies(Score, SPD);

            if (player.checkCollision(enemies)) {
                BSFrames = 6;
                player.Heart--;
                enemies.erase(std::remove_if(enemies.begin(),enemies.end(),[&] (const Enemy& enemy){ return player.laneIndex==enemy.type; }),enemies.end());
                if(player.Heart<=0) {
                    Playing = false;
                    Menu = false;
                    currScore = Score;

                    if(currScore > HighScore) {
                        saveHighScore("HighScore.txt",currScore);
                        HighScore = currScore;
                    }
                } else Mix_PlayChannel(-1, GetHit, 0);
            }


            renderBackground(graphics, bg, SPD, GroundV);

            bool playerRendered = false;
            for (const auto& enemy : enemies) {
                if (!playerRendered && enemy.PosY > player.PosY + 100) {
                    renderPlayer(graphics, player, PlayerV);
                    playerRendered = true;
                }
                renderEnemy(graphics, enemy, EnemiesV);
            }
            if (!playerRendered) {
                renderPlayer(graphics, player, PlayerV);
            }
            if (BSFrames > 0) {
                graphics.renderTexture(bg.BloodScreen, 0, 0);
                BSFrames--;  // Giảm bộ đếm sau mỗi frame
            }


            // Hiển thị điểm số

            std::string scoreText;
            if(Score%100==0) scoreText = "Score: " + std::to_string(Score);
            else scoreText = "Score: " + std::to_string(Score-50);
            scoreFont.render(graphics.renderer, scoreText, Gwidth / 2 - 380, 20, 2, 2);
            scoreFont.render(graphics.renderer, "High Score: " + std::to_string(HighScore),700,40,1,1);
        }
        HandleMusic(currMusic, Playing, Menu, Score, HighScore);
        presentButtons(quit, Playing, Menu, buttons, graphics);

        graphics.presentScene();
        Tick2 = SDL_GetTicks();
        if (Tick2 - Tick1 < 1000 / FPS) {
            SDL_Delay(1000 / FPS - (Tick2 - Tick1));
        }
    }

for (auto tex : GroundV) SDL_DestroyTexture(tex);
for (auto tex : EnemiesV) SDL_DestroyTexture(tex);
for (auto tex : PlayerV) SDL_DestroyTexture(tex);
for (auto tex : buttonTexs) SDL_DestroyTexture(tex);
SDL_DestroyTexture(bg.menuKnight);

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



    return 0;
}
