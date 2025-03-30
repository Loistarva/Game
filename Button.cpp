#include "Button.h"

Button::Button(int ButtonType, int x, int y, int w, int h, SDL_Texture* texture): type(ButtonType), x(x), y(y), w(w), h(h), texture(texture), hovering(false), pressed(false), frameCounter(0) {
    for (int i=0; i<3; i++) {
        clips[i] = {i*ButtonCutWidth, 0, ButtonCutWidth, ButtonCutHeight}; // Cắt hình theo chiều ngang
    }
}

void Button::handleEvent(const SDL_Event& event,const bool& quit,const bool& Playing,const bool& Menu) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    hovering = (mouseX >= x && mouseX <= x + w && mouseY >= y+h/2 && mouseY <= y + h);

    if (event.type == SDL_MOUSEBUTTONDOWN && hovering) {
        pressed = true;
        Mix_PlayChannel(-1,Click,0);
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

void presentButtons(bool &quit, bool &playing, bool &menu, std::vector<Button> &buttons, Background bg, Graphics &graphics) {

    if (!playing && menu) {
        graphics.renderTexture(bg.menuKnight,menuKnightPosX, menuKnightPosY, menuKnightW, menuKnightH);

        buttons[playButtonMenu].render(graphics.renderer);
        buttons[exitButtonMenu].render(graphics.renderer);

        buttons[playButtonMenu].update(quit,playing,menu);
        buttons[exitButtonMenu].update(quit,playing,menu);
    } else if (playing && menu) {
        buttons[playButtonPause].render(graphics.renderer);
        buttons[homeButtonPause].render(graphics.renderer);
        buttons[exitButtonPause].render(graphics.renderer);

        buttons[playButtonPause].update(quit,playing,menu);
        buttons[homeButtonPause].update(quit,playing,menu);
        buttons[exitButtonPause].update(quit,playing,menu);
    } else if (!playing && !menu) {
        buttons[playButtonOver].render(graphics.renderer);
        buttons[homeButtonOver].render(graphics.renderer);
        buttons[exitButtonOver].render(graphics.renderer);

        buttons[playButtonOver].update(quit,playing,menu);
        buttons[homeButtonOver].update(quit,playing,menu);
        buttons[exitButtonOver].update(quit,playing,menu);
    } else {
        buttons[stopButtonPlaying].render(graphics.renderer);
        buttons[stopButtonPlaying].update(quit,playing,menu);
    }
}

void initButtons(std::vector<Button>& buttons, std::vector<SDL_Texture*>& buttonTexs) {
    // Menu chính
    buttons.emplace_back(PLAY_BUTTON, ButtonMenuPosX, ButtonMenuPosY1, ButtonWidthBig, ButtonHeightBig, buttonTexs[PLAY_BUTTON]);
    buttons.emplace_back(EXIT_BUTTON, ButtonMenuPosX, ButtonMenuPosY2, ButtonWidthBig, ButtonHeightBig, buttonTexs[EXIT_BUTTON]);

    // Pause Menu
    buttons.emplace_back(PLAY_BUTTON, ButtonPausePosX, ButtonPausePosY1, ButtonWidthMedium, ButtonHeightMedium, buttonTexs[PLAY_BUTTON]);
    buttons.emplace_back(HOME_BUTTON, ButtonPausePosX, ButtonPausePosY2, ButtonWidthMedium, ButtonHeightMedium, buttonTexs[HOME_BUTTON]);
    buttons.emplace_back(EXIT_BUTTON, ButtonPausePosX, ButtonPausePosY3, ButtonWidthMedium, ButtonHeightMedium, buttonTexs[EXIT_BUTTON]);

    // Game Over
    buttons.emplace_back(PLAY_BUTTON, ButtonOverPosX1, ButtonOverPosY, ButtonWidthMedium, ButtonHeightMedium, buttonTexs[PLAY_BUTTON]);
    buttons.emplace_back(HOME_BUTTON, ButtonOverPosX2, ButtonOverPosY, ButtonWidthMedium, ButtonHeightMedium, buttonTexs[HOME_BUTTON]);
    buttons.emplace_back(EXIT_BUTTON, ButtonOverPosX3, ButtonOverPosY, ButtonWidthMedium, ButtonHeightMedium, buttonTexs[EXIT_BUTTON]);

    // Playing Menu
    buttons.emplace_back(STOP_BUTTON, ButtonStopPosX, ButtonStopPosY, ButtonWidthSmall, ButtonHeightSmall, buttonTexs[STOP_BUTTON]);
}

