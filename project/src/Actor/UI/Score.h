/**
* @file Score.h
* @brief スコアの計算を行うクラスを定義する
* @author yokota0717
* @date 2018.11.18
*/

#pragma once
#include "../../System/TaskSystem/TaskObject.h"

class Score final : public TaskObject {
private:
	//! 現在のスコア(登った高さ)
	int score_;

	Score();
public:
	static Score* create();
	~Score();

	//! スコア加算
	void addScore(const int add);
	//! スコアを取得する
	int getScore() const;
	void receiveMsg(TaskObject * sender, const std::any msg);
};