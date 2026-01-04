#include "enemy.h"
#include <sgg/graphics.h>
#include "GameState.h"
#include "box.h"
#define SETCOLOR(c,r,g,b){c[0]=r,c[1]=g,c[2]=b;}


void Enemy::moveEnemy(float dt){

	float delta_time = dt / 1000.0f;
	enemy_pos_x -= speed * delta_time;
	
	m_pos_x = enemy_pos_x;
	m_pos_y = enemy_pos_y;

	
}
void Enemy::update(float dt)
{
	moveEnemy(dt);

	if (enemy_pos_x < -m_state->m_global_offset_x) { //if enemy is out of bounds change enemy's state
		active = false;
	}

}

//draw enemy 
void Enemy::draw()
{
	int s = (int)fmodf(1000.0f - enemy_pos_x, m_sprites_enemy.size());
	brush.texture = m_sprites_enemy.at(s);
	graphics::drawRect(m_pos_x+m_state->m_global_offset_x, m_pos_y+m_state->m_global_offset_y, size, size, brush);
	if (m_state->m_debugging) {
		debugDraw();
	}
	
}
//initialize enemy's values 
void Enemy::init()
{
	speed= 4.f ;
	enemy_pos_y = 5.0f;
	size = 0.8f;
	m_pos_x = 5.0f;
	m_pos_y = 5.0f;
	m_height = size;
	m_width = size;
	
	brush.fill_opacity = 1.0f;
	brush.outline_opacity = 0.0f;
	m_sprites_enemy.push_back(m_state->getFullAssetPath("enemy1.png"));
	m_sprites_enemy.push_back(m_state->getFullAssetPath("enemy0.png"));
	m_sprites_enemy.push_back(m_state->getFullAssetPath("enemy5.png"));
}

bool Enemy::isActive()
{
	return active;
}


Enemy::Enemy(std::string name):GameObject(name) {
	init();
}


Enemy::~Enemy()
{
}

//draw enemy in debug mode 
void Enemy::debugDraw()
{

	graphics::Brush debug_brush;
	SETCOLOR(debug_brush.fill_color, 1, 0.3f, 0);
	SETCOLOR(debug_brush.outline_color, 1, 0.1f, 0);
	
	char s[20]; 
	sprintf_s(s, "(%.2f, %.2f)",
		m_pos_x,
		m_pos_y
		);
	SETCOLOR(debug_brush.fill_color, 1, 0, 0);
	debug_brush.fill_opacity = 1.0f;

	
	graphics::drawText(m_pos_x+m_state->m_global_offset_x - 0.4f,
		m_pos_y + m_state-> m_global_offset_y- 0.6f,
		0.15f, s, debug_brush);
	
	debug_brush.fill_opacity = 0.1f;
	debug_brush.outline_opacity = 1.0f;
	graphics::drawRect(m_pos_x+m_state->m_global_offset_x, m_pos_y+m_state->m_global_offset_y,m_width, m_height, debug_brush);
	
	
}



