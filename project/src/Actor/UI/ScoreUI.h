/**
* @file ScoreUI.h
* @brief スコアを表示するUIクラスを定義する
* @author yokota0717
* @date 2018.11.19
*/

#pragma once
#include "../../System/TaskSystem/TaskSystem.h"
#include "Score.h"
#include "../../System/Image/Image.h"

class ScoreUI final : public TaskObject {
private:
	Image image_;
	int score_;
	
	ScoreUI();
public:
	static ScoreUI* create();
	~ScoreUI();

	void update() override;
	void render() override;

	void receiveMsg(TaskObject* sender, const std::any msg) override;
};