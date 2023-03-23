#ifndef MENUVIEW_HPP
#define MENUVIEW_HPP

#include <gui_generated/menu_screen/MenuViewBase.hpp>
#include <gui/menu_screen/MenuPresenter.hpp>

class MenuView : public MenuViewBase
{
public:
    MenuView();
    virtual ~MenuView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    void handleTickEvent();
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);

    // Variable
    uint32_t tickCount;

    const uint32_t numCar = 4;
    const uint32_t delay = 50;
    uint32_t lastFromDelay = 50;


    uint32_t carNameList[4] = {69, 96, 6996, 9669};
    uint32_t carHPList[4] = {4, 5, 3, 7};
    uint32_t carSPDList[4] = {2, 3, 2, 2};
    uint32_t carBULList[4] = {4, 5, 7, 2};

    // Temp
    touchgfx::Unicode::UnicodeChar testTextAreaBuffer0[40];
    touchgfx::Unicode::UnicodeChar testTextAreaBuffer1[20];
    touchgfx::Unicode::UnicodeChar testTextAreaBuffer2[10];
    touchgfx::Unicode::UnicodeChar testTextAreaBuffer3[10];
    touchgfx::Unicode::UnicodeChar testTextAreaBuffer4[10];

protected:
};

#endif // MENUVIEW_HPP
