#include "Score.h"
#include "../../System/TaskSystem/TaskSystem.h"

Score* Score::create() {
	auto obj = new Score();
	TaskSystem::getTaskSystem().addTask(obj);	
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
}

int Score::getScore() const {
	return score_;
}
