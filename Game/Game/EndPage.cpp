#include "EndPage.h"
#include <iostream>
#include <chrono>
#include "GameState.h"
#include "level.h"
#define SETCOLOR(c,r,g,b){c[0]=r,c[1]=g,c[2]=b;}



EndPage::EndPage()
{
    // Initialize Menu as an active GameObject
    this->GameObject::setActive(true);

    // setup the end page
    m_width = GameState::getInstance()->getCanvasWidth();
    m_height = GameState::getInstance()->getCanvasHeight();
    m_pos_x = GameState::getInstance()->getCanvasWidth() / 2.0f;
    m_pos_y = GameState::getInstance()->getCanvasHeight() / 2.0f;
}

void EndPage::init()
{
    // Set background texture and opacity
    brush_background_EndPage.texture = m_state->getFullAssetPath("menu.png");
    brush_background_EndPage.outline_opacity = 0.0f;
}

void EndPage::draw()
{
    graphics::drawRect(m_pos_x, m_pos_y, m_width, m_height, brush_background_EndPage);

    // draw the end Page based on the level outcome
    SETCOLOR(brush_endPage.fill_color, 0, 0, 0);
    graphics::drawText(1.5f, 1.0f, 0.6f, "SUPER MARIO", brush_endPage);

    if (endHealth<=0) {//player died scenario
        graphics::drawText(2.7f,1.5f, 0.35,"GAME OVER" , brush_play);
    }
    else {//player won senario
        graphics::drawText(2.7f, 1.5f, 0.35,"YOU  WON" , brush_play);
    }
    
    // draw EndPage options (handled in GameState)
    graphics::drawText(1.8f, 3.f, 0.35, "PRESS  M  TO  GO TO MENU", brush_play);
    std::string scoreText = "Score: " + std::to_string(scoreResult);
    graphics::drawText(2.9f, 2.f, 0.35, scoreText, brush_play);
    graphics::drawText(2.f, 3.6f, 0.35, "PRESS  ESC  TO  EXIT", brush_exit);
}

void EndPage::update(float dt)
{
  
}
