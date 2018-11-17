#include "Camera.h"

Camera2D::Camera2D(int width, int height)
	:
	pos_({ 0,0 }),
	size_({ (float)width,(float)height }),
	visibleArea_({ 0.f,0.f,(float)width, (float)height }),
	rotation_(0.f),
	scale_({ 1,1 }),
	target_(nullptr)
{
}

void Camera2D::move(const Math::Vec& est) {
	pos_ += est;
	visibleArea_ = Math::Box2D(pos_.x, pos_.y, size_.x, size_.y);
}

void Camera2D::setPos(const Math::Vec& pos) {
	pos_ = pos;
	visibleArea_ = Math::Box2D(pos_.x, pos_.y, size_.x, size_.y);
}

Math::Vec & Camera2D::getPos() {
	return pos_;
}

Math::Vec& Camera2D::getSize() {
	return size_;
}

Math::Box2D& Camera2D::getVisibleArea() {
	return visibleArea_;
}

void Camera2D::setTarget(TaskObject* target) {
	if (target) {
		target_ = target;
	}
}

void Camera2D::chaseTarget() {
	if (!target_) { return; }
	float x, y;
	x = target_->getPos().x - size_.x / 2 - 1;
	y = target_->getPos().y - size_.y / 2 - 1;
	setPos(Math::Vec(x, y));
}

void Camera2D::setCenter(Math::Vec & center) {
	setPos(Math::Vec(center.x - size_.x / 2, center.y - size_.y / 2));
}
