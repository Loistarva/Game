#ifndef BUTTON_H
#define BUTTON_H

#include <vector>

#include <SDL.h>
#include <SDL_mixer.h>

#include "background.h"
#include "Defs.h"
#include "graphics.h"
#include "Media.h"



std::vector<SDL_Texture*> loadButton(Graphics &graphics);

struct Button {
    int x, y, w, h;     // Vị trí và kích thước
    int type;           // Thể Hiện Loại Nút
    bool hovering;      // Trạng thái hover
    bool pressed;       // Trạng thái pressed
    int frameCounter;   // Đếm số frame để thay đổi trạng thái
    SDL_Texture* texture; // Ảnh của button
    SDL_Rect clips[3];   // Phần cắt từ texture để hiển thị

    Button(int ButtonType, int x, int y, int w, int h, SDL_Texture* texture);

    void handleEvent(const SDL_Event& e,const bool& quit,const bool& Playing,const bool& Menu);
    void update(bool& quit, bool& Playing, bool& Menu);
    void render(SDL_Renderer* renderer);
};

void presentButtons(bool &quit, bool &playing, bool &menu, std::vector<Button> &buttons, Background bg, Graphics &graphics);

void initButtons(std::vector<Button>& buttons, std::vector<SDL_Texture*>& buttonTexs);

#endif

