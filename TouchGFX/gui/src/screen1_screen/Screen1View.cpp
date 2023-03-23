//Nhóm 10
//Lê Quốc Hưng
//Trịnh Quang Hùng
//Bùi Ngọc Tân
//Nghiêm Việt Thắng
#include <gui/screen1_screen/Screen1View.hpp>
#include <cmsis_os.h>
#include <stdlib.h>
#include <touchgfx/Color.hpp>
#include <touchgfx/TypedText.hpp>
#include <stm32f4xx_hal.h>

extern osMessageQueueId_t Queue1Handle;
extern osMessageQueueId_t Queue2Handle;
extern int32_t curCar;
extern uint32_t highScore;

Screen1View::Screen1View()
{
	randomIndex = (curCar + 971) % 93;
	curCar = curCar % 4;

	tickCount = 0;
	point = 0;

	maxHP = carHPList[curCar];
	currentHP = maxHP;
	speed = carSPDList[curCar];
	numBullet = carBULList[curCar];

	spawnInterval = 100;
	yBackgroundPos = 0;
}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}


void Screen1View::handleTickEvent()
{
	// Declare index variable
	int32_t i1 = 0;
	int32_t i2 = 0;
	int16_t addPoint = 0;

	Screen1ViewBase::handleTickEvent();



	// 1. Spawn obstacle
	if (tickCount % spawnInterval == 0) {

		int r = Screen1View::randomNumberBetween(0, 7) % 4;
		for (i1 = 0; i1 < 12; i1 ++) {
			if (obstacleStatus[i1] == 0) {

				obstacleStatus[i1] = 1;
				(*(spawnImagePool[i1])).setX(xSpawnPoint[r]);
				(*(spawnImagePool[i1])).setY(-40);
				yObstaclePos[i1] = -40;
				int r1 = Screen1View::randomNumberBetween(0, 99) % 10;
				// Con cu co the di chuyen sang phai
				if (r1 < 5) {
					int r2 = r;
					while (r2 == r) {
						r2 = Screen1View::randomNumberBetween(0, 99) % 4;
					}
					xObstcaleMoveStatus[i1] = 1;
					xObstcaleTarget[i1] = xSpawnPoint[r2];
					int r3 = Screen1View::randomNumberBetween(0, 1000) % 160;
					yObstcaleStartChange[i1] = r3;
				}
				break;

			}
		}

	}

	// 2. Check dan da ra ngoai map
	for (i1=0;i1<4;i1++) {
		if (bulletStatus[i1]==1) {
			bool isOutMap = Screen1View::checkOutMap((*bulletImagePool[i1]).getX(),(*bulletImagePool[i1]).getY(),
					(*bulletImagePool[i1]).getWidth(),(*bulletImagePool[i1]).getHeight());

			if (isOutMap) {
				bulletStatus[i1]=3;
			}
		}
	}

	// 3. Check va cham hoac ghi diem cua obstacle
	for (i1=0; i1<12; i1++) {
		for (i2=0;i2<4;i2++) {
			if (bulletStatus[i2]==1) {
				// TODO: check va cham voi dan tai day
				bool isHitBullet = Screen1View::checkCollide((*bulletImagePool[i2]).getX(),(*bulletImagePool[i2]).getY(),
						(*bulletImagePool[i2]).getWidth(),(*bulletImagePool[i2]).getHeight(),
						(*(spawnImagePool[i1])).getX(), (*(spawnImagePool[i1])).getY(),
						(*(spawnImagePool[i1])).getWidth(), (*(spawnImagePool[i1])).getHeight());

				if (isHitBullet) {
					bulletStatus[i1]=2;
					obstacleStatus[i1]=5;
				}
			}
		}


		if (obstacleStatus[i1] == 1 ) {
			// TODO: check va cham voi xe tai day
			bool isHitCar = Screen1View::checkCollide(car.getX(), car.getY(), car.getWidth(), car.getHeight(),
					(*(spawnImagePool[i1])).getX(), (*(spawnImagePool[i1])).getY(), (*(spawnImagePool[i1])).getWidth(), (*(spawnImagePool[i1])).getHeight());

			if (isHitCar) {
				obstacleStatus[i1] = 3;
			}

			bool isScorePoint = Screen1View::checkScorePoint(car.getX(), car.getY(), car.getWidth(), car.getHeight(),
								(*(spawnImagePool[i1])).getX(), (*(spawnImagePool[i1])).getY(), (*(spawnImagePool[i1])).getWidth(), (*(spawnImagePool[i1])).getHeight());

			if (isScorePoint) {
				obstacleStatus[i1] = 2;
			}
		}
	}



	// 4. Duyet lai toan bo status cua obstacle
	for (i1=0; i1<12; i1++) {
		if (obstacleStatus[i1] == 3) {
			// TODO: set lai vat can va cham len tren man hinh
			(*(spawnImagePool[i1])).setY(-40);
			yObstaclePos[i1] = -40;
			obstacleStatus[i1] = 0;

			// TODO: logic va cham o day
			currentHP -= 1;
			point += 1;
			xObstcaleMoveStatus[i1] = 0;

		}

		if (obstacleStatus[i1] == 5) {
			// TODO: set lai vat can va cham len tren man hinh
			(*(spawnImagePool[i1])).setY(-40);
			yObstaclePos[i1] = -40;
			obstacleStatus[i1] = 0;

			// TODO: logic va cham o day
			point += 1;
			xObstcaleMoveStatus[i1] = 0;
		}
	}

	// 5. Duyet lai toan bo status cua bullet
	for (i1=0; i1<4; i1++) {
		if (bulletStatus[i1] == 2 || bulletStatus[i1] == 3) {
			// TODO: set lai dan da va cham hoac ra ngoai man hinh
			(*(bulletImagePool[i1])).setX(320);
			(*(bulletImagePool[i1])).setY(283);
			bulletStatus[i1] = 0;
		}
	}


	// 6. Check diem tang nho vuot obstacle
	for (i1=0; i1<12; i1++) {
		if (obstacleStatus[i1] == 2) {
			addPoint += 1;
			obstacleStatus[i1] = 4;
		}
	}
	point += addPoint;

	// 7. Logic tam ngam thay doi
	uint32_t startX;
	uint32_t startY;
	uint32_t endX;
	uint32_t endY;

	line1.getStart(startX, startY);
	line1.getEnd(endX, endY);

	if (endX < 60 && endX > 0) {
		endX += changeAxis;
	} else if (endX == 60) {
		changeAxis = -1;
		endX += changeAxis;
	} else if (endX == 0) {
		changeAxis = 1;
		endX += changeAxis;
	}
	line1.setEnd(endX, endY);



	// 8. Logic car di chuyen va ban dan

	//set duong dua chay vo han
	yBackgroundPos = (yBackgroundPos + speed) % 320;
	background1.setY(yBackgroundPos % 320 - 320);
	background2.setY(yBackgroundPos % 320);

	uint8_t res=0;
	uint32_t count=osMessageQueueGetCount(Queue1Handle);
	if (count>0){
		osMessageQueueGet(Queue1Handle,&res,NULL,osWaitForever);
		//khi interupt pc11 re trai
		if (res=='R'){

			int16_t x1=car.getX();
			int16_t x2=line1.getX();

			if (x1 < 203){
				x1 += 2 * speed;
				x2 += 2 * speed;
			}
			car.setX(x1);
			line1.setX(x2);
		}

		//interupt pc13 re phai
		if (res=='L'){
			int16_t x1=car.getX();
			int16_t x2=line1.getX();
			if (x1 >0){
				x1 -= 2 * speed;
				x2 -= 2 * speed;
			}
			car.setX(x1);
			line1.setX(x2);
		}


		//interupt pc0  hay USER BUTTON ban dan
		if (res=='J') {
			for (i1=0;i1<4;i1++) {
				if (bulletStatus[i1] == 0 && usedBullet < numBullet && lastShotTime > shotTime) {
					lastShotTime = 0;
					bulletStatus[i1] = 1;
					bulletXAxis[i1] = endX - startX;
					bulletYAxis[i1] = endY - startY;
					(*bulletImagePool[i1]).setX(line1.getX() + 30);
					usedBullet += 1;
					break;
				}
			}
		}
	}

	// 9. Logic di chuyen cua obstacle
	for (i1=0; i1<12; i1++) {
		if (obstacleStatus[i1] == 1 || obstacleStatus[i1] == 2 || obstacleStatus[i1] == 4) {

			yObstaclePos[i1] += speed;
			(*(spawnImagePool[i1])).setY(yObstaclePos[i1]);
			if (yObstaclePos[i1] >= 320) {
				obstacleStatus[i1] = 0;
				xObstcaleMoveStatus[i1] = 0;
			}

			if (xObstcaleMoveStatus[i1] == 1 && yObstaclePos[i1] > yObstcaleStartChange[i1]) {
				int x = (*(spawnImagePool[i1])).getX();
				if (x > xObstcaleTarget[1]) {
					x -= speed;
				} else if (x < xObstcaleTarget[1]) {
					x += speed;
				}
				(*(spawnImagePool[i1])).setX(x);
			}
		}
	}

	// 10. Logic di chuyen cua bullet
	if (lastShotTime <= shotTime) {
		lastShotTime += 1;
	}

	if (usedBullet > 0) {
		if (lastReloadTime + 1 > reloadTime) {
			lastReloadTime = 0;
			usedBullet -= 1;
		}
		lastReloadTime += 1;

	}
	for (i1=0; i1<4; i1++) {
		if (bulletStatus[i1] == 1) {
			int32_t x = (*bulletImagePool[i1]).getX();
			int32_t y = (*bulletImagePool[i1]).getY();

			x += bulletXAxis[i1] / 4;
			y += bulletYAxis[i1] / 4;

			(*bulletImagePool[i1]).setX(x);
			(*bulletImagePool[i1]).setY(y);

		}
	}

	// 11. Logic tang do kho cho game

	for (i1=0;i1<numCheckPoint;i1++){
		if ((point >= checkPoint[i1]) && (checkPointFlag[i1] == 0)) {
			speed += speedList[i1];
			spawnInterval = spawnIntervalList[i1];
			checkPointFlag[i1] = 1;
			break;
		}
	}


	// 12. Logic set lai cac doi tuong UI
	Unicode::snprintf(testTextAreaBuffer1, 10, "%d", point);
	textArea1.setWildcard(testTextAreaBuffer1);
	textArea1.resizeToCurrentText();
	if (point > highScore) {
		textArea1.setColor(touchgfx::Color::getColorFromRGB(255,0,0));
	} else if (point + 10 > highScore) {
		textArea1.setColor(touchgfx::Color::getColorFromRGB(255,255,0));
	}

	if (lastShotTime <= shotTime) {
		textArea2.setColor(touchgfx::Color::getColorFromRGB(255,0,0));
	} else {
		textArea2.setColor(touchgfx::Color::getColorFromRGB(0,255,0));
		if (usedBullet == 4) {
			textArea2.setColor(touchgfx::Color::getColorFromRGB(255,0,0));
		}
	}

	Unicode::snprintf(testTextAreaBuffer2, 10, "%d", numBullet - usedBullet);
	textArea2.setWildcard1(testTextAreaBuffer2);

	Unicode::snprintf(testTextAreaBuffer3, 10, "%d", numBullet);
	textArea2.setWildcard2(testTextAreaBuffer3);

	textArea2.resizeToCurrentText();

	if (currentHP == 0) {
		speed = 0;
		retryButton.setY(100);
		exitButton.setY(170);
		if (point > highScore) {
			highScore = point;
		}
	}

	uint32_t percentHP = currentHP * 100 / maxHP;
	if (percentHP > 50) {
		textProgress1.setColor(touchgfx::Color::getColorFromRGB(0,255,0));
	}
	else if (percentHP >= 25) {
		textProgress1.setColor(touchgfx::Color::getColorFromRGB(255,255,0));
	}

	if (currentHP == 1) {
		textProgress1.setColor(touchgfx::Color::getColorFromRGB(255,0,0));
	}

	textProgress1.setValue(percentHP);

	// 12. Ket thuc mot tick
	tickCount+=1;

	invalidate();
}

bool Screen1View::checkCollide(int16_t x1, int16_t y1, int16_t w1, int16_t h1,
		int16_t x2, int16_t y2, int16_t w2, int16_t h2) {

	if ((x1 + w1 < x2) || (x1 > x2 + w2)) {
		return false;
	}

	if ((y1 + h1 < y2) || (y1 > y2 + h2)) {
		return false;
	}
	return true;
}

/*
 * x1, y1, w1, h1 la car
 * x2, y2, w2, h2 la obstacle
 *
 */
bool Screen1View::checkScorePoint(int16_t x1, int16_t y1, int16_t w1, int16_t h1,
		int16_t x2, int16_t y2, int16_t w2, int16_t h2) {

	if (y1 + h1 < y2) {
		return true;
	}
	return false;
}


bool Screen1View::checkOutMap(int16_t x1, int16_t y1, int16_t w1, int16_t h1) {
	if ((x1 + w1 < 0) || x1 > 240)
		return true;
	if ((y1 + h1 < 0) || y1 > 320)
		return true;

	return false;
}


int Screen1View::randomNumberBetween(int lowest, int highest)
   {
       uint32_t random = randomList[randomIndex];
       randomIndex += 1;
       return lowest + (random % (highest - lowest));
   }
