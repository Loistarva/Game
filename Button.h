#ifndef BUTTON_H
#define BUTTON_H

#include <vector>

#include <SDL.h>

#include "Defs.h"
#include "graphics.h"

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

    void handleEvent(const SDL_Event& e, bool& quit, bool& Playing, bool& Menu);
    void update(bool& quit, bool& Playing, bool& Menu);
    void render(SDL_Renderer* renderer);
};



#endif

