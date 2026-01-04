#pragma once
#include <string>
#include <sgg/graphics.h>
#include "enemy.h"
class GameState {
private:
	std::string m_asset_path = "assets\\"; //asset path
	float m_canvas_width = 8.0f;
	float m_canvas_height = 8.0f;

	static GameState* m_unique_instance;
	
	GameState();
	class Menu* m_menu = 0;
	class Player* m_player = 0;
	class Enemy* m_enemy = 0;
	class EndPage* m_endPage = 0;
	class Level* m_current_level = 0;
public:
	float m_global_offset_x = 0.0f; //offsets to handle each object's movement
	float m_global_offset_y = 0.0f;
	bool m_debugging = false; 
	
	void init();
	void draw();
	void update(float dt);

	static GameState* getInstance();
	~GameState();

	float getCanvasWidth() {
		return m_canvas_width;
	}
	float getCanvasHeight() {
		return m_canvas_height;
	}

	std::string getAssetDir();
	std::string getFullAssetPath(const std::string& asset);

	void switchToMenu(); //helps switching to menu

	class Player* getPlayer() {
		return m_player;
	}
	class Enemy* getEnemy() {
		return m_enemy;
	}
	
};
