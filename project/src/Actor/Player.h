/**
* @file	Player.h
* @brief プレイヤクラス
* @author yokota0717
* @date 2018.11.6
*/

#pragma once
#include "../System/TaskSystem/TaskObject.h"
#include "../System/Image/Image.h"
#include "../System/Collision/Collision.h"
#include "../Utility/easing.hpp"

/**
* @brief プレイヤクラス
* @todo
* - 左右キーでジャンプし足場を昇る
* - カメラが追従する
* - 昇った高さによってスコアを加算する
* - 着地した足場の種類によって反応を変える
* - アニメーションする
*/
class Player final : public TaskObject {
public:
	enum Angle {
		L,
		R,
		F,
	};
private:
	//! ピクセル単位の現在座標
	Math::Vec draw_;
	//! 1つ前の座標
	Math::Vec preDraw_;
	//! 向き
	Angle angle_;
	//! 画像(仮画像)
	Image image_;
	//! 当たり判定(要るか？)
	Math::Box2DCollider col_;
	//! X方向座標用イージング
	Easing easeX_;
	//! Y方向座標用イージング
	Easing easeY_;
	//! 移動中かどうか
	bool isMoving_;
	//! カメラ移動用イージング(設計なおしたい)
	Easing easeCameraY_;

	//! 隠しコンストラクタ
	Player();
	//! ジャンプ処理
	void jump(Angle angle);
public:
	//! 生成窓口
	static Player* create();

	void update() override;
	void render() override;
};