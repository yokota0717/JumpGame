/**
* @file Block.h
* @brief 足場ブロッククラスを定義する
* @author yokota0717
* @date 2018.11.6
*/

#pragma once
#include "../../System/TaskSystem/TaskSystem.h"
#include "../../System/Math/Math.h"
#include "../../System/Image/Image.h"
#include "../../System/Collision/Collision.h"

class Block final : public TaskObject {
public:
	enum Type {
		NOMAL,
		COIN,
		NEEDLE,
	};
private:
	//! 大きさ
	Math::Vec size_;
	//! ブロックタイプ
	Type type_;
	//! 画像
	Image image_;
	//! 当たり判定矩形
	Math::Box2DCollider col_;
	//! カメラに一度でも映ればtrue(カメラから出た判定のため) 使ってない
	bool inCamera_;


	//! 隠しコンストラクタ
	Block();
	//! カメラに映っているか判定する
	bool isInCamera();
public:
	//! 生成窓口
	static Block* create();
	~Block();

	void setType(const Type type);
	void setPos(const Math::Vec& pos);

	bool getIsInCamera() const;  //使ってない

	Math::Vec& getSize();
	Type getType() const;

	void update() override;
	void render() override;
};