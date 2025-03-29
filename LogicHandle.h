#ifndef LOGIC_HANDLE_H
#define LOGIC_HANDLE_H

#include <vector>
#include <algorithm>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "Defs.h"
#include "Player.h"
#include "Button.h"
#include "Media.h"


void HandleKey(SDL_Keycode key, bool &playing, bool &menu, bool &quit, Player &player);

void HandleButton(std::vector<Button> &buttons, const SDL_Event& event, bool &quit, bool &playing, bool & menu);

void HandleMusic(Mix_Music *&currMusic, const bool &playing, const bool &menu, const long long &currScore, const long long &HighScore);

void HandleCollision(bool& playing, bool& menu, int& HurtFrame, Player& player, std::vector<Enemy>& enemies, long long& currScore,const long long& Score, long long& HighScore);

std::string GetPresentScore(long long score);

#endif // LOGIC_HANDLE_H
