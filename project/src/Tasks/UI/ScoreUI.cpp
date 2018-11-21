#include "ScoreUI.h"
#include "../../System/ResourceManager/ResourceManager.h"

ScoreUI::ScoreUI()
	:
	TaskObject("scoreUI", "UI", TaskObject::State::RUN),
	number_(new Image()),
	font_(new Image()),
	scale_({ 0.7f,0.7f })
{
	number_->setHandleDiv("number.png", 20, 10, 2, 60, 60);
	font_->setHandleDiv("font1.png", 14 * 3, 3, 14, 300, 60);
	setPos(Math::Vec{ -50,5 });
	setPriority(1.f);
}
ScoreUI* ScoreUI::create() {
	auto obj = new ScoreUI();
	TaskSystem::getInstance().addTask(obj);
	return obj;
}

ScoreUI::~ScoreUI() {
	delete number_;
	delete font_;
}

void ScoreUI::update() {

}

void ScoreUI::render() {
	//‚Æ‚è‚ ‚¦‚¸100‚ÌˆÊ‚Ü‚Å
	Math::Vec d = getPos();
	font_->drawExtRota(d, scale_, 0.f, 17, false);
	d.x += font_->getGraphSize().x - 50;
	if (score_ > 999) { score_ %= 1000; }
	number_->drawExtRota(d, scale_, 0.f, score_ / 100, false);
	d.x += 35;
	number_->drawExtRota(d, scale_, 0.f, ((score_ % 100) / 10), false);
	d.x += 35;
	number_->drawExtRota(d, scale_, 0.f, score_ % 10, false);
}

void ScoreUI::receiveMsg(TaskObject * sender, const std::any msg) {
	score_ = std::any_cast<int>(msg);
}
