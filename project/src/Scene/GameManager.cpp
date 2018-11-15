#include "GameManager.h"
#include "../define.h"

GameManager::GameManager()
	:
	pad(0),
	camera_({ SCREEN_WIDTH, SCREEN_HEIGHT })
{
	debug_ = false;
	sceneManager_ = new Scene::SceneManager();
	//ResourceManager::getGraphFac().initLoad();
}

GameManager::~GameManager(){
	delete sceneManager_;
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