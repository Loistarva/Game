#include "Button.h"

Button::Button(int ButtonType, int x, int y, int w, int h, SDL_Texture* texture): type(ButtonType), x(x), y(y), w(w), h(h), texture(texture), hovering(false), pressed(false), frameCounter(0) {
    for (int i=0; i<3; i++) {
        clips[i] = {i*280, 0, 280, 170}; // Cắt hình theo chiều ngang
    }
}

void Button::handleEvent(const SDL_Event& event, bool& quit, bool& Playing, bool& Menu) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    hovering = (mouseX >= x && mouseX <= x + w && mouseY >= y+h/2 && mouseY <= y + h);

    if (event.type == SDL_MOUSEBUTTONDOWN && hovering) {
        pressed = true;
        frameCounter = 12; // Đếm ngược 12 frames


        }
    }


void Button::update(bool& quit, bool& Playing, bool& Menu) {
    if (frameCounter > 0) {
        frameCounter--;
        if (frameCounter == 0) {
            switch (type) {
            case PLAY_BUTTON:
                Playing = true;
                Menu = false;
                break;
            case STOP_BUTTON:
                Playing = true;
                Menu = !Menu;
                break;
            case HOME_BUTTON:
                Playing = false;
                Menu = true;
                break;
            case EXIT_BUTTON:
                quit = true;
                break;
            }
            pressed = false;
            hovering = false;
        }

    }
}

void Button::render(SDL_Renderer* renderer) {
    int state = pressed ? 2 : (hovering ? 1 : 0);
    SDL_Rect dstRect = { x, y, w, h };
    SDL_RenderCopy(renderer, texture, &clips[state], &dstRect);
}

std::vector<SDL_Texture*> loadButton(Graphics &graphics) {
    return {
        graphics.loadTexture("imgs/Buttons/PlayButton.png"),
        graphics.loadTexture("imgs/Buttons/StopButton.png"),
        graphics.loadTexture("imgs/Buttons/HomeButton.png"),
        graphics.loadTexture("imgs/Buttons/ExitButton.png")
    };
}
