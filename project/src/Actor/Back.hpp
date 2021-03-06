/**
* @file Back.hpp
* @brief 背景クラスを定義する
* @author yokota0717
* @date 2018.11.16
*/

#pragma once
#include "../System/TaskSystem/TaskSystem.h"
#include "../System/Image/Image.h"
#include "../Scene/GameManager.h"

/**
* @brief 背景の絵を映すクラス
*- とりあえずカメラに合わせて移動するだけ
*/
class Back final : public TaskObject {
private:
	Image image_;
	
	Back()
		:
		TaskObject("back", "back", TaskObject::State::RUN)
	{
		setPriority(0.1f);
	};
public:
	static Back* create(const std::string& imagePath) {
		auto back = new Back();
		TaskSystem::getTaskSystem().addTask(back);
		back->setImage(imagePath);
		return back;
	}
	~Back() {};

	void setImage(const std::string& path) {
		image_.setHandle(path);
	}
	void updateLate() override {
		setPos(game->camera_.getPos());
	}
	void render() override {
		image_.draw(getPos(), false);
	}
};