#ifndef LOGIC_HANDLE_H
#define LOGIC_HANDLE_H

#include <vector>
#include <algorithm>
#include <cmath>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "Defs.h"
#include "Player.h"
#include "Button.h"
#include "Media.h"
#include "Font.h"
#include "background.h"


void HandleKey(SDL_Keycode key, bool &playing, bool &menu, bool &quit, Player &player);

void HandleButton(std::vector<Button> &buttons, const SDL_Event& event, bool &quit, bool &playing, bool & menu);

void HandleMusic(Mix_Music *&currMusic, const bool &playing, const bool &menu, const long long &currScore, const long long &HighScore);

void HandleCollision(bool& playing, bool& menu, int& HurtFrame, Player& player, std::vector<Enemy>& enemies, long long& currScore,const long long& Score, long long& HighScore);

void resetScoreAndFrameCounter(long long &Score, int &Fcounter);

void renderText(const bool &playing, const bool &menu, Font &scoreFont, Font &Title, Font &TellScore,const long long &Score, const long long &currScore, const long long &HighScore, Graphics &graphics);

void updateSpeed(double &SPD, const long long &Score);

void updateScore(long long &Score);

void lockFPS(const long long Tick0);

void freeResources(Background &bg, std::vector<SDL_Texture*> &GroundV, std::vector<SDL_Texture*> &EnemiesV, std::vector<SDL_Texture*> &PlayerV, std::vector<SDL_Texture*> &buttonTexs, Font &scoreFont, Font &Title, Font &TellScore, Graphics &graphics);


std::string GetPresentScore(long long score);

#endif // LOGIC_HANDLE_H
