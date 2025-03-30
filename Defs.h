#ifndef DEFS_H
#define DEFS_H

    static const int Gheight = 800;
    static const int Gwidth = 1240;
    const double FPS = 60;

    const int DeltaScore = 50;
    const int DeltaSpeed = 30;

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

// Define Background Pos

    const double LeftForestPosX = 0;
    const double LeftForestPosY = 50;
    const double LeftForestWidth = 274;
    const double LeftForestHeight = 661;

    const double RightForestPosX = Gwidth - 274;
    const double RightForestPosY = 70;
    const double RightForestWidth = 274;
    const double RightForestHeight = 661;

    const double LeftForestPosX0 = 0;
    const double LeftForestPosY0 = 270;
    const double LeftForestWidth0 = 530;
    const double LeftForestHeight0 = 1280;
    const double LeftForestTargetX = 530;
    const double LeftForestTargetY = 0;
    const double LeftForestTargetWidth = 340;
    const double LeftForestTargetHeight = 780;

    const double RightForestPosX0 = 260;
    const double RightForestPosY0 = 200;
    const double RightForestWidth0 = 520;
    const double RightForestHeight0 = 1150;
    const double RightForestTargetX = 0;
    const double RightForestTargetY = 0;
    const double RightForestTargetWidth = 260;
    const double RightForestTargetHeight = 570;

    const double SkyPosX = 0;
    const double SkyPosY = 0;
    const double SkyWidth = Gwidth;
    const double SkyHeight = 290;
    const double SkyCutWidth = 2480;
    const double SkyCutHeight = 580;

// Define Button Types

    const int PLAY_BUTTON = 0;
    const int STOP_BUTTON = 1;
    const int HOME_BUTTON = 2;
    const int EXIT_BUTTON = 3;

    const int ButtonCutWidth = 280;
    const int ButtonCutHeight = 170;

    const int ButtonWidthBig = 420;
    const int ButtonHeightBig = 255;

    const int ButtonWidthMedium = 336;
    const int ButtonHeightMedium = 204;

    const int ButtonWidthSmall = 112;
    const int ButtonHeightSmall = 68;

    const int ButtonMenuPosX = 720;
    const int ButtonMenuPosY1 = 150;
    const int ButtonMenuPosY2 = 450;

    const int ButtonPausePosX = 452;
    const int ButtonPausePosY1 = 150;
    const int ButtonPausePosY2 = 350;
    const int ButtonPausePosY3 = 550;

    const int ButtonOverPosX1 = 52;
    const int ButtonOverPosX2 = 452;
    const int ButtonOverPosX3 = 852;
    const int ButtonOverPosY = 500;

    const int ButtonStopPosX = 1050;
    const int ButtonStopPosY = -2;

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

    const int PlayerPosX0 = 0;
    const int PlayerPosX1 = 270;
    const int PlayerPosX2 = 550;
    const int PlayerPosX3 = 780;
    const int PlayerPosX4 = 1050;

    const int PlayerWidth = 150;
    const int PlayerHeight = 375;

    const int HeartPosX0 = 60;
    const int HeartPosY = 30;
    const int HeartWidth = 52;
    const int HeartHeight = 40;
    const int HeartGap = 55;

    const int Determination = 2;
    const int Brave = 3;

// Define Speed
    const double SPD0 = 2;

// Define Font
    const int scoreFontSize = 32;
    const int TitleSize = 128;
    const int TellScoreSize = 64;

#endif
