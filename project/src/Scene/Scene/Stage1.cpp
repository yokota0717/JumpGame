#include "Stage1.h"
#include "DxLib.h"
#include "../GameManager.h"
#include "../../Tasks/Player.h"
#include "../../Tasks/Block/BlockManager.h"
#include "../../Tasks/Back.hpp"
#include "../../Tasks/UI/Score.h"
#include "../../Tasks/UI/ScoreUI.h"
#include "../../Tasks/FileLoad/HighScoreLoader.hpp"


namespace Scene {
	Stage1::Stage1(IOnSceneChangedListener* listener, [[maybe_unused]]const Parameter& param)
		:
		AbstractScene(listener)
	{
		BlockManager::create();
		auto player = Player::create();
		game->camera_.setTarget(player);
		Score::create();
		ScoreUI::create();
		auto hi = HighScoreLoader::create();
		hi->loadHighScore();
		hi->outputHighScore();
	}

	Stage1::~Stage1() {
		TaskSystem::getInstance().killTaskGroup("player");
		TaskSystem::getInstance().killTaskGroup("block");
		TaskSystem::getInstance().killTaskGroup("score");
		TaskSystem::getInstance().killTaskGroup("UI");
		game->camera_.setPos(Math::Vec{ 0,0 });
	}

	void Stage1::update() {
		//テスト処理　カメラ移動----------------------------------
		if (game->kb.On(J)) {
			game->camera_.move(Math::Vec(-2, 0));
		}
		if (game->kb.On(L)) {
			game->camera_.move(Math::Vec(2, 0));
		}
		if (game->kb.On(I)) {
			game->camera_.move(Math::Vec(0, -2));
		}
		if (game->kb.On(K)) {
			game->camera_.move(Math::Vec(0, 2));
		}
		//テストここまで-----------------------------------------
		if (game->kb.Down(ENTER)) {
			callBack().onSceneChanged(Scene::SceneName::TITLE, nullptr, Scene::StackPopFlag::POP);
		}
	}

	void Stage1::render() {
		DrawFormatString(0, 0, GetColor(255, 255, 255), "stage1");
	}
}

