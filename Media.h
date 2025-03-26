#ifndef MEDIA_H
#define MEDIA_H

#include <SDL_mixer.h>
#include <string>

// Định nghĩa các biến âm thanh toàn cục

extern Mix_Music* MenuMusic ;    // Nhạc nền menu
extern Mix_Music* LowScore ;
extern Mix_Music* MediumScore ;
extern Mix_Music* MHighScore ;
extern Mix_Music* Champion ;
extern Mix_Music* YouTried ;

extern Mix_Chunk* Click ;
extern Mix_Chunk* GetHit ;

void InitMedia();

#endif // MEDIA_H

