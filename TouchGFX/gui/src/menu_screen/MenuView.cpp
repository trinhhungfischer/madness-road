#include <gui/menu_screen/MenuView.hpp>
#include <cmsis_os.h>

extern osMessageQueueId_t Queue1Handle;
extern osMessageQueueId_t Queue2Handle;
extern int32_t curCar;
extern uint32_t highScore;

MenuView::MenuView()
{
	tickCount = 0;
}

void MenuView::setupScreen()
{
    MenuViewBase::setupScreen();
}

void MenuView::tearDownScreen()
{
    MenuViewBase::tearDownScreen();
}

void MenuView::handleTickEvent()
{
	uint8_t res=0;
	uint32_t count=osMessageQueueGetCount(Queue1Handle);
	if ((count>0) && (lastFromDelay>delay)){
		osMessageQueueGet(Queue1Handle,&res,NULL,osWaitForever);
		//khi interupt pc11 re trai
		if (res=='R'){
			lastFromDelay = 0;
			curCar = (curCar + 1);
		}

		//interupt pc13 re phai
		if (res=='L'){
			lastFromDelay = 0;
			curCar = (curCar - 1);
		}

	}

	uint32_t count_2=osMessageQueueGetCount(Queue2Handle);
	if (count_2 < 2) {
		int32_t x = curCar;
		osMessageQueuePut(Queue2Handle,&x,0,10);
	}


	if (lastFromDelay <= delay) {
		lastFromDelay += 1;
	}
	Unicode::snprintf(testTextAreaBuffer0, 10, "%d", highScore);
	textArea2.setWildcard(testTextAreaBuffer0);
	textArea2.resizeToCurrentText();

	Unicode::snprintf(testTextAreaBuffer1, 10, "%d", carNameList[curCar % numCar]);
	carName.setWildcard(testTextAreaBuffer1);
	carName.resizeToCurrentText();

	Unicode::snprintf(testTextAreaBuffer2, 10, "%d", carHPList[curCar % numCar]);
	HP.setWildcard(testTextAreaBuffer2);
	HP.resizeToCurrentText();

	Unicode::snprintf(testTextAreaBuffer3, 10, "%d", carSPDList[curCar % numCar]);
	SPD.setWildcard(testTextAreaBuffer3);
	SPD.resizeToCurrentText();

	Unicode::snprintf(testTextAreaBuffer4, 10, "%d", carBULList[curCar % numCar]);
	BUL.setWildcard(testTextAreaBuffer4);
	BUL.resizeToCurrentText();

	tickCount+=1;

	invalidate();
}


