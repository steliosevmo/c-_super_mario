#pragma once
#include "gameobject.h"
#include <sgg/graphics.h>
#include <list>
#include "player.h"
#include "enemy.h"
#include <vector>


class Level :public GameObject {
	graphics::Brush m_brush_background;

	graphics::Brush m_blocks_brush;      
	graphics::Brush m_blocks_brush_debug;
	const float m_block_size = 1.0f;
	std::vector<Box> m_blocks;
	std::vector<std::string>m_block_names;

	graphics::Brush m_blocks_brush_death;
	std::vector<Box> m_blocks_death; //invisible blocks that help with the fall damage
	
	Box* flag = new Box(150 * m_block_size, 4 * m_block_size, m_block_size, m_block_size * 5); //end level flag
	Enemy* enemy=nullptr;
	float enemy_pos_x;           //enemy initialization
	float enemy_pos_y{4.0f};
	float enemy_size = 0.8f;
	float enemy_speed = 7.5f;
	std::vector<std::string>m_sprites_enemy;
	graphics::Brush m_enemy_brush;

	const float m_gravity = 10.0f;


	float m_center_x = 5.0f;
	float m_center_y = 5.0f;
	

	void drawBlock(int i);
	void checkCollisions();
	void spawnEnemy();
	void deleteEnemy();
	void checkEnemy();
public:
	int score{0};
	Level(const std::string& name = "Level0");
	bool level_finished = false;
	void update(float dt) override;
	void init() override;
	void draw() override;
	~Level();
	
};
