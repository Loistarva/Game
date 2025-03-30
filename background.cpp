#include <iostream>
#include <cmath>

#include "background.h"


double offsetX1 = LeftForestPosX0;
double offsetX2 = RightForestPosX0;
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

    offsetX1+=v;
    if(offsetX1>=LeftForestTargetX) offsetX1-=LeftForestTargetX;
    double t = (offsetX1 - LeftForestPosX0) / (LeftForestTargetX - LeftForestPosX0);
    double PosY = (1 - t) * LeftForestPosY0 + t * LeftForestTargetY;
    double Width = (1 - t) * LeftForestWidth0 + t * LeftForestTargetWidth;
    double Height = (1 - t) * LeftForestHeight0 + t * LeftForestTargetHeight;
    graphics.renderTexture(LeftForest, LeftForestPosX, LeftForestPosY, LeftForestWidth, LeftForestHeight, offsetX1, PosY, Width, Height);
}

void scrollingRightForest(const double v, Graphics graphics, SDL_Texture* RightForest) {

    offsetX2-=v/2;
    if(offsetX2<=RightForestTargetX) offsetX2+=RightForestPosX0;
    double t = (offsetX2 - RightForestPosX0) / (RightForestTargetX - RightForestPosX0);
    double PosY = (1 - t) * RightForestPosY0 + t * RightForestTargetY;
    double Width = (1 - t) * RightForestWidth0 + t * RightForestTargetWidth;
    double Height = (1 - t) * RightForestHeight0 + t * RightForestTargetHeight;
    graphics.renderTexture(RightForest, RightForestPosX, RightForestPosY, RightForestWidth, RightForestHeight, offsetX2, PosY, Width, Height);

}

void scrollingSky(Graphics graphics,SDL_Texture* Sky) {
    graphics.renderTexture(Sky, SkyPosX, SkyPosY, SkyWidth, SkyHeight,0, offsetSky, SkyCutWidth, SkyCutHeight);
    offsetSky+=0.2;
    if(offsetSky>=SkyCutHeight) offsetSky-=SkyCutHeight;
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


void renderPlayerAndEnemies(const std::vector<Enemy> &enemies,std::vector<SDL_Texture*> EnemiesV, Player &player, std::vector<SDL_Texture*> PlayerV, Graphics &graphics, int &HurtFrame, Background bg) {
    bool playerRendered = false;
    for (const auto& enemy : enemies) {
        if (!playerRendered && enemy.PosY > player.PosY + 100) {
            renderPlayer(graphics, player, PlayerV);
            playerRendered = true;
        }
        renderEnemy(graphics, enemy, EnemiesV);
    }
    if (!playerRendered) {
        renderPlayer(graphics, player, PlayerV);
    }
    if (HurtFrame > 0) {
        graphics.renderTexture(bg.BloodScreen, 0, 0);
        HurtFrame--;  // Giảm bộ đếm sau mỗi frame
    }
}


