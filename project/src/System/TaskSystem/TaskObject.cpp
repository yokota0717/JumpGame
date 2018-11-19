#include "TaskObject.h"

TaskObject::TaskObject(const std::string& name, const std::string& group, const State state)
	:
	name_(name),
	group_(group),
	state_(state),
	pos_({ 0,0 })
{
	id_ = ++uid_;
}

void TaskObject::setPriority(const float priority) {
	drawPriority_ = priority;
}

void TaskObject::changeState(const State state) {
	state_ = state;
}

std::string TaskObject::changeName(const std::string& name) {
	std::string old = name_;
	name_ = name;
	return old;
}

std::string TaskObject::changeGroup(const std::string& group) {
	std::string old = group_;
	group_ = group;
	return old;
}

void TaskObject::postMsg(TaskObject* sender, TaskObject* receiver, const std::any msg) {
	if (receiver) {
		receiver->receiveMsg(sender, msg);
	}
}

void TaskObject::receiveMsg(TaskObject* sender, const std::any msg) {}

void TaskObject::setPos(Math::Vec pos) {
	pos_ = pos;
}

const std::string& TaskObject::name() const {
	return name_;
}

const std::string& TaskObject::group() const {
	return group_;
}

const TaskObject::State & TaskObject::state() const {
	return state_;
}

const int TaskObject::id() const {
	return id_;
}

const bool TaskObject::isRun() {
	return state_ == State::RUN;
}

const bool TaskObject::isStop() {
	return state_ == State::STOP;
}

const bool TaskObject::isDestroy() {
	return state_ == State::DESTROY;
}

Math::Vec & TaskObject::getPos() {
	return pos_;
}

bool TaskObject::operator<(const TaskObject& v) const {
	return drawPriority_ < v.drawPriority_;
}

const bool TaskObject::getPriority() const {
	return drawPriority_;
}
