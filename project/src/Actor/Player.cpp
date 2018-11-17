/**
* @file Player.cpp
* @brief プレイヤクラスの定義
* @author yokota0717
* @date 2018.11.6
* @param history
- 2018.11.15 yokota0717
-# 上方向への座標移動を追加
*/

#include "Player.h"
#include "../Scene/GameManager.h"
#include "../define.h"

Player::Player()
	:
	TaskObject("player", "player", TaskObject::State::RUN),
	draw_({ SCREEN_WIDTH / 2,SCREEN_HEIGHT - (64 + 120) }),
	angle_(F),
	isMoving_(false)
{
	__super::setPos({ 1,0 });
	image_.setHandle("player2.png");
	setPriority(1.f);
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
	//入力
	if (game->kb.Down(LEFT) && !isMoving_) {
		setPos(Math::Vec(getPos().x - 1, getPos().y + 1));
		isMoving_ = true;
		preDraw_ = draw_;
		angle_ = Angle::L;
		jump(L);
	}
	if (game->kb.Down(RIGHT) && !isMoving_) {
		setPos(Math::Vec(getPos().x + 1, getPos().y + 1));
		isMoving_ = true;
		preDraw_ = draw_;
		angle_ = Angle::R;
		jump(R);
	}
	//動いているなら座標更新
	if (isMoving_) {
		easeX_.run(Easing::CubicInOut, 10);
		easeY_.run(Easing::BackOut, 10);
		easeCameraY_.run(Easing::CubicOut, 10);
		//座標更新
		draw_.x = easeX_.getVolume(preDraw_.x, -100 + 200 * (int)angle_);
		draw_.y = easeY_.getVolume(preDraw_.y, -160);
		//カメラ座標更新
		Math::Vec cameraCenter{ draw_.x, game->camera_.getPos().y };
		cameraCenter.y = easeCameraY_.getVolume(preDraw_.y, -160);
		game->camera_.setCenter(cameraCenter);

	}
	//移動し終わったか判定
	if (easeX_.isEaseEnd() && easeY_.isEaseEnd()) {
		isMoving_ = false; 
		easeX_.reset();
		easeY_.reset();
		easeCameraY_.reset();
	}
	if (game->camera_.getPos().y > 0) {
		game->camera_.setPos(Math::Vec(game->camera_.getPos().x, 0));
	}

}

void Player::render() {
	Math::Vec d = draw_;
	d.Offset(-game->camera_.getPos().x, -game->camera_.getPos().y);
	image_.draw(d, true);
}
