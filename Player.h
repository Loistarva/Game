#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>

#include "graphics.h"
#include "Enemy.h"

struct Player {
    int Heart;
    double PosX, PosY; // Vị trí hiện tại
    double PWidth, PHeight; // Kích thước Player
    int laneIndex; // Chỉ số làn đường (0-4)

    bool isChangingLane;
    int laneChangeFrameCount;
    static constexpr int maxLaneChangeFrames = 5;
    double startX, targetX;

    std::vector<double> lanes; // Danh sách vị trí X của các làn đường

    Player(double startY);

    void moveLeft();
    void moveRight();

    void update();

    bool checkCollision(const std::vector<Enemy>& enemies) const;

    void reset();
};

std::vector<SDL_Texture*> loadPlayer(Graphics& graphics);

void renderPlayer(Graphics& graphics, Player& player, const std::vector<SDL_Texture*>& PlayerVec);

#endif // PLAYER_H

