/**
* @file HighScoreLoader.hpp
* @brief �O���t�@�C������n�C�X�R�A����ǂݍ��ރN���X���L�q
* @author yokota0717
* date 2018.11.23
*/

#pragma once
#include "../../System/TaskSystem/TaskSystem.h"
#include <fstream>
#include <sstream>

class HighScoreLoader final : public TaskObject {
private:
	//! �n�C�X�R�A�ۑ��z��A�Ƃ肠����10��
	int highScore_[10];
	//! �n�C�X�R�A��ǂݍ��ރt�@�C����
	std::string fileName_;

	HighScoreLoader()
		:
		TaskObject("highScoreLoader","file",TaskObject::State::RUN),
		fileName_("./data/score/score.bin")
	{}
public:
	static HighScoreLoader* create() {
		auto loader = new HighScoreLoader();
		TaskSystem::getInstance().addTask(loader);
		return loader;
	}

	/**
	* @brief �n�C�X�R�A��ǂݍ���
	* @return �t�@�C���I�[�v�������s������false
	*/
	[[nodiscard]] bool loadHighScore() {
		std::fstream fin(fileName_, std::ios::in | std::ios::binary);
		if (!fin) { return false; }
		//��s���̓ǂݎ��p
		std::string line;
		for (int i = 0; i < 10; ++i) {
			//��s���ǂݍ���
			std::getline(fin, line);
			//stringstream�ɓ����
			std::istringstream is(line);
			is >> highScore_[i];
		}
		fin.close();
		return true;
	}
	[[nodiscard]] bool outputHighScore() {
		std::fstream fout(fileName_, std::ios::out | std::ios::binary | std::ios::trunc);
		if (!fout) { return false; }
		for (int i = 0; i < 10; ++i) {
			fout << highScore_[i] << std::endl;
		}
		fout.close();
		return true;
	}
};