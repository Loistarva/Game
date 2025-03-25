#include "Enemy.h"
#include "Defs.h"

#include <iostream>
#include <vector>
#include <chrono>
#include <random>

#include <SDL.h>
#include <SDL_image.h>





std::vector<Enemy> enemies;
std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());

Enemy::Enemy(int _type) {
    type = _type;
    portrait = gen()%4;
    delayFrames = 10;
    switch (type) {
        case 0: StartX = EnemyPosX0; StartY = EnemyPosY0; targetX = EnemyTargetX0; targetY = EnemyTargetY0; break;
        case 1: StartX = EnemyPosX1; StartY = EnemyPosY1; targetX = EnemyTargetX1; targetY = EnemyTargetY1; break;
        case 2: StartX = EnemyPosX2; StartY = EnemyPosY2; targetX = EnemyTargetX2; targetY = EnemyTargetY2; break;
        case 3: StartX = EnemyPosX3; StartY = EnemyPosY3; targetX = EnemyTargetX3; targetY = EnemyTargetY3; break;
        case 4: StartX = EnemyPosX4; StartY = EnemyPosY4; targetX = EnemyTargetX4; targetY = EnemyTargetY4; break;
    }
    PosX = StartX;
    PosY = StartY;
    EWidth = EnemyWidth;
    EHeight = EnemyHeight;
}

void Enemy::move(double SPD) {
    if (delayFrames > 0) {
        delayFrames--;
        return;
    }

    if (PosY < targetY) PosY += SPD;

    double t = (PosY - StartY) / (targetY - StartY);
    PosX = (1 - t) * StartX + t * targetX;
    EWidth = (1 - t) * EnemyWidth + t * EnemyTargetW;
    EHeight = (1 - t) * EnemyHeight + t * EnemyTargetH;
}

bool Enemy::hasReachedTarget() const {
    return (PosY >= targetY);
}

void UpdateEnemies(long long Score, double SPD) {
    bool allReached = !enemies.empty();

    for (const auto& enemy : enemies) {
        if (!enemy.hasReachedTarget()) {
            allReached = false;
            break;
        }
    }

    if (enemies.empty() || allReached) {
        enemies.clear();

        int maxEnemies = std::min(static_cast<int>(Score / 2500), 4);

        if (Score <= 50000) {
            maxEnemies = std::min(maxEnemies, 3);
        }
        int minEnemies = 1;
        if (Score >= 100000) minEnemies = 3;
        if (Score >= 200000) minEnemies = 4;

        maxEnemies = std::max(maxEnemies, minEnemies);
        //maxEnemies = std::max(maxEnemies, 1); // Đảm bảo ít nhất 1 enemy
        for (int i = 0; i < maxEnemies; i++) {
            int newType = gen() % 5;
            enemies.emplace_back(newType);
        }
    }






    for (auto& enemy : enemies) {
        enemy.move(SPD);
    }
}

std::vector<SDL_Texture*> loadEnemies(Graphics &graphics) {
    return {
        graphics.loadTexture("imgs/Objs/Enemies/Ghost1.png"),
        graphics.loadTexture("imgs/Objs/Enemies/Ghost2.png"),
        graphics.loadTexture("imgs/Objs/Enemies/Ghost3.png"),
        graphics.loadTexture("imgs/Objs/Enemies/Ghost4.png"),
        graphics.loadTexture("imgs/Objs/Enemies/Ghost5.png")
    };
}

void renderEnemy(Graphics& graphics, Enemy enemy, std::vector<SDL_Texture*> enemiesVec) {
    graphics.renderTexture(enemiesVec[enemy.portrait],enemy.PosX,enemy.PosY,enemy.EWidth,enemy.EHeight);

}
