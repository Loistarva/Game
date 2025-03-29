#ifndef DEFS_H
#define DEFS_H

    static const int Gheight = 800;
    static const int Gwidth = 1240;
    const double FPS = 60;

// Define enemy type pos

    const double EnemyPosX0 = 300;
    const double EnemyTargetX0 = -120;
    const double EnemyPosY0 = 192;
    const double EnemyTargetY0 = 800;

    const double EnemyPosX1 = 440;
    const double EnemyTargetX1 = 218;
    const double EnemyPosY1 = 192;
    const double EnemyTargetY1 = 800;

    const double EnemyPosX2 = 565;
    const double EnemyTargetX2 = 530;
    const double EnemyPosY2 = 192;
    const double EnemyTargetY2 = 800;

    const double EnemyPosX3 = 690;
    const double EnemyTargetX3 = 838;
    const double EnemyPosY3 = 192;
    const double EnemyTargetY3 = 800;

    const double EnemyPosX4 = 820;
    const double EnemyTargetX4 = 1142;
    const double EnemyPosY4 = 192;
    const double EnemyTargetY4 = 800;


    const double EnemyWidth = 102.0;
    const double EnemyHeight = 93.0;
    const double EnemyTargetW = 170.0;
    const double EnemyTargetH = 155.0;

// Define Button Types

    const int PLAY_BUTTON = 0;
    const int STOP_BUTTON = 1;
    const int HOME_BUTTON = 2;
    const int EXIT_BUTTON = 3;

// Define Button Index in Vector

    const int playButtonMenu = 0;
    const int exitButtonMenu = 1;
    const int playButtonPause = 2;
    const int homeButtonPause = 3;
    const int exitButtonPause = 4;
    const int playButtonOver = 5;
    const int homeButtonOver = 6;
    const int exitButtonOver = 7;
    const int stopButtonPlaying = 8;

// Define Text and Button Texture Pos

    /// MenuKnight :
        const int menuKnightPosX = 80;
        const int menuKnightPosY = 200;
        const int menuKnightW = 500;
        const int menuKnightH = 500;

    /// Title :
        const int titlePosX = Gwidth / 2 - 550;
        const int titlePosY = 50;
        const int titleScale = 1;

    /// Game Paused :
        const int gamePausedPosX = 250;
        const int gamePausedPosY = 50;
        const int gamePausedScale = 1;

    /// Game Over :
        const int gameOverPosX = 270;
        const int gameOverPosY = 50;
        const int gameOverScale = 1;

    /// Your Score :
        const int yourScorePosX = 310;
        const int yourScorePosY = 200;
        const int yourScoreScale = 1;

    /// High Score :
        const int highScorePosX = 320;
        const int highScorePosY = 300;
        const int highScoreScale = 1;

    /// Congratulation :
        const int congratulationPosX = 200;
        const int congratulationPosY = 50;
        const int congratulationScale = 1;

    /// New High Score :
        const int NewHighPosX = 310;
        const int NewHighPosY = 200;
        const int NewHighScale = 1;

    /// Score text :
        const int ScoreTextPosX = Gwidth/2 - 380;
        const int ScoreTextPosY = 20;
        const int ScoreTextScale = 2;

    /// HighScorePlaying :
        const int highScorePlayingPosX = 700;
        const int highScorePlayingPosY = 40;
        const int highScorePlayingScale = 1;

// Define Player Pos
    const int PlayerPosY = 580;

#endif
