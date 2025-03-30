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
    Font scoreFont, Title, TellScore;
    if (!initFonts(scoreFont, Title, TellScore)) return -1;
    Background bg = loadBackground(graphics);
    std::vector<SDL_Texture*> GroundV = loadGroundTextures(graphics);
    std::vector<SDL_Texture*> EnemiesV = loadEnemies(graphics);
    std::vector<SDL_Texture*> PlayerV = loadPlayer(graphics);
    std::vector<SDL_Texture*> buttonTexs = loadButton(graphics);
    std::vector<Button> buttons;
    initButtons(buttons, buttonTexs);
    InitMedia();
    long long Tick0;
    bool quit = false;
    bool Playing = false;
    bool Menu = true;
    SDL_Event event;
    double SPD;
    long long Score = 0;
    long long currScore = 0;
    long long HighScore = loadHighScore("HighScore.txt");
    int BSFrames = 0;
    Mix_Music* currMusic = nullptr;
    Player player(PlayerPosY);
    while (!quit) {
        Tick0 = SDL_GetTicks();
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
        if ((!Playing && Menu) || (!Playing && !Menu)) {
            resetScoreAndFrameCounter(Score, BSFrames);
            enemies.clear();
            player.reset();
        }
        else if(Playing && !Menu) {  // **Gameplay**
            updateScore(Score);
            updateSpeed(SPD, Score);
            UpdateEnemies(Score, SPD);
            if (player.checkCollision(enemies)) {
                HandleCollision(Playing, Menu, BSFrames, player, enemies, currScore, Score, HighScore);
            }
            renderBackground(graphics, bg, SPD, GroundV);
            renderPlayerAndEnemies(enemies,EnemiesV, player, PlayerV, graphics, BSFrames, bg);
        }
        HandleMusic(currMusic, Playing, Menu, Score, HighScore);
        presentButtons(quit, Playing, Menu, buttons, bg, graphics);
        renderText(Playing, Menu, scoreFont, Title, TellScore, Score , currScore, HighScore, graphics);
        graphics.presentScene();
        lockFPS(Tick0);
    }
    freeResources(bg, GroundV, EnemiesV, PlayerV, buttonTexs, scoreFont, Title, TellScore, graphics);
    return 0;
}
