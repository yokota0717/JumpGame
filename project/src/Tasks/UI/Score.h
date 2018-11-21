/**
* @file Score.h
* @brief �X�R�A�̌v�Z���s���N���X���`����
* @author yokota0717
* @date 2018.11.18
*/

#pragma once
#include "../../System/TaskSystem/TaskObject.h"

class Score final : public TaskObject {
private:
	//! ���݂̃X�R�A(�o��������)
	int score_;

	Score();
public:
	static Score* create();
	~Score();

	//! �X�R�A���Z
	void addScore(const int add);
	//! �X�R�A���擾����
	int getScore() const;
	void receiveMsg(TaskObject * sender, const std::any msg);
};