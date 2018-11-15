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
	draw_({ SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2 + 100 }),
	angle_(F)
{
	__super::setPos({ 1,1 });
	setPriority(0.8f);
	image_.setHandle("player.png");
	col_.setPos(draw_);
	col_.setSize(Math::Vec{ 50,50 });
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
	if (game->kb.On(LEFT)) {
		setPos(Math::Vec(getPos().x - 1, getPos().y));
		draw_.x -= 3;
		jump(L);
	}
	if (game->kb.On(RIGHT)) {
		setPos(Math::Vec(getPos().x + 1, getPos().y));
		draw_.x += 3;
		jump(R);
	}
	game->camera_.setCenter(draw_);
}

void Player::render() {
	Math::Vec d = draw_;
	d.Offset(-game->camera_.getPos().x, -game->camera_.getPos().y);
	image_.draw(d, true);
}
