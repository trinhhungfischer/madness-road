/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef SCREEN1VIEWBASE_HPP
#define SCREEN1VIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/ScalableImage.hpp>
#include <touchgfx/widgets/canvas/Circle.hpp>
#include <touchgfx/widgets/canvas/PainterRGB565.hpp>
#include <touchgfx/widgets/canvas/Line.hpp>
#include <touchgfx/containers/progress_indicators/TextProgress.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/widgets/ButtonWithLabel.hpp>

class Screen1ViewBase : public touchgfx::View<Screen1Presenter>
{
public:
    Screen1ViewBase();
    virtual ~Screen1ViewBase() {}
    virtual void setupScreen();

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box __background;
    touchgfx::Image background2;
    touchgfx::Image background1;
    touchgfx::ScalableImage car;
    touchgfx::Image obstacle_0;
    touchgfx::Image obstacle_1;
    touchgfx::Image obstacle_2;
    touchgfx::Image obstacle_3;
    touchgfx::Image obstacle_4;
    touchgfx::Image obstacle_5;
    touchgfx::Image obstacle_6;
    touchgfx::Image obstacle_7;
    touchgfx::Image obstacle_8;
    touchgfx::Image obstacle_9;
    touchgfx::Image obstacle_10;
    touchgfx::Image obstacle_11;
    touchgfx::Circle bullet3;
    touchgfx::PainterRGB565 bullet3Painter;
    touchgfx::Circle bullet2;
    touchgfx::PainterRGB565 bullet2Painter;
    touchgfx::Circle bullet1;
    touchgfx::PainterRGB565 bullet1Painter;
    touchgfx::Circle bullet0;
    touchgfx::PainterRGB565 bullet0Painter;
    touchgfx::Line line1;
    touchgfx::PainterRGB565 line1Painter;
    touchgfx::TextProgress textProgress1;
    touchgfx::TextAreaWithOneWildcard textArea1;
    touchgfx::TextAreaWithTwoWildcards textArea2;
    touchgfx::ButtonWithLabel exitButton;
    touchgfx::ButtonWithLabel retryButton;

private:

    /*
     * Callback Declarations
     */
    touchgfx::Callback<Screen1ViewBase, const touchgfx::AbstractButton&> buttonCallback;

    /*
     * Callback Handler Declarations
     */
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);

    /*
     * Canvas Buffer Size
     */
    static const uint16_t CANVAS_BUFFER_SIZE = 3600;
    uint8_t canvasBuffer[CANVAS_BUFFER_SIZE];
};

#endif // SCREEN1VIEWBASE_HPP
