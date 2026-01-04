#pragma once

// Include necessary headers
#include "gameobject.h"
#include "sgg/graphics.h"


// Menu class derived from GameObject
class EndPage : public GameObject {
    // Brushes for menu background and options
    graphics::Brush brush_background_EndPage;
    graphics::Brush brush_endPage;
    graphics::Brush brush_play;
    graphics::Brush brush_exit; 
   


public:
    EndPage();

    int scoreResult{0};//updated when the level ends
    int endHealth{ 0 };//updated when the level ends 

    
    void init() override;// Initialization method

    
    void draw() override;// End Page draw method 

   
    void update(float dt) override; // Update method for EndPage 
    

private:
    // Private members for display purposes
    int m_width;
    int m_height;
    int m_pos_x;
    int m_pos_y;
    
};