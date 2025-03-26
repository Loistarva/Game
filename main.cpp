#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <random>

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

long long loadHighScore(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    long long highScore = 0;

    if (file.is_open()) {
        if (std::getline(file, line)) {
            try {
                highScore = std::stoll(line);
            } catch (const std::exception& e) {
                std::cerr << "Error converting high score from file: " << e.what() << "\n";
            }
        }
        file.close();
    } else {
        std::cerr << "Could not open " << filename << " for reading!\n";
    }

    return highScore;
}

void saveHighScore(const std::string& filename, long long newScore) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << newScore;
        file.close();
    } else {
        std::cerr << "Could not open " << filename << " for writing!\n";
    }
}

int main(int argc, char* argv[]) {
    Graphics graphics;
    graphics.init();

    Font scoreFont;
    if (!scoreFont.init("fonts/alagard.ttf", 32, {0, 0, 0})) {
        std::cerr << "Error in create font!\n";
        return -1;
    }
    Font Title;
    if (!Title.init("fonts/alagard.ttf", 128, {255, 255, 255})) {
        std::cerr << "Error in create font!\n";
        return -1;
    }

    Font TellScore;
    if (!TellScore.init("fonts/alagard.ttf", 64, {255, 255, 255})) {
        std::cerr << "Error in create font!\n";
        return -1;
    }

    Background bg = loadBackground(graphics);
    std::vector<SDL_Texture*> GroundV = loadGroundTextures(graphics);
    std::vector<SDL_Texture*> EnemiesV = loadEnemies(graphics);
    std::vector<SDL_Texture*> PlayerV = loadPlayer(graphics);
    std::vector<SDL_Texture*> buttonTexs = loadButton(graphics);

    //Menu chính
    Button playButtonMenu(PLAY_BUTTON, 720, 150, 420, 255,buttonTexs[PLAY_BUTTON]);
    Button exitButtonMenu(EXIT_BUTTON, 720, 450, 420, 255,buttonTexs[EXIT_BUTTON]);

    //Pause Menu
    Button playButtonPause(PLAY_BUTTON, 452, 150, 336, 204,buttonTexs[PLAY_BUTTON]);
    Button homeButtonPause(HOME_BUTTON, 452, 350, 336, 204,buttonTexs[HOME_BUTTON]);
    Button exitButtonPause(EXIT_BUTTON, 452, 550, 336, 204,buttonTexs[EXIT_BUTTON]);

    // GameOver
    Button playButtonOver(PLAY_BUTTON, 52, 500, 336, 204,buttonTexs[PLAY_BUTTON]);
    Button homeButtonOver(HOME_BUTTON, 452, 500, 336, 204,buttonTexs[HOME_BUTTON]);
    Button exitButtonOver(EXIT_BUTTON, 852, 500, 336, 204,buttonTexs[EXIT_BUTTON]);

    //Playing Menu
    Button stopButtonPlaying(STOP_BUTTON, 1050, -2, 112, 68,buttonTexs[STOP_BUTTON]);

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
                    if (event.key.keysym.sym == SDLK_ESCAPE) { // Bấm ESC để thoát về menu
                        if (Playing) {
                            Menu = !Menu;
                        } else {
                            quit = true;
                        }
                    }
                    if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a) {
                        player.moveLeft();
                    }
                    if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d) {
                        player.moveRight();
                    }

                    break;
            }
            if (!Playing && Menu) {  // **Menu chính**
                playButtonMenu.handleEvent(event, quit, Playing, Menu);
                exitButtonMenu.handleEvent(event, quit, Playing, Menu);
            } else if (Playing && Menu) {  // **Pause Menu**
                playButtonPause.handleEvent(event, quit, Playing, Menu);
                homeButtonPause.handleEvent(event, quit, Playing, Menu);
                exitButtonPause.handleEvent(event, quit, Playing, Menu);
            } else if(!Playing && !Menu) {  // **Game Over**
                playButtonOver.handleEvent(event, quit, Playing, Menu);
                homeButtonOver.handleEvent(event, quit, Playing, Menu);
                exitButtonOver.handleEvent(event, quit, Playing, Menu);
            } else if (Playing && !Menu) { // **Playing**
                stopButtonPlaying.handleEvent(event, quit, Playing, Menu);
            }
        }

        SDL_RenderClear(graphics.renderer);

        if (!Playing && Menu) {  // **Hiển thị menu chính**

            Score=0;
            enemies.clear();
            player.reset();


            graphics.renderTexture(bg.menuKnight,80, 200, 500, 500);
            Title.render(graphics.renderer, "Hollow Knight", Gwidth / 2 - 550, 50, 1, 1);

            if (Mix_PlayingMusic() == 0 || currMusic != MenuMusic) {
                Mix_PlayMusic(MenuMusic, -1);
                currMusic = MenuMusic;
            }



            playButtonMenu.render(graphics.renderer);
            exitButtonMenu.render(graphics.renderer);

            playButtonMenu.update(quit,Playing,Menu);
            exitButtonMenu.update(quit,Playing,Menu);



        }
        else if (Playing && Menu) {  // **Pause Menu**

            Title.render(graphics.renderer, "Game Paused", 250, 50, 1, 1);

            playButtonPause.render(graphics.renderer);
            homeButtonPause.render(graphics.renderer);
            exitButtonPause.render(graphics.renderer);

            playButtonPause.update(quit,Playing,Menu);
            homeButtonPause.update(quit,Playing,Menu);
            exitButtonPause.update(quit,Playing,Menu);
        }
        else if (!Playing && !Menu) {  // **Game Over**
            if(currScore<HighScore) {
                Title.render(graphics.renderer, "Game Over!", 270, 50, 1, 1);
                TellScore.render(graphics.renderer, "Your Score: " + std::to_string(currScore) , 310, 200, 1, 1);
                TellScore.render(graphics.renderer, "High Score: " + std::to_string(HighScore), 320, 300, 1, 1);

                if (Mix_PlayingMusic() == 0 || currMusic != YouTried) {
                    Mix_PlayMusic(YouTried, -1);
                    currMusic = YouTried;
                }
            } else {
                Title.render(graphics.renderer, "Congratulation!", 200, 50, 1, 1);
                TellScore.render(graphics.renderer, "New High Score: " + std::to_string(currScore) , 310, 200, 1, 1);

                if (Mix_PlayingMusic() == 0 || currMusic != Champion) {
                    Mix_PlayMusic(Champion, -1);
                    currMusic = Champion;
                }
            }

            playButtonOver.render(graphics.renderer);
            homeButtonOver.render(graphics.renderer);
            exitButtonOver.render(graphics.renderer);

            playButtonOver.update(quit,Playing,Menu);
            homeButtonOver.update(quit,Playing,Menu);
            exitButtonOver.update(quit,Playing,Menu);

            Score=0;
            enemies.clear();
            player.reset();
        }
        else {  // **Gameplay**
            Score += 50;
            SPD = SPD0 + sqrt(static_cast<double>(Score)) / 50;
            UpdateEnemies(Score, SPD);

            if (player.checkCollision(enemies)) {
                Playing = false;
                Menu = false;
                currScore = Score;
                Mix_PlayChannel(-1, GetHit, 0);

                if(currScore > HighScore) {
                    saveHighScore("HighScore.txt",currScore);
                    HighScore = currScore;
                    if (Mix_PlayingMusic() == 0 || currMusic==Champion) {
                        Mix_PlayMusic(Champion, -1);
                        currMusic=Champion;
                    } else {
                        Mix_HaltMusic();
                        Mix_PlayMusic(Champion, -1);
                        currMusic=Champion;
                    }
                }
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

            stopButtonPlaying.render(graphics.renderer);
            stopButtonPlaying.update(quit,Playing,Menu);

            // Hiển thị điểm số

            std::string scoreText;
            if(Score%100==0) scoreText = "Score: " + std::to_string(Score);
            else scoreText = "Score: " + std::to_string(Score-50);
            scoreFont.render(graphics.renderer, scoreText, Gwidth / 2 - 400, 20, 2, 2);
            scoreFont.render(graphics.renderer, "High Score: " + std::to_string(HighScore),700,40,1,1);
            if (Score <= 72600) {
                if (Mix_PlayingMusic() == 0 || currMusic != LowScore) {
                    Mix_PlayMusic(LowScore, -1);
                    currMusic = LowScore;
                }
            } else if (Score <= 265000) {
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
