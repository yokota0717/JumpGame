#include "Block.h"
#include "../../Scene/GameManager.h"
#include "../../define.h"

Block::Block()
	:
	TaskObject("block", "block", TaskObject::State::RUN),
	size_({ 100,30 }),
	type_(Type::NOMAL),
	inCamera_(false)
{
}

bool Block::isInCamera() {
	return col_.Collision(game->camera_.getVisibleArea());
}

Block * Block::create() {
	auto b = new Block();
	TaskSystem::getTaskSystem().addTask(b);
	return b;
}

Block::~Block() {}

void Block::setType(const Type type) {
	type_ = type;
}

void Block::setPos(const Math::Vec& pos) {
	__super::setPos(pos);
	col_.setPos(pos);
	col_.setSize(Math::Vec{ 100,30 });
}

bool Block::getIsInCamera() const {
	return inCamera_;
}

Math::Vec & Block::getSize() {
	return size_;
}

Block::Type Block::getType() const {
	return type_;
}

void Block::update() {
	//! 一度でもカメラに入ったかどうか判定
	if (!inCamera_) {
		inCamera_ = isInCamera();
	}
}

void Block::render() {
	//カメラにあわせた描画
	Math::Vec p = getPos();
	p.Offset(-game->camera_.getPos().x, -game->camera_.getPos().y);
	//タイプ別描画分け
	switch (type_) {
	case Type::NOMAL:
		DrawBox(p.x, p.y, p.x + size_.x, p.y + size_.y, GetColor(50, 255, 50), true);
		break;
	case Type::COIN:
		DrawBox(p.x, p.y, p.x + size_.x, p.y + size_.y, GetColor(150, 150, 50), true);
		break;
	case Type::NEEDLE:
		DrawBox(p.x, p.y, p.x + size_.x, p.y + size_.y, GetColor(255, 50, 50), true);
		break;
	}
}
