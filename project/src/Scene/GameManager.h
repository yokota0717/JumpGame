/**
* @file GameManager.h
* @brief ゲームクラスを定義する
*/

#pragma once
#include "../System/Input/Input.h"
#include "../System/ResourceManager/ResourceManager.h"
#include "../Scene/SceneManager.hpp"
#include "../System/TaskSystem/TaskSystem.h"
#include "../System/FPS/FPS.hpp"
#include "../System/Camera/Camera.h"
#include "../Utility/Counter.hpp"

/**
* @brief ゲーム管理クラス
*/
class GameManager final {
	//! デバッグモード切替用
	bool debug_;
	//! シーン管理用
	Scene::SceneManager* sceneManager_;
	//! FPS固定
	FPS fps_;
	//! 経過フレームを計測する
	Counter frame_;
public:
	//! カメラ
	Camera2D camera_;

	GameManager();
	~GameManager();
	void init();
	void fin();

	//!入力関連
	Keyboard kb;
	Mouse mouse;
	GPad pad;

	/**
	* @brief メインループ
	*/
	void mainLoop();

	/**
	* @brief 現在デバッグモードが起動中かを返す
	* @return bool デバッグモード起動中かどうか
	*/
	bool debugMode();

	/**
	* @brief シーンが始まってからの経過フレームを取得する
	* @return int そのシーンが始まってからの経過フレーム
	* @note シーン遷移時に初期化される
	*/
	int getFrame();
	/**
	* @brief 経過フレーム計測カウンターを初期化する
	* @note シーン遷移時に必ず呼ぶこと
	*/
	void resetFrameCounter();
};

//! ゲーム管理オブジェクト
extern GameManager* game;