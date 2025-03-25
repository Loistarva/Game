#include "Player.h"

#include <iostream>
#include <vector>

#include "Defs.h"
#include "graphics.h"

using namespace std;

int framesCount=0;

Player::Player(double startY) {
    lanes = { 150, 200, 300, 400, 500 }; // Tọa độ X của 5 làn đường
    laneIndex = 2;
    PosX = lanes[laneIndex];
    PosY = startY;
    PWidth = 180;
    PHeight = 450;
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

vector<SDL_Texture*> loadPlayer(Graphics& graphics) {
    return {
        graphics.loadTexture("imgs/Objs/Player/RunningPlayer1"),
        graphics.loadTexture("imgs/Objs/Player/RunningPlayer2")
    };
}

void renderPlayer(Graphics graphics,Player player,vector<SDL_Texture*> PlayerVec) {
    int TextureIndex = (framesCount/10) % PlayerVec.size();
    graphics.renderTexture(PlayerVec[TextureIndex],player.PosX,player.PosY,player.PWidth,player.PHeight);
}
