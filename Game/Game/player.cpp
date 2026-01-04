#include "player.h"
#include <sgg/graphics.h>
#include "GameState.h"
#include "enemy.h"
#define SETCOLOR(c,r,g,b){c[0]=r,c[1]=g,c[2]=b;}

void Player::movePlayer(float dt)
{
	float delta_time = dt / 1000.0f;            //move player with A and D
	float move = 0.0f;
	if (graphics::getKeyState(graphics::SCANCODE_A)) {
		
		move -= 1.0f;
		
	}
	if (graphics::getKeyState(graphics::SCANCODE_D)) {
	
		move += 1.0f;

	}


	//x
	m_vx =std::min(m_max_velocity, m_vx + delta_time * move * m_accel_horizontal);
	m_vx = std::max(-m_max_velocity, m_vx);
	m_vx -= 0.2f*m_vx/(0.1f+fabs(m_vx));

	if (fabs(m_vx) < 0.01f) {
		m_vx = 0.0f;
	}

	m_pos_x += delta_time * m_vx;
	//y
	if (m_vy == 0.0f) {
		m_vy -= graphics::getKeyState(graphics::SCANCODE_W) ? m_accel_vertical : 0.0f;
		
	}//player's jump
	m_vy += delta_time * m_gravity;

	m_pos_y += m_vy * delta_time;

}

void Player::update(float dt)
{
	movePlayer(dt);
	
	m_state->m_global_offset_x = m_state->getCanvasWidth() / 2.0f - m_pos_x;
	m_state->m_global_offset_y = m_state->getCanvasHeight() / 2.0f - m_pos_y;

	GameObject::update(dt);
}

void Player::init()
{
	m_pos_x = 5.0f;
	m_pos_y = 5.0f;
	m_width /= 2.f;   
	m_height /= 1.1f;

	m_state->m_global_offset_x = m_state->getCanvasWidth() / 2.0f - m_pos_x;
	m_state->m_global_offset_y = m_state->getCanvasHeight() / 2.0f - m_pos_y;

	m_brush_player.fill_opacity = 1.0f;
	m_brush_player.outline_opacity = 0.0f;
	

	m_sprites.push_back(m_state->getFullAssetPath("marios0.png"));
	m_sprites.push_back(m_state->getFullAssetPath("marios1.png"));
	m_sprites.push_back(m_state->getFullAssetPath("marios2.png"));
}

void Player::draw()
{
	int s = (int)fmodf(1000.0f-m_pos_x,m_sprites.size());
	m_brush_player.texture = m_sprites.at(s);
	//player's sprites change according to his movement
	if (graphics::getKeyState(graphics::SCANCODE_A)) {
		graphics::setScale(-1.0f, 1.0f);
	}
	graphics::drawRect(m_state->getCanvasWidth() * 0.5f, m_state->getCanvasHeight() * 0.5f, 1.f, 1.f, m_brush_player);
	graphics::resetPose();
	if (m_state->m_debugging) {
		debugDraw();
	}
}

void Player::debugDraw()
{
	graphics::Brush debug_brush;
	SETCOLOR(debug_brush.fill_color, 1, 0.3f, 0);
	SETCOLOR(debug_brush.outline_color, 1, 0.1f, 0);
	debug_brush.fill_opacity = 0.1f;
	debug_brush.outline_opacity = 1.0f;
	graphics::drawRect(m_state->getCanvasWidth() * 0.5f, m_state->getCanvasHeight() * 0.5f, m_width, m_height, debug_brush);

	char s[20];
	sprintf_s(s, "(%5.2f,%5.2f", m_pos_x, m_pos_y);
	SETCOLOR(debug_brush.fill_color, 1, 0, 0);
	debug_brush.fill_opacity = 1.0f;
	graphics::drawText(m_state->getCanvasWidth() * 0.5f - 0.4f, m_state->getCanvasHeight() * 0.5f - 0.6f, 0.15f, s, debug_brush);

}
