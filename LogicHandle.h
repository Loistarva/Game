#ifndef LOGIC_HANDLE_H
#define LOGIC_HANDLE_H

#include <vector>

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

#endif // LOGIC_HANDLE_H
