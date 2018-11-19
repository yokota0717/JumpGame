#include "ScoreUI.h"

ScoreUI::ScoreUI()
	:
	TaskObject("scoreUI", "UI", TaskObject::State::RUN)
{
	image_.setHandleDiv("number.png", 13, 13, 1, 16, 32);
	setPos(Math::Vec{ 30,10 });
	setPriority(1.f);
}
ScoreUI* ScoreUI::create() {
	auto obj = new ScoreUI();
	TaskSystem::getTaskSystem().addTask(obj);
	return obj;
}

ScoreUI::~ScoreUI() {}

void ScoreUI::update() {

}

void ScoreUI::render() {
	//‚Æ‚è‚ ‚¦‚¸100‚ÌˆÊ‚Ü‚Å
	Math::Vec d = getPos();
	if (score_ > 999) { score_ %= 1000; }
	image_.draw(d, score_ / 100, false);
	d.x += 20;
	image_.draw(d, ((score_ % 100) / 10), false);
	d.x += 20;
	image_.draw(d, score_ % 10, false);
}

void ScoreUI::receiveMsg(TaskObject * sender, const std::any msg) {
	score_ = std::any_cast<int>(msg);
}
