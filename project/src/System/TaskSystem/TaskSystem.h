/**
* @file TaskSystem.h
* @brief �^�X�N�Ǘ��V�X�e�����`����
* @author yokota0717
* @date 2018.11.2
*/

#pragma once
#include <vector>
#include "TaskObject.h"
#include <functional>

/**
* @brief �^�X�N�Ǘ��N���X
*/
class TaskSystem final {
private:
	//! �C���X�^���X
	static std::unique_ptr<TaskSystem> instance_;
	//! �o�^���ꂽ�^�X�N�ꗗ
	std::vector<TaskObject*> tasks_;
	//! �o�^�\�񂪂��ꂽ�^�X�N�ꗗ
	std::vector<TaskObject*> addTasks_;

	//std::function<bool(TaskObject* t1, TaskObject* t2)> isLowerPriority_;
	//bool isLeftPriorityLower(const TaskObject* left, const TaskObject* right);

	bool sortPriority(const TaskObject* left, const TaskObject* right) const;

	TaskSystem();
	/**
	* @brief �ێ�����|�C���^��S�ĉ������
	*/
	void releaseMemory();
public:
	~TaskSystem();

	/**
	* @brief �^�X�N�Ǘ��V�X�e���̃C���X�^���X�𓾂�
	*/
	static TaskSystem& getTaskSystem();

	/**
	* @brief �^�X�N��ǉ�����
	* @param task �^�X�N�̃|�C���^
	* @return �ǉ������^�X�N�̃|�C���^
	*/
	TaskObject* addTask(TaskObject* task);

	/**
	* @brief �w�肵�����O�̃^�X�N���폜�\�񂷂�
	* - ���O���[�v�����^�X�N����������ꍇ�͂��ׂč폜�\�񂷂�
	* @param name �폜�������^�X�N�̖��O
	* @param group �폜�������^�X�N��������O���[�v��
	*/
	void killTask(const std::string& name, const std::string& group);
	/**
	* @brief �w�肵���O���[�v�ɑ�����^�X�N��S�č폜�\�񂷂�
	* @param group �폜�������O���[�v��
	*/
	void killTaskGroup(const std::string& group);
	/**
	* @brief �w�肵���^�X�N���폜�\�񂷂�
	* @param id �폜�������^�X�N��ID
	*/
	void killTask(const int id);

	/**
	* @brief �^�X�N���擾����
	* @param name �擾�������^�X�N�̖��O
	* @param group �擾�������^�X�N�̃O���[�v��
	* @return �^�X�N�̃|�C���^
	*/
	[[nodiscard]] TaskObject* getTask(const std::string& name, const std::string& group);
	/**
	* @brief �^�X�N���O���[�v�Ŏ擾����
	* @param group �擾�������O���[�v��
	* @return �^�X�N�̃|�C���^��vector
	*/
	[[nodiscard]] std::vector<TaskObject*> getTaskGroup(const std::string& group);

	/**
	* @brief �o�^�^�X�N��`��D��x���Ƀ\�[�g����
	*/
	void sortByPriority();

	/**
	* @brief �o�^�^�X�N���X�V����
	*/
	void updateTasks();
	/**
	* @brief �o�^�^�X�N�̕`�������
	*/
	void renderTasks();
	
};