#include "Player.h"

#include <iostream>
#include <vector>

#include "Defs.h"
//#include "graphics.h"



int framesCount=0;

Player::Player(double startY) {
    lanes = { 0, 300, 550, 780, 1050 }; // Tọa độ X của 5 làn đường
    laneIndex = 2;
    PosX = lanes[laneIndex];
    PosY = startY;
    PWidth = 150;
    PHeight = 375;
}

void Player::moveLeft() {
    if (laneIndex > 0) {
        laneIndex--;
        PosX = lanes[laneIndex];
    }
}

void Player::moveRight() {
    if (laneIndex < 4) {
        laneIndex++;
        PosX = lanes[laneIndex];
    }
}

bool Player::checkCollision(const std::vector<Enemy>& enemies) const {
    for (const auto& enemy : enemies) {
        if (enemy.type == laneIndex && enemy.PosY >= PosY) {
            return true;
        }
    }
    return false;
}

std::vector<SDL_Texture*> loadPlayer(Graphics& graphics) {
    return {
        graphics.loadTexture("imgs/Objs/Player/RunningPlayer1.png"),
        graphics.loadTexture("imgs/Objs/Player/RunningPlayer2.png")
    };
}

void renderPlayer(Graphics& graphics, const Player& player, const std::vector<SDL_Texture*>& PlayerVec) {
    int TextureIndex = (framesCount/15) % PlayerVec.size();
    framesCount++;
    graphics.renderTexture(PlayerVec[TextureIndex],player.PosX,player.PosY,player.PWidth,player.PHeight);
}
