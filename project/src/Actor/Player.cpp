/**
* @file Player.cpp
* @brief プレイヤクラスの定義
* @author yokota0717
* @date 2018.11.6
* @param history
- 2018.11.15 yokota0717
-# 上方向への座標移動を追加
*/

//------------------------------------
// @TODO
// * 左右キー入力でBlockManagerにメッセージ送信
// * 完全に画面外に出たブロックを反対側に配置しなおす処理
//------------------------------------
#include "Player.h"
#include "../Scene/GameManager.h"
#include "../define.h"

Player::Player()
	:
	TaskObject("player", "player", TaskObject::State::RUN),
	draw_({ SCREEN_WIDTH / 2,SCREEN_HEIGHT - (64+120) }),
	angle_(F)
{
	__super::setPos({ 1,0 });
	setPriority(0.8f);
	image_.setHandle("player2.png");
	col_.setPos(draw_);
	col_.setSize(Math::Vec{ 50,80 });
}

void Player::jump(Angle angle) {
	//ここにジャンプ処理
}

Player* Player::create() {
	auto obj = new Player();
	TaskSystem::getTaskSystem().addTask(obj);
	return obj;
}

void Player::update() {
	if (game->kb.Down(LEFT)) {
		setPos(Math::Vec(getPos().x - 1, getPos().y));
		draw_.x -= 100;
		draw_.y -= 160;
		angle_ = Angle::L;
		jump(L);
	}
	if (game->kb.Down(RIGHT)) {
		setPos(Math::Vec(getPos().x + 1, getPos().y));
		draw_.x += 100;
		draw_.y -= 160;
		angle_ = Angle::R;
		jump(R);
	}
	game->camera_.setCenter(draw_);
	if (game->camera_.getPos().y > 0) {
		game->camera_.setPos(Math::Vec(game->camera_.getPos().x, 0));
	}
}

void Player::render() {
	Math::Vec d = draw_;
	d.Offset(-game->camera_.getPos().x, -game->camera_.getPos().y);
	image_.draw(d, true);
}
