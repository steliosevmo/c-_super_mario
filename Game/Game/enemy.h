#pragma once
#include "sgg/graphics.h"
#include "box.h"
#include "gameobject.h"


class Enemy : public GameObject, public Box {
	graphics::Brush brush;
	
	float speed;

	std::vector<std::string>m_sprites_enemy;//sprites for enemy's animation

	bool active = true;//checks if enemy is alive

	void moveEnemy(float dt);
public:
		Enemy(std::string name);
		~Enemy();

		void debugDraw();//draw method for debug mode
		
		float size; //enemy's size
		float enemy_pos_x, enemy_pos_y; //enemy's position

		void update(float dt) override;
		void draw() override;
		void init() override;
		bool isActive();//returns is enemy is alive
		
};


