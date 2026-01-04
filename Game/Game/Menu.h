#pragma once

#include "gameobject.h"
#include "sgg/graphics.h"


class Menu : public GameObject {
    // Brushes for menu background and options
    graphics::Brush brush_background_menu;
    graphics::Brush brush_menu;
    graphics::Brush brush_play;
    graphics::Brush brush_exit;
    
public:
    
    Menu();

    
    void init() override;// Initialization method

    
    void draw() override;//Menu draw method  

    
    void update(float dt) override;// Update method for menu page


private:
    // Private members for display purposes
    int m_width;
    int m_height;
    int m_pos_x;
    int m_pos_y;
};