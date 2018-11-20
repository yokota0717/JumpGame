#include "Image.h"
#include "../../Scene/GameManager.h"


Image::Image()
	:
	handleDiv_(nullptr)
{}

Image::~Image()
{
}

void Image::setHandle(const std::string& path) {
	handle_ = ResourceManager::getGraphFac().getGraph(path);
}
void Image::setHandleDiv(const std::string& path, const int allNum, const int xNun, const int yNun, const int xSize, const int ySize) {
	handleDiv_ = ResourceManager::getGraphFac().getGraphDiv(path, allNum, xNun, yNun, xSize, ySize);
}

void Image::draw(const Math::Vec& pos, const bool isCenter) {
	if (isCenter) {
		int w = 0, h = 0;
		GetGraphSize(handle_, &w, &h);
		Math::Vec pivot{ pos.x - w / 2,pos.y - h / 2 };
		DrawGraphF(pivot.x, pivot.y, handle_, true);
	}
	else {
		DrawGraphF(pos.x, pos.y, handle_, true);
	}
}

void Image::draw(const Math::Vec& pos, const int index, const bool isCenter) {
	if (isCenter) {
		int w, h;
		GetGraphSize(handle_, &w, &h);
		Math::Vec pivot{ pos.x + w,pos.x + h };
		DrawGraphF(pivot.x, pivot.y, handleDiv_[index], true);
	}
	else {
		DrawGraphF(pos.x, pos.y, handleDiv_[index], true);
	}
}

void Image::drawRect(const Math::Vec& pos, const Math::Box2D& src, const bool turnFlag) {
	DrawRectGraphF(pos.x, pos.y, (int)src.x, (int)src.y, (int)src.w, (int)src.h, handle_, true, turnFlag);
}

void Image::drawExtRota(const Math::Vec & pos, const Math::Vec & scale, const float angle, const bool isTurn) {
	int w = 0, h = 0;
	GetGraphSize(handle_, &w, &h);
	Math::Vec pivot{ pos.x + w / 2,pos.y + h / 2 };
	DrawRectRotaGraphFast3F(pivot.x, pivot.y, 0, 0, w, h, w / 2.f, h / 2.f, scale.x, scale.y, angle, handle_, true, isTurn);
}

void Image::drawExtRota(const Math::Vec & pos, const Math::Vec & scale, const float angle, const int index, const bool isTurn) {
	int w = 0, h = 0;
	GetGraphSize(handleDiv_[index], &w, &h);
	Math::Vec pivot{ pos.x + w / 2,pos.y + h / 2 };
	DrawRectRotaGraphFast3F(pivot.x, pivot.y, 0, 0, w, h, w / 2.f, h / 2.f, scale.x, scale.y, angle, handleDiv_[index], true, isTurn);
}

Math::Vec Image::getGraphSize() {
	Math::Vec size;
	if (handleDiv_ == nullptr) {
		GetGraphSizeF(handle_, &size.x, &size.y);
	}
	else {
		GetGraphSizeF(handleDiv_[0], &size.x, &size.y);
	}
	return size;
}

int Image::getHandle() {
	return handle_;
}