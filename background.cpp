#include <iostream>
#include <cmath>

#include <SDL.h>
#include <SDL_image.h>

#include "graphics.h"
#include "Defs.h"
#include "background.h"



double offsetX1 = 0;
double offsetX2 = 0;
double offsetSky = 0;
long long Ground = 0;


Background loadBackground(Graphics &graphics) {
    return {
        graphics.loadTexture("imgs/background/LeftForestFixed2.png"),
        graphics.loadTexture("imgs/background/RightForest.png"),
        graphics.loadTexture("imgs/background/Top_2.png"),
        graphics.loadTexture("imgs/background/SKY.png"),
        graphics.loadTexture("imgs/background/Blur.png"),
        graphics.loadTexture("imgs/background/MenuKnight.png"),
        graphics.loadTexture("imgs/background/BloodScreen.png")
    };
}

std::vector<SDL_Texture*> loadGroundTextures(Graphics &graphics) {
    return {
        graphics.loadTexture("imgs/background/ground1.png"),
        graphics.loadTexture("imgs/background/ground2.png"),
        graphics.loadTexture("imgs/background/ground3.png"),
        graphics.loadTexture("imgs/background/ground4.png"),
        graphics.loadTexture("imgs/background/ground5.png"),
        graphics.loadTexture("imgs/background/ground6.png")
    };
}

void renderBackground(Graphics &graphics, Background &bg, double speed, const std::vector<SDL_Texture*> &GroundV) {
    scrollingSky(graphics, bg.sky);
    scrollingGround(graphics, GroundV, speed);
    scrollingLeftForest(speed, graphics, bg.leftForest);
    scrollingRightForest(speed, graphics, bg.rightForest);
    graphics.renderTexture(bg.top, 0, 0);
    graphics.renderTexture(bg.blur, 0, 0);
}




void scrollingLeftForest(const double v, Graphics graphics, SDL_Texture* LeftForest) {

    graphics.renderTexture(LeftForest, 0, 50, 274, 661, offsetX1, (14310-27*offsetX1)/53.0, 530-19*offsetX1/53.0, 1280-50*offsetX1/53.0);
    offsetX1+=v;
    offsetX1+=(530-offsetX1)*0.001;
    if(offsetX1>=530.0) offsetX1-=530.0;
}

void scrollingRightForest(const double v, Graphics graphics, SDL_Texture* RightForest) {
    graphics.renderTexture(RightForest, Gwidth-274, 70, 274, 661, -offsetX2/2+260, -5.0/13*offsetX2+200, -offsetX2/2 +520,-57.0/52*offsetX2+1140);
    offsetX2+=v;
    offsetX2+=(520-offsetX2)*0.001;
    if(offsetX2>=520.0) offsetX2-=520.0;
}

void scrollingSky(Graphics graphics,SDL_Texture* Sky) {
    graphics.renderTexture(Sky,0,0,Gwidth,290,0,offsetSky,2480,580);
    offsetSky+=0.2;
    if(offsetSky>=580) offsetSky-=580;
}

void scrollingGround(Graphics graphics, std::vector<SDL_Texture*> ground, double v) {
    static int frameCounter = 0; // Biến đếm số frame đã qua
    static long long groundIndex = 0; // Lưu chỉ mục của Ground hiện tại

    graphics.renderTexture(ground[groundIndex % 6], 0, 0, Gwidth, Gheight);

    frameCounter++;
    if (frameCounter >= 80.0 / v) {
        frameCounter = 0; // Reset đếm frame
        groundIndex++; // Chuyển sang ảnh ground tiếp theo
    }
}


