#include "Player.h"

#include <iostream>
#include <vector>

#include "Defs.h"
//#include "graphics.h"



int framesCount=0;

Player::Player(double startY) {
    lanes = { 0, 270, 550, 780, 1050 }; // Tọa độ X của 5 làn đường
    laneIndex = 2;
    Heart = 3;
    PosX = lanes[laneIndex];
    PosY = startY;
    PWidth = 150;
    PHeight = 375;
}

void Player::moveLeft() {
    if (laneIndex > 0 && !isChangingLane) {
        laneIndex--;
        startX = PosX;
        targetX = lanes[laneIndex];
        isChangingLane = true;
        laneChangeFrameCount = maxLaneChangeFrames;
    }
}

void Player::moveRight() {
    if (laneIndex < 4 && !isChangingLane) {
        laneIndex++;
        startX = PosX;
        targetX = lanes[laneIndex];
        isChangingLane = true;
        laneChangeFrameCount = maxLaneChangeFrames;
    }
}

void Player::update() {
    if (isChangingLane) {
        double t = 1.0 - (double)laneChangeFrameCount / maxLaneChangeFrames;
        PosX = startX + (targetX - startX) * t;

        laneChangeFrameCount--;
        if (laneChangeFrameCount <= 0) {
            isChangingLane = false;
            PosX = targetX;
        }
    }
}

bool Player::checkCollision(const std::vector<Enemy>& enemies) const {
    for (const auto& enemy : enemies) {
        if (enemy.type == laneIndex && enemy.PosY >= PosY && enemy.PosY < PosY + 100) {
            return true;
        }
    }
    return false;
}

void Player::reset() {
    laneIndex = 2; // Quay lại vị trí giữa
    Heart = 3;
    PosX = lanes[laneIndex];
    isChangingLane = false;
}


std::vector<SDL_Texture*> loadPlayer(Graphics& graphics) {
    return {
        graphics.loadTexture("imgs/Objs/Player/RunningPlayer1.png"),
        graphics.loadTexture("imgs/Objs/Player/RunningPlayer2.png"),
        graphics.loadTexture("imgs/Objs/Player/Determination.png"),
        graphics.loadTexture("imgs/Objs/Player/Brave.png")
    };
}

void renderPlayer(Graphics& graphics, Player& player, const std::vector<SDL_Texture*>& PlayerVec) {
    player.update();

    int TextureIndex = (framesCount/15) % 2;
    framesCount++;

    graphics.renderTexture(PlayerVec[TextureIndex],player.PosX,player.PosY,player.PWidth,player.PHeight);
    for(int i=0;i<player.Heart;i++) {
        graphics.renderTexture(PlayerVec[2],60+55*i,30,52,40);
    }
    for(int i=0;i<3;i++) {
        graphics.renderTexture(PlayerVec[3],60+55*i,30,52,40);
    }
}
