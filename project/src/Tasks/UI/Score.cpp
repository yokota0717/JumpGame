#include "Score.h"
#include "../../System/TaskSystem/TaskSystem.h"

Score* Score::create() {
	auto obj = new Score();
	TaskSystem::getInstance().addTask(obj);	
	return obj;
}

Score::Score()
	:
	TaskObject("score", "score", TaskObject::State::RUN)
{
	score_ = 0;
}

Score::~Score() {}

void Score::addScore(const int add) {
	score_ += add;
	auto scoreUI = TaskSystem::getInstance().getTask("scoreUI", "UI");
	postMsg(this, scoreUI, score_);
}

int Score::getScore() const {
	return score_;
}

void Score::receiveMsg(TaskObject* sender, const std::any msg) {
	addScore(std::any_cast<int>(msg));
}
