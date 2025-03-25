#include "Button.h"

Button::Button(int ButtonType, int x, int y, int w, int h, SDL_Texture* texture): type(ButtonType), x(x), y(y), w(w), h(h), texture(texture), hovering(false), pressed(false), frameCounter(0) {
    for (int i=0; i<3; i++) {
        clips[i] = {i*w, 0, w, h}; // Cắt hình theo chiều ngang
    }
}

void Button::handleEvent(const SDL_Event& event, bool& quit, bool& Playing, bool& Menu) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    hovering = (mouseX >= x && mouseX <= x + w && mouseY >= y && mouseY <= y + h);

    if (event.type == SDL_MOUSEBUTTONDOWN && hovering) {
        pressed = true;
        frameCounter = 3; // Đếm ngược 3 frames

        switch (type) {
            case PLAY_BUTTON:
                Playing = true;
                Menu = false;
                break;
            case STOP_BUTTON:
                Playing = true;
                Menu = true;
                break;
            case HOME_BUTTON:
                Playing = false;
                Menu = true;
                break;
            case EXIT_BUTTON:
                quit = true;
                break;
        }
    }

}

void Button::update() {
    if (frameCounter > 0) {
        frameCounter--;
        if (frameCounter == 0) {
            pressed = false;
        }
    }
}

void Button::render(SDL_Renderer* renderer) {
    int state = pressed ? 2 : (hovering ? 1 : 0);
    SDL_Rect dstRect = { x, y, w, h };
    SDL_RenderCopy(renderer, texture, &clips[state], &dstRect);
}

