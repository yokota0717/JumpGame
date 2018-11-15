/**
* @file TaskObject.h
* @brief タスク基底クラスを定義する
* @author yokota0717
* @date 2018.11.2
* @param history
- 2018.11.11 yokota0717
-# 座標を持たせた
*/

#pragma once
#include <string>
#include "../Math/Math.h"

/**
* @brief タスク基底クラス
*/
class TaskObject {
public:
	enum class State {
		NON,		//! 未定義
		RUN,		//! 通常
		STOP,		//! 停止
		DESTROY,	//! 削除予約
	};
private:
	//! 固有ID、オブジェクト生成毎にインクリメントされる
	static int uid_;
	//! ID
	int id_;
	//! 固有の名前
	std::string name_;
	//! 属するグループ名
	std::string group_;
	//! 駆動状態
	State state_;
	//! 描画優先度
	float drawPriority_;

	//! 座標
	Math::Vec pos_;

public:
	TaskObject(const std::string& name, const std::string& group, const State state);
	virtual ~TaskObject() = default;

	/**
	* @brief 描画優先度を設定する
	* - 数値が大きいほど手前に描画される
	* @param priority 描画優先度
	*/
	void setPriority(const float priority);
	/**
	* @brief 駆動状態を変更する
	* @param state 指定する駆動状態
	*/
	void changeState(const State state);
	/**
	* @brief 名前を変更する
	* @param name 新しい名前
	* @return 変更前の名前
	*/
	std::string changeName(const std::string& name);
	/**
	* @brief グループを変更する
	* @param name 新しいグループ名
	* @return 変更前のグループ名
	*/
	std::string changeGroup(const std::string& group);

	/**
	* @brief タスクにメッセージを送る
	* @param sender メッセージを送るタスクのポインタ
	* @param receiver メッセージを受け取るタスクのポインタ
	* @msg メッセージ
	*/
	void postMsg(TaskObject* sender, TaskObject* receiver, std::string& msg);
	/**
	* @brief タスクからのメッセージ受け取り関数
	* @param sender メッセージを送るタスクのポインタ
	* @param msg メッセージ
	*/
	virtual void receiveMsg(TaskObject* sender, std::string& msg);

	/**
	* @brief 座標を設定する
	* @param pos 指定する座標
	*/
	void setPos(Math::Vec pos);

	virtual void init() {};
	virtual void update() = 0;
	virtual void render() = 0;

	//! 名前を取得する
	[[nodiscard]] const std::string& name();

	//! グループ名を取得する
	[[nodiscard]] const std::string& group();

	//! 駆動状態を取得する
	[[nodiscard]] const State& state();

	//! IDを取得する
	[[nodiscard]] const int id();

	//! 駆動状態が通常ならtrue
	[[nodiscard]] const bool isRun();

	//! 駆動状態が停止ならtrue
	[[nodiscard]] const bool isStop();

	//! 駆動状態が削除予定ならtrue
	[[nodiscard]] const bool isDestroy();

	//! 現在座標を取得する
	Math::Vec& getPos();


	//! 比較演算子のオーバーロード
	bool operator < (const TaskObject& v);
};

