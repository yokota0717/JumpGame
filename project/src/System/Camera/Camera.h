/**
* @file Camera.h
* @brief カメラクラスを定義する
* @author yokota0717
* @date 2018.11.8
* @param history
- 2018.11.11 yokota0717
-# ターゲットに追従する処理を追加
- 2018.11.12 yokota0717
-# 描画範囲のゲッター作成
*/

#pragma once
#include "../Math/Math.h"
#include "../TaskSystem/TaskObject.h"

class Camera2D final {
private:
	//! カメラの左上の座標
	Math::Vec pos_;
	//! カメラサイズ
	Math::Vec size_;
	//! カメラに映る範囲
	Math::Box2D visibleArea_;
	//! カメラの回転角度(degree)(未実装)
	float rotation_;
	//! カメラの拡大率(未実装)
	Math::Vec scale_;
	//! 中心にとらえるターゲット
	TaskObject* target_;

public:
	Camera2D(int width, int height);
	~Camera2D() = default;

	//! カメラを指定ベクトル分移動させる
	void move(const Math::Vec& est);

	//! カメラを指定した座標に移動させる
	void setPos(const Math::Vec& pos);

	//! 現在座標を返す(左上座標)
	Math::Vec& getPos();

	//! サイズを返す
	Math::Vec& getSize();

	//! 描画範囲を返す
	Math::Box2D& getVisibleArea();

	//! 中心にとらえるターゲットを設定する
	void setTarget(TaskObject* target);

	/**
	* @brief ターゲットに追従する更新処理
	* @note ターゲットを指定した場合にそのシーンのupdateで呼ぶこと
	* ターゲットの指定がない場合は何もしない
	*/
	void chaseTarget();

	void setCenter(Math::Vec& center);
};