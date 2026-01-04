#include "Menu.h"
#include <iostream>
#include <chrono>
#include "GameState.h"
#define SETCOLOR(c,r,g,b){c[0]=r,c[1]=g,c[2]=b;}


Menu::Menu()
{
    // Initialize Menu as an active GameObject
    this->GameObject::setActive(true);

    // setup the menu sizes
    m_width = GameState::getInstance()->getCanvasWidth();
    m_height = GameState::getInstance()->getCanvasHeight();
    m_pos_x = GameState::getInstance()->getCanvasWidth() / 2.0f;
    m_pos_y = GameState::getInstance()->getCanvasHeight() / 2.0f;
}


void Menu::init() {
    // Set background texture and opacity
    brush_background_menu.texture = m_state->getFullAssetPath("menu.png");
    brush_background_menu.outline_opacity = 0.0f;
}


void Menu::draw() {
    // Draw the menu background
    graphics::drawRect(m_pos_x, m_pos_y, m_width, m_height, brush_background_menu);

    // Set font and draw the game title
    graphics::setFont(m_state->getFullAssetPath("bitstream.ttf"));
    SETCOLOR(brush_menu.fill_color, 0, 0, 0);
    graphics::drawText(1.5f, 1.0f, 0.6f, "SUPER MARIO", brush_menu);

    
    // Draw menu options (handled in GameState)
    graphics::drawText(1.7f, 3.f, 0.35,  "PRESS  ENTER  TO  START", brush_play);
    graphics::drawText(2.f, 3.6f, 0.35, "PRESS  ESC  TO  EXIT", brush_exit);

}

void Menu::update(float dt) {
    
    static std::chrono::steady_clock::time_point lastKeyPressTime = std::chrono::steady_clock::now();

    
    auto currentTime = std::chrono::steady_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastKeyPressTime).count();
    if (elapsedTime < 160) {
        return;
    }
  
}
