/**
* @file Back.hpp
* @brief �w�i�N���X���`����
* @author yokota0717
* @date 2018.11.16
*/

#pragma once
#include "../System/TaskSystem/TaskSystem.h"
#include "../System/Image/Image.h"
#include "../Scene/GameManager.h"

/**
* @brief �w�i�̊G���f���N���X
*- �Ƃ肠�����J�����ɍ��킹�Ĉړ����邾��
*/
class Back final : public TaskObject {
private:
	Image image_;
	
	Back()
		:
		TaskObject("Back", "Back", TaskObject::State::RUN)
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