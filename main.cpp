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



int main(int argc, char* argv[])
{


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


    int Tick1, Tick2;
    bool quit = 0;
    SDL_Event event;
    double SPD,SPD0=2;
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
                    if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a) {
                        player.moveLeft();
                    }
                    if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d) {
                        player.moveRight();
                    }
                    break;
            }
        }
        Score+=50;
        SPD = SPD0 + sqrt(static_cast<double>(Score))/20;

        UpdateEnemies(Score,SPD);
        std::cerr << Score << '\n';

        if (player.checkCollision(enemies)) {
            std::cout << "Game Over!\n";
            quit = true;
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

        if(Score%100==0) {
            std::string scoreText = "Score: " + std::to_string(Score);
            scoreFont.render(graphics.renderer, scoreText, Gwidth / 2 - 200, 20,2,2);
        } else {
            std::string scoreText = "Score: " + std::to_string(Score-50);
            scoreFont.render(graphics.renderer, scoreText, Gwidth / 2 - 200, 20,2,2);
        }

        graphics.presentScene();
        SDL_RenderClear(graphics.renderer);

        Tick2 = SDL_GetTicks();
        if (Tick2 - Tick1 < 1000 / FPS) {
            SDL_Delay(1000 / FPS - (Tick2 - Tick1));
        }
    }

    return 0;
}
