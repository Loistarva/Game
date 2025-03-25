#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <random>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "graphics.h"
#include "Font.h"
#include "Defs.h"
#include "background.h"
#include "Enemy.h"
#include "Player.h"
#include "Button.h"



int main(int argc, char* argv[]) {
    Graphics graphics;
    graphics.init();

    Font scoreFont;
    if (!scoreFont.init("fonts/alagard.ttf", 32, {0, 0, 0})) {
        std::cerr << "Error in create font!\n";
        return -1;
    }

    Background bg = loadBackground(graphics);
    std::vector<SDL_Texture*> GroundV = loadGroundTextures(graphics);
    std::vector<SDL_Texture*> EnemiesV = loadEnemies(graphics);
    std::vector<SDL_Texture*> PlayerV = loadPlayer(graphics);
    std::vector<SDL_Texture*> buttonTexs = loadButton(graphics);

    //Menu chính
    Button playButtonMenu(PLAY_BUTTON, 820, 200, 280, 170,buttonTexs[PLAY_BUTTON]);
    Button exitButtonMenu(EXIT_BUTTON, 820, 500, 280, 170,buttonTexs[EXIT_BUTTON]);

    //Pause Menu || GameOver
    Button playButtonPause(STOP_BUTTON, 514, 400, 252, 153,buttonTexs[STOP_BUTTON]);
    Button homeButtonPause(HOME_BUTTON, 514, 600, 252, 153,buttonTexs[HOME_BUTTON]);
    Button exitButtonPause(EXIT_BUTTON, 514, 800, 252, 153,buttonTexs[EXIT_BUTTON]);

    //Playing Menu
    Button stopButtonPlaying(STOP_BUTTON, 1000, 50, 56, 34,buttonTexs[STOP_BUTTON]);


    int Tick1, Tick2;
    bool quit = false;
    bool Playing = false;  // Chưa chơi
    bool Menu = true;      // Đang ở menu
    SDL_Event event;
    double SPD, SPD0 = 2;
    long long Score = 0;

    Player player(580);

    while (!quit) {
        Tick1 = SDL_GetTicks();
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_RETURN) { // Enter để bắt đầu / tiếp tục
                        if (!Playing && Menu) {  // Đang ở menu, bấm Enter để vào game
                            Playing = true;
                            Menu = false;
                        } else if (Playing && Menu) {  // Đang tạm dừng, tiếp tục game
                            Menu = false;
                        }
                    }
                    if (event.key.keysym.sym == SDLK_p) {  // Bấm P để Pause
                        if (Playing) {
                            Menu = !Menu;
                        }
                    }
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
        }

        SDL_RenderClear(graphics.renderer);

        if (!Playing && Menu) {  // **Hiển thị menu chính**
            scoreFont.render(graphics.renderer, "Press Enter to Start", Gwidth / 2 - 150, Gheight / 2, 2, 2);
        }
        else if (Playing && Menu) {  // **Pause Menu**
            scoreFont.render(graphics.renderer, "Game Paused", Gwidth / 2 - 100, Gheight / 2 - 20, 2, 2);
            scoreFont.render(graphics.renderer, "Press P to Resume", Gwidth / 2 - 130, Gheight / 2 + 20, 1, 1);
            scoreFont.render(graphics.renderer, "Press ESC to Quit", Gwidth / 2 - 130, Gheight / 2 + 50, 1, 1);
        }
        else if (!Playing && !Menu) {  // **Game Over**
            scoreFont.render(graphics.renderer, "Game Over!", Gwidth / 2 - 100, Gheight / 2 - 20, 2, 2);
            scoreFont.render(graphics.renderer, "Press Enter to Restart", Gwidth / 2 - 150, Gheight / 2 + 20, 1, 1);
            scoreFont.render(graphics.renderer, "Press ESC to Exit", Gwidth / 2 - 120, Gheight / 2 + 50, 1, 1);
        }
        else {  // **Gameplay**
            Score += 50;
            SPD = SPD0 + sqrt(static_cast<double>(Score)) / 20;
            UpdateEnemies(Score, SPD);

            if (player.checkCollision(enemies)) {
                Playing = false;
                Menu = false;
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

            // Hiển thị điểm số
            std::string scoreText = "Score: " + std::to_string(Score);
            scoreFont.render(graphics.renderer, scoreText, Gwidth / 2 - 200, 20, 2, 2);
        }

        graphics.presentScene();
        SDL_Delay(1000 / FPS);
    }

    return 0;
}
