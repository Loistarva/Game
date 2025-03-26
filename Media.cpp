#include "Media.h"
#include <iostream>

extern Mix_Music* MenuMusic = nullptr;
extern Mix_Music* LowScore = nullptr;
extern Mix_Music* MediumScore = nullptr;
extern Mix_Music* MHighScore = nullptr;
extern Mix_Music* Champion = nullptr;
extern Mix_Music* YouTried = nullptr;

extern Mix_Chunk* Click = nullptr;
extern Mix_Chunk* GetHit = nullptr;

void InitMedia()
{
    bool success = true;

    // Initialize SDL_Mixer
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        success = false;
    }

    // Load music files
    MenuMusic = Mix_LoadMUS("sound/OnceUponATime.mp3");
    if (MenuMusic == nullptr)
    {
        std::cerr << "Failed to load menu music: " << Mix_GetError() << std::endl;
        success = false;
    }

    LowScore = Mix_LoadMUS("sound/Memory.mp3");
    if (LowScore == nullptr)
    {
        std::cerr << "Failed to load low score music: " << Mix_GetError() << std::endl;
        success = false;
    }

    MediumScore = Mix_LoadMUS("sound/HisTheme.mp3");
    if (MediumScore == nullptr)
    {
        std::cerr << "Failed to load medium score music: " << Mix_GetError() << std::endl;
        success = false;
    }

    MHighScore = Mix_LoadMUS("sound/SaveTheWorld.mp3");
    if (MHighScore == nullptr)
    {
        std::cerr << "Failed to load high score music: " << Mix_GetError() << std::endl;
        success = false;
    }

    Champion = Mix_LoadMUS("sound/HopesAndDreams.mp3");
    if (Champion == nullptr)
    {
        std::cerr << "Failed to load champion music: " << Mix_GetError() << std::endl;
        success = false;
    }

    YouTried = Mix_LoadMUS("sound/FallenDown.mp3");
    if (YouTried == nullptr)
    {
        std::cerr << "Failed to load You Tried music: " << Mix_GetError() << std::endl;
        success = false;
    }

    // Load sound effects
    Click = Mix_LoadWAV("sound/mouse_click.wav");
    if (Click == nullptr)
    {
        std::cerr << "Failed to load mouse click sound: " << Mix_GetError() << std::endl;
        success = false;
    }

    GetHit = Mix_LoadWAV("sound/Hurt.mp3");
    if (GetHit == nullptr)
    {
        std::cerr << "Failed to load get hit sound: " << Mix_GetError() << std::endl;
        success = false;
    }

    // If any sound failed to load, print the error message
    if (!success) {
        std::cerr << "Error: One or more sounds failed to load." << std::endl;
    }
}
