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
    Font Title;
    if (!Title.init("fonts/alagard.ttf", 128, {255, 255, 255})) {
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

    //Pause Menu || GameOver
    Button playButtonPause(PLAY_BUTTON, 452, 150, 336, 204,buttonTexs[PLAY_BUTTON]);
    Button homeButtonPause(HOME_BUTTON, 452, 350, 336, 204,buttonTexs[HOME_BUTTON]);
    Button exitButtonPause(EXIT_BUTTON, 452, 550, 336, 204,buttonTexs[EXIT_BUTTON]);

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
            } else if ((Playing && Menu) || (!Playing && !Menu)) {  // **Pause Menu || GameOver**
                playButtonPause.handleEvent(event, quit, Playing, Menu);
                homeButtonPause.handleEvent(event, quit, Playing, Menu);
                exitButtonPause.handleEvent(event, quit, Playing, Menu);
            } else if (Playing && !Menu) { // **Playing**
                stopButtonPlaying.handleEvent(event, quit, Playing, Menu);
            }
        }

        SDL_RenderClear(graphics.renderer);

        if (!Playing && Menu) {  // **Hiển thị menu chính**

            Score=0;
            enemies.clear();


            graphics.renderTexture(bg.menuKnight,60, 200, 500, 500);
            Title.render(graphics.renderer, "Hollow Knight", Gwidth / 2 - 550, 50, 1, 1);

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
