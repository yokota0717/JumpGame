/**
* @file HighScoreLoader.hpp
* @brief 外部ファイルからハイスコア情報を読み込むクラスを記述
* @author yokota0717
* date 2018.11.23
*/

#pragma once
#include "../../System/TaskSystem/TaskSystem.h"
#include <fstream>
#include <sstream>

class HighScoreLoader final : public TaskObject {
private:
	//! ハイスコア保存配列、とりあえず10個
	int highScore_[10];
	//! ハイスコアを読み込むファイル名
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
	* @brief ハイスコアを読み込む
	* @return ファイルオープンが失敗したらfalse
	*/
	[[nodiscard]] bool loadHighScore() {
		std::fstream fin(fileName_, std::ios::in | std::ios::binary);
		if (!fin) { return false; }
		//一行分の読み取り用
		std::string line;
		for (int i = 0; i < 10; ++i) {
			//一行分読み込む
			std::getline(fin, line);
			//stringstreamに入れる
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