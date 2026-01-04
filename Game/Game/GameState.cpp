#include "GameState.h"
#include "level.h"
#include "player.h"
#include "EndPage.h"
#include "enemy.h"
#include "Menu.h"
#include <thread>
#include <chrono>
#define SETCOLOR(c,r,g,b){c[0]=r,c[1]=g,c[2]=b;}



GameState::GameState()
{
}

void GameState::init()
{

	m_menu = new Menu();
	m_menu->init();

	graphics::preloadBitmaps(getAssetDir());//preloads the assets
	graphics::playMusic(getFullAssetPath("background_music.mp3"), 0.01, true);//plays music 
	graphics::setFont(getFullAssetPath("bitstream.ttf"));//sets font 
}
//calls the draw method of each object
void GameState::draw()
{
	if (m_menu) {
		m_menu->draw();
	}
	if (m_current_level){
		m_current_level->draw();
	}
	if (m_endPage) {
		m_endPage->draw();
	}

}

void GameState::update(float dt)
{
	if (dt > 500) {
		return;
	}
	float sleep_time = std::max(0.0f, 17.0f - dt);

	std::this_thread::sleep_for(std::chrono::duration<float, std::milli>(sleep_time));

	
	if (m_current_level) {
		m_current_level->update(dt);
		if (m_current_level->level_finished) {    //if level is finished get the information we need and go to end page
		    int* i= int(m_current_level->score);
			int* health = int(m_player->health);
			switchToMenu();
			m_endPage = new EndPage();
			m_endPage->init();
			m_endPage->scoreResult = *i;
			m_endPage->endHealth = *health;
		}
	}

	if (m_menu) {
		m_menu->update(dt);
		if (graphics::getKeyState(graphics::SCANCODE_RETURN)) {   //press return and create the level
			delete m_menu;
			m_menu = nullptr;

			m_current_level = new Level("Level1");
			m_current_level->init();

			m_player = new Player("Player");
			m_player->init();

			m_enemy = new Enemy("Enemy");
			m_enemy->init();
		}
	}
	if (m_endPage) {
		m_endPage->update(dt);

		if (graphics::getKeyState(graphics::SCANCODE_M)) { //press M and go to the Menu
			delete m_endPage;
			m_endPage = nullptr;

			m_menu = new Menu();
			m_menu->init();
		}
	}
	if (!m_current_level) {
		return;
	}

	m_debugging = graphics::getKeyState(graphics::SCANCODE_0);
}

GameState* GameState::getInstance()
{
	if (m_unique_instance == nullptr) {
		m_unique_instance = new GameState();
	}
	return m_unique_instance;
}

GameState::~GameState()
{
	if (m_player) {
		delete m_player;
	}
	if (m_current_level) {
		delete m_current_level;
	}
	
	if (m_menu)
	{
		delete m_menu;
	}
}

std::string GameState::getAssetDir()
{
	return m_asset_path;
}

std::string GameState::getFullAssetPath(const std::string& asset)
{
	return  m_asset_path + asset;
}

void GameState::switchToMenu()
{
	// delete end screen if exists
	if (m_endPage) {
		delete m_endPage;
		m_endPage = nullptr;
	}

	// delete current level(and enemy) if exists
	if (m_current_level) {
		delete m_current_level;
		m_current_level = nullptr;
	}

	// delete player if exists
	if (m_player) {
		delete m_player;
		m_player = nullptr;
	}

}


GameState* GameState::m_unique_instance = nullptr ;