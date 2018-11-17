/**
* @file TaskSystem.h
* @brief タスク管理システムを定義する
* @author yokota0717
* @date 2018.11.2
*/

#pragma once
#include <vector>
#include "TaskObject.h"
#include <functional>

/**
* @brief タスク管理クラス
*/
class TaskSystem final {
private:
	//! インスタンス
	static std::unique_ptr<TaskSystem> instance_;
	//! 登録されたタスク一覧
	std::vector<TaskObject*> tasks_;
	//! 登録予約がされたタスク一覧
	std::vector<TaskObject*> addTasks_;

	//std::function<bool(TaskObject* t1, TaskObject* t2)> isLowerPriority_;
	//bool isLeftPriorityLower(const TaskObject* left, const TaskObject* right);

	bool sortPriority(const TaskObject* left, const TaskObject* right) const;

	TaskSystem();
	/**
	* @brief 保持するポインタを全て解放する
	*/
	void releaseMemory();
public:
	~TaskSystem();

	/**
	* @brief タスク管理システムのインスタンスを得る
	*/
	static TaskSystem& getTaskSystem();

	/**
	* @brief タスクを追加する
	* @param task タスクのポインタ
	* @return 追加したタスクのポインタ
	*/
	TaskObject* addTask(TaskObject* task);

	/**
	* @brief 指定した名前のタスクを削除予約する
	* - 同グループ同名タスクが複数ある場合はすべて削除予約する
	* @param name 削除したいタスクの名前
	* @param group 削除したいタスクが属するグループ名
	*/
	void killTask(const std::string& name, const std::string& group);
	/**
	* @brief 指定したグループに属するタスクを全て削除予約する
	* @param group 削除したいグループ名
	*/
	void killTaskGroup(const std::string& group);
	/**
	* @brief 指定したタスクを削除予約する
	* @param id 削除したいタスクのID
	*/
	void killTask(const int id);

	/**
	* @brief タスクを取得する
	* @param name 取得したいタスクの名前
	* @param group 取得したいタスクのグループ名
	* @return タスクのポインタ
	*/
	[[nodiscard]] TaskObject* getTask(const std::string& name, const std::string& group);
	/**
	* @brief タスクをグループで取得する
	* @param group 取得したいグループ名
	* @return タスクのポインタのvector
	*/
	[[nodiscard]] std::vector<TaskObject*> getTaskGroup(const std::string& group);

	/**
	* @brief 登録タスクを描画優先度順にソートする
	*/
	void sortByPriority();

	/**
	* @brief 登録タスクを更新する
	*/
	void updateTasks();
	/**
	* @brief 登録タスクの描画をする
	*/
	void renderTasks();
	
};