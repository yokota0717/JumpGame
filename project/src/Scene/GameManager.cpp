#include "GameManager.h"
#include "../define.h"

GameManager::GameManager()
	:
	debug_(false),
	pad(0),
	camera_({ SCREEN_WIDTH, SCREEN_HEIGHT })
{}

GameManager::~GameManager(){
	delete sceneManager_;
}

void GameManager::init() {
	sceneManager_ = new Scene::SceneManager();
	ResourceManager::getGraphFac().initLoad();
}

void GameManager::mainLoop() {
	fps_.update();
	kb.update();
	mouse.update();
	pad.update();
	sceneManager_->updateTopScene();
	TaskSystem::getTaskSystem().updateTasks();
	if (kb.Down(Q)) { debug_ = !debug_; }
	sceneManager_->renderTopScene();
	TaskSystem::getTaskSystem().renderTasks();
	fps_.wait();
}
void GameManager::fin() {}

bool GameManager::debugMode() {
	return debug_;
}

extern GameManager* game = new GameManager();