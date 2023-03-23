#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/canvas/Circle.hpp>


class Screen1View : public Screen1ViewBase
{
public:
    Screen1View();
    virtual ~Screen1View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    void handleTickEvent();
    bool checkCollide(int16_t x1, int16_t y1, int16_t w1, int16_t h1,
    		int16_t x2, int16_t y2, int16_t w2, int16_t h2);
    bool checkScorePoint(int16_t x1, int16_t y1, int16_t w1, int16_t h1,
    		int16_t x2, int16_t y2, int16_t w2, int16_t h2);
    bool checkOutMap(int16_t x1, int16_t y1, int16_t w1, int16_t h1);

    int randomNumberBetween(int lowest, int highest);

    // Temp varible
    touchgfx::Unicode::UnicodeChar testTextAreaBuffer1[10];
    touchgfx::Unicode::UnicodeChar testTextAreaBuffer2[10];
    touchgfx::Unicode::UnicodeChar testTextAreaBuffer3[10];
    touchgfx::Unicode::UnicodeChar testTextAreaBuffer4[10];

    // Variable
    uint32_t tickCount;

    // Car variable
    uint32_t carHPList[4] = {4, 5, 3, 7};
    uint32_t carSPDList[4] = {2, 3, 2, 2};
    uint32_t carBULList[4] = {4, 5, 7, 2};

    uint32_t currentHP;
    uint32_t maxHP;
    uint32_t speed;
    uint32_t point;
	uint32_t numBullet;

    // Spawn obstacle variable
    uint32_t spawnInterval;
    uint8_t numObstacleInPool = 12;
    Image *spawnImagePool[12] = {&obstacle_0, &obstacle_1, &obstacle_2, &obstacle_3, &obstacle_4, &obstacle_5,
			  &obstacle_6, &obstacle_7, &obstacle_8, &obstacle_9, &obstacle_10, &obstacle_11};
	uint8_t obstacleStatus[12] ={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int yObstaclePos[12] ={-40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40};

	int xObstcaleMoveStatus[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int yObstcaleStartChange[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int xObstcaleTarget[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	int xSpawnPoint[4] = {12, 78, 140, 200};

	// Background variable
	int yBackgroundPos;

	// Bullet variable
	uint32_t changeAxis = 1;
	const uint32_t reloadTime = 200;
	const uint32_t shotTime = 50;

	uint32_t lastReloadTime = 0;

	uint32_t lastShotTime = 50;
	uint32_t usedBullet = 0;
	Circle *bulletImagePool[4] = {&bullet0, &bullet1, &bullet2, &bullet3};
	uint8_t bulletStatus[4] ={0, 0, 0, 0};
	uint32_t bulletXAxis[4] = {0, 0, 0, 0};
	uint32_t bulletYAxis[4] = {0, 0, 0, 0};


	// Pseu-random variable here
	uint16_t randomList[100] = {756, 547, 931, 929, 519, 840, 771, 662, 546, 79, 268, 623, 421, 48, 958, 48, 429, 725, 257, 681, 747, 71, 668, 77, 598, 904, 465, 224, 10, 202, 490, 886, 777, 823, 523, 941, 619, 628, 991, 565, 790, 185, 320, 535, 449, 523, 929, 477, 46, 682, 217, 394, 81, 157, 357, 6, 856, 776, 428, 432, 663, 626, 968, 403, 136, 391, 95, 135, 97, 622, 427, 121, 545, 143, 883, 368, 210, 100, 754, 618, 870, 836, 960, 774, 978, 438, 253, 130, 653, 450, 313, 685, 950, 149, 158, 430, 684, 744, 216, 861};
	uint16_t randomIndex = 0;


	// Difficult array
	uint32_t numCheckPoint = 10;
	uint32_t checkPoint[10] = {100, 90, 80, 70, 60, 50, 40, 30, 20, 10};
	uint32_t checkPointFlag[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	uint32_t speedList[10] = {1, 1, 0, 0, 1, 0, 0, 1, 0, 0};
	uint32_t spawnIntervalList[10] = {40, 40, 40, 50, 60, 40, 60, 80, 80, 100};

protected:
};

#endif // SCREEN1VIEW_HPP
