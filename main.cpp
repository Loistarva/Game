#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <random>

#include <SDL.h>
#include <SDL_image.h>

#include "Grahics.h"
#include "Defs.h"
#include "background.h"
#include "Enemy.h"
#include "Player.h"

using namespace std;



void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if (SDL_PollEvent(&e) != 0 && (e.type == SDL_KEYDOWN || e.type == SDL_QUIT))
            return;
        SDL_Delay(10);
    }
}
int main(int argc, char* argv[])
{


    Graphics graphics;
    graphics.init();

    Background bg = loadBackground(graphics);
    vector<SDL_Texture*> GroundV = loadGroundTextures(graphics);
    vector<SDL_Texture*> EnemiesV = loadEnemies(graphics);
    vector<SDL_Texture*> PlayerV = loadPlayer(graphics);


    int Tick1, Tick2;
    bool quit = 0;
    SDL_Event event;
    double SPD,SPD0=2;
    long long Score = 0;

    Player player;



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
        SPD = SPD0 + sqrt(static_cast<double>(Score))/50;

        UpdateEnemies(Score,SPD);
        cerr << Score << '\n';

        if (player.checkCollision(enemies)) {
            cout << "Game Over!\n";
            quit = true;
        }

        renderBackground(graphics, bg, SPD, GroundV);

        renderPlayer(graphics, player, PlayerV);

        for(const auto& enemy: enemies) {
            renderEnemy(graphics,enemy,EnemiesV);
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
