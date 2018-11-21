#include "../GameManager.h"
#include "Title.h"
#include "DxLib.h"
#include "../../Tasks/Back.hpp"

namespace Scene {
	Title::Title(IOnSceneChangedListener* listener, [[maybe_unused]]const Parameter& param)
		:
		AbstractScene(listener)
	{
		Back::create("sky.bmp");
	}

	Title::~Title() {}

	void Title::update() {
		if (game->kb.Down(ENTER)) {
			callBack().onSceneChanged(Scene::SceneName::GAME, nullptr, Scene::StackPopFlag::POP);
		}
	}

	void Title::render()
	{
		SetFontSize(50);
		DrawFormatString(0, 0, GetColor(255, 255, 255), "title");


	}
}
