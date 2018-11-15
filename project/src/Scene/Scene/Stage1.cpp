#include "Stage1.h"
#include "DxLib.h"
#include "../GameManager.h"
#include "../../Actor/Player.h"
#include "../../Actor/Block/BlockManager.h"


namespace Scene {
	Stage1::Stage1(IOnSceneChangedListener* listener, [[maybe_unused]]const Parameter& param)
		:
		AbstractScene(listener)
	{
		auto player = Player::create();
		BlockManager::create();
		game->camera_.setTarget(player);
	}


	Stage1::~Stage1() {
		TaskSystem::getTaskSystem().killTaskGroup("player");
		TaskSystem::getTaskSystem().killTaskGroup("block");
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

