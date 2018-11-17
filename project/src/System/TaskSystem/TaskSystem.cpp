#include "TaskSystem.h"
#include <algorithm>
#include <functional>

bool isLowerPriority(const TaskObject* left, const TaskObject* right) {
	return *left < *right;
}

TaskSystem::TaskSystem(){}

void TaskSystem::sortByPriority() {
	std::sort(tasks_.begin(), tasks_.end(), isLowerPriority);
}

void TaskSystem::releaseMemory() {
	for (int i = 0; i < tasks_.size(); ++i) {
		if (tasks_[i]) {
			delete tasks_[i];
		}
	}
	for (int i = 0; i < addTasks_.size(); ++i) {
		if (addTasks_[i]) { 
			delete addTasks_[i]; 
		}
	}
}

TaskSystem::~TaskSystem() {
	releaseMemory();
}

TaskSystem& TaskSystem::getTaskSystem() {
	if (!instance_) {
		instance_ = std::unique_ptr<TaskSystem>(new TaskSystem());
	}
	return *(instance_.get());
}

TaskObject* TaskSystem::addTask(TaskObject* task) {
	if (task) {
		addTasks_.emplace_back(task);
		return task;
	}	
	return nullptr;
}

void TaskSystem::killTask(const std::string& name, const std::string& group) {
	auto it = tasks_.begin();
	while (it != tasks_.end()) {
		if ((*it)->name() == name && (*it)->group() == group) {
			(*it)->changeState(TaskObject::State::DESTROY);
		}
		++it;
	}
}

void TaskSystem::killTaskGroup(const std::string& group) {
	auto it = tasks_.begin();
	while (it != tasks_.end()) {
		if ((*it)->group() == group) {
			(*it)->changeState(TaskObject::State::DESTROY);
		}
		++it;
	}
}

void TaskSystem::killTask(const int id) {
	auto it = std::find_if(tasks_.begin(), tasks_.end(), [&](TaskObject* t) -> bool {return t->id() == id;});
	if (it != tasks_.end()) {
		(*it)->changeState(TaskObject::State::DESTROY);		
	}

}

TaskObject* TaskSystem::getTask(const std::string& name, const std::string& group) {
	auto it = std::find_if(tasks_.begin(), tasks_.end(), [&](TaskObject* t) -> bool {return t->name() == name && t->group() == group; });
	if (it != tasks_.end()) {
		return (*it);
	}
	return nullptr;
}

std::vector<TaskObject*> TaskSystem::getTaskGroup(const std::string& group) {
	std::vector<TaskObject*> ret;
	for (auto it = tasks_.begin(); it != tasks_.end(); ++it) {
		if ((*it)->group() == group) {
			ret.push_back((*it));
		}
	}	
	return ret;
}

void TaskSystem::updateTasks() {
	for (auto task : tasks_) {
		if (task->state() == TaskObject::State::STOP) { continue; }
		task->update();
	}
	for (auto add : addTasks_) {
		if (add->state() == TaskObject::State::STOP) { continue; }
		add->update();
	}
	//オブジェクトの削除
	for (auto id = tasks_.begin(); id != tasks_.end();) {
		if ((*id)->state() == TaskObject::State::DESTROY) {
			delete (*id);
			id = tasks_.erase(id);
		}
		else {
			++id;
		}
	}
	if (!addTasks_.empty()) {
		//オブジェクトの登録
		for (auto id = addTasks_.begin(); id != addTasks_.end(); ++id) {
			tasks_.emplace_back(*id);
		}
		addTasks_.clear();
	}
	sortByPriority();
}

void TaskSystem::renderTasks() {
	for (auto task : tasks_) {
		task->render();
	}
	for (auto add : addTasks_) {
		add->render();
	}
}

std::unique_ptr<TaskSystem> TaskSystem::instance_(nullptr);