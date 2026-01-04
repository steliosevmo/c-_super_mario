#include "level.h"
#include <windows.h>
#include <cmath>
#include "gamestate.h"
#include "player.h"
#include "enemy.h"
#include <iostream>
#define SETCOLOR(c,r,g,b){c[0]=r,c[1]=g,c[2]=b;}



void Level::drawBlock(int i)  //draw necessary blocks
{
	Box& box = m_blocks[i];
	float x = box.m_pos_x + m_state->m_global_offset_x;
	float y = box.m_pos_y + m_state->m_global_offset_y;
	m_blocks_brush.texture = m_state->getFullAssetPath(m_block_names[i]);

	m_blocks_brush_death.fill_opacity = 0.0f;
	m_blocks_brush_death.outline_opacity = 1.0f;


	graphics::drawRect(x, y+20, 1.0f * m_block_size, 1.0f * m_block_size, m_blocks_brush_death);

	graphics::drawRect(x, y, 1.0f*m_block_size, 1.0f*m_block_size,m_blocks_brush);


	graphics::Brush flag_brush;
	flag_brush.texture = m_state->getFullAssetPath("flag.png");
	flag_brush.outline_opacity = 0;
	graphics::drawRect(flag->m_pos_x + m_state->m_global_offset_x+0.2, flag->m_pos_y + m_state->m_global_offset_y-0.5f, 3.5f * m_block_size, 6.1f * m_block_size, flag_brush);


	if (m_state->m_debugging) {
		graphics::drawRect(x, y, m_block_size, m_block_size, m_blocks_brush_debug);
	}
}

void Level::checkCollisions()//checks for collisions
{
	float offset = 0.0;
	
	for (auto& box : m_blocks) {
		
		if (offset = m_state->getPlayer()->intersectDown(box)) //change offset in order to stay on top of the block
		{
			
			m_state->getPlayer()->m_pos_y += offset;
			m_state->getPlayer()->m_vy = 0.0f;
			break;
		}
	}
	for (auto& box : m_blocks_death) {

		if (offset = m_state->getPlayer()->intersectDown(box)) //fall damage handling
		{
			m_state->getPlayer()->health = 0;
			if (m_state->getPlayer()->health <= 10) {

				graphics::playSound(m_state->getFullAssetPath("mariodie.wav"), 0.5);
				
				level_finished = true;

			}
			
			break;
		}
	}
	//if we hit the flag level ends
	if (m_state->getPlayer()->intersect(*flag))
	{
		level_finished = true;
		

	}


	
	for (auto& box : m_blocks) {
		
		if (offset = m_state->getPlayer()->intersectSideways(box))
		{
			m_state->getPlayer()->m_pos_x += offset;
			m_state->getPlayer()->m_vx = 0.0f;
			break;

		}
	}//check collisions with the enemy 
	if (enemy && m_state->getPlayer()->intersectDown(*enemy)) {
		
		graphics::playSound(m_state->getFullAssetPath("goomba_dead.wav"), 0.2f);
		score += 10;
		graphics::Brush br;
		br.texture = m_state->getFullAssetPath("smashed.png");
		graphics::drawRect(enemy->m_pos_x + m_state->m_global_offset_x, enemy->m_pos_y + m_state->m_global_offset_y, enemy->size, enemy->size, br);
		
		deleteEnemy(); 
	}
	if (enemy && m_state->getPlayer()->intersectSideways(*enemy)) {
		graphics::playSound(m_state->getFullAssetPath("bump.wav"), 0.5);
		if (m_state->getPlayer()->health <=10) {
			
			graphics::playSound(m_state->getFullAssetPath("mariodie.wav"), 0.5);
			level_finished = true;

		}
		m_state->getPlayer()->health -= 10;
		deleteEnemy();
	}
	
}

void Level::spawnEnemy() //spawns an enemy 
{
	enemy = new Enemy("enemy1");
	enemy->enemy_pos_x = m_state->getCanvasWidth()-m_state->m_global_offset_x ;
	
}
void Level::deleteEnemy() {
	
	delete enemy;
	enemy = nullptr;
}

void Level::checkEnemy()
{
	if (enemy &&!enemy->isActive()) {
		delete enemy;
		enemy = nullptr;
	}
}

Level::Level(const std::string& name)
{
}

void Level::update(float dt)
{
	if (m_state->getPlayer()->isActive()) {
		m_state->getPlayer()->update(dt);
	}
	checkCollisions();
	GameObject::update(dt);
	checkEnemy();
	
	float delta_time = dt / 1000.0f;
	enemy_pos_x -= enemy_speed * delta_time;
	

	if (!enemy) {
		spawnEnemy();
	}
	if (enemy) {
		
			enemy->update(dt);
	}


}

void Level::init()
{
	
	graphics::setFont(m_state->getFullAssetPath("bitstream.ttf"));


	m_brush_background.outline_opacity = 0.0f;
	m_brush_background.texture = m_state->getFullAssetPath("background_real.png");

	
	int i = -10;
	while (i < 170) {
		m_blocks_death.push_back(Box(i * m_block_size, 20 * m_block_size, m_block_size, m_block_size));  // Πλατφόρμα ψηλότερη
		i++;
	}

	int j = -10;
	while(j<150) {
	
		if (j % 10 == 0) {  //creates the level blocks 
			m_blocks.push_back(Box(j * m_block_size,4 * m_block_size, m_block_size, m_block_size));  // Πλατφόρμα ψηλότερη
			m_block_names.push_back("block.png");
			j++;
			m_blocks.push_back(Box(j * m_block_size, 4 * m_block_size, m_block_size, m_block_size));  // Πλατφόρμα ψηλότερη
			m_block_names.push_back("block.png");
			j++;
			m_blocks.push_back(Box(j * m_block_size, 4 * m_block_size, m_block_size, m_block_size));  // Πλατφόρμα ψηλότερη
			m_block_names.push_back("block.png");
			j++;

		}
		else {
			m_blocks.push_back(Box(j * m_block_size, 6 * m_block_size, m_block_size, m_block_size));  // Κανονική πλατφόρμα
			m_block_names.push_back("block.png");
			j++;
		}
	}

	
	//creates the flag at the end
	m_dynamic_objects_list.push_back(*flag);
	m_block_names.push_back("flags.png");
	graphics::drawRect(flag->m_pos_x + m_state->m_global_offset_x, flag->m_pos_y + m_state->m_global_offset_y, m_block_size, m_block_size * 5, m_blocks_brush);
	


	m_sprites_enemy.push_back(m_state->getFullAssetPath("enemy1.png"));
	m_sprites_enemy.push_back(m_state->getFullAssetPath("enemy0.png"));
	m_sprites_enemy.push_back(m_state->getFullAssetPath("enemy5.png"));
	enemy_pos_x = m_state->getCanvasWidth() + 1.1f * enemy_size;
	enemy_pos_y = 4.f;
	
	m_blocks_brush.outline_opacity = 0.0f;
	m_blocks_brush_debug.fill_opacity = 0.1f;
	SETCOLOR(m_blocks_brush_debug.fill_color, 0.2f, 1.0f, 0.1f);
	SETCOLOR(m_blocks_brush_debug.outline_color, 0.3f, 1.0f, 0.2f);

}

void Level::draw()
{
	float w = m_state->getCanvasWidth();
	float h = m_state->getCanvasHeight();

	float offset_x = m_state->m_global_offset_x + w / 2.0f;
	float offset_y = m_state->m_global_offset_y + h / 2.0f;
	
	graphics::drawRect(0, 1, 2.0f * w, 2.0f * h, m_brush_background);


	if (m_state->getPlayer()->isActive()) {
		m_state->getPlayer()->draw();
		
	}

	for (int i = 0; i < m_blocks.size(); i++) {
		drawBlock(i);
	}
	
	if (m_state->getPlayer()->isActive()) {
		graphics::Brush brr;
		brr.fill_opacity = 1.f;
		SETCOLOR(brr.fill_color, 0, 0, 0);
		std::string scoreText = "Score: " + std::to_string(score);
		graphics::drawText(5.5f, 0.7f, 0.4f, scoreText, brr); //draws score 
	}
	if (m_state->getPlayer()->isActive()) {
		graphics::Brush brr;
		brr.fill_opacity = 1.f;
		SETCOLOR(brr.fill_color, 0, 0, 0);
		std::string healthText= "Health:" + std::to_string(m_state->getPlayer()->health);
		graphics::drawText(0.5f, 0.7f, 0.4f, healthText, brr); //draw health count
	}
	if (enemy) {
		enemy->draw();
	}
	
	

	
}

Level::~Level()
{

	delete flag;
	flag = nullptr;
}


