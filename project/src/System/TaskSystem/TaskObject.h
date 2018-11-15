/**
* @file TaskObject.h
* @brief �^�X�N���N���X���`����
* @author yokota0717
* @date 2018.11.2
* @param history
- 2018.11.11 yokota0717
-# ���W����������
*/

#pragma once
#include <string>
#include "../Math/Math.h"

/**
* @brief �^�X�N���N���X
*/
class TaskObject {
public:
	enum class State {
		NON,		//! ����`
		RUN,		//! �ʏ�
		STOP,		//! ��~
		DESTROY,	//! �폜�\��
	};
private:
	//! �ŗLID�A�I�u�W�F�N�g�������ɃC���N�������g�����
	static int uid_;
	//! ID
	int id_;
	//! �ŗL�̖��O
	std::string name_;
	//! ������O���[�v��
	std::string group_;
	//! �쓮���
	State state_;
	//! �`��D��x
	float drawPriority_;

	//! ���W
	Math::Vec pos_;

public:
	TaskObject(const std::string& name, const std::string& group, const State state);
	virtual ~TaskObject() = default;

	/**
	* @brief �`��D��x��ݒ肷��
	* - ���l���傫���قǎ�O�ɕ`�悳���
	* @param priority �`��D��x
	*/
	void setPriority(const float priority);
	/**
	* @brief �쓮��Ԃ�ύX����
	* @param state �w�肷��쓮���
	*/
	void changeState(const State state);
	/**
	* @brief ���O��ύX����
	* @param name �V�������O
	* @return �ύX�O�̖��O
	*/
	std::string changeName(const std::string& name);
	/**
	* @brief �O���[�v��ύX����
	* @param name �V�����O���[�v��
	* @return �ύX�O�̃O���[�v��
	*/
	std::string changeGroup(const std::string& group);

	/**
	* @brief �^�X�N�Ƀ��b�Z�[�W�𑗂�
	* @param sender ���b�Z�[�W�𑗂�^�X�N�̃|�C���^
	* @param receiver ���b�Z�[�W���󂯎��^�X�N�̃|�C���^
	* @msg ���b�Z�[�W
	*/
	void postMsg(TaskObject* sender, TaskObject* receiver, std::string& msg);
	/**
	* @brief �^�X�N����̃��b�Z�[�W�󂯎��֐�
	* @param sender ���b�Z�[�W�𑗂�^�X�N�̃|�C���^
	* @param msg ���b�Z�[�W
	*/
	virtual void receiveMsg(TaskObject* sender, std::string& msg);

	/**
	* @brief ���W��ݒ肷��
	* @param pos �w�肷����W
	*/
	void setPos(Math::Vec pos);

	virtual void init() {};
	virtual void update() = 0;
	virtual void render() = 0;

	//! ���O���擾����
	[[nodiscard]] const std::string& name();

	//! �O���[�v�����擾����
	[[nodiscard]] const std::string& group();

	//! �쓮��Ԃ��擾����
	[[nodiscard]] const State& state();

	//! ID���擾����
	[[nodiscard]] const int id();

	//! �쓮��Ԃ��ʏ�Ȃ�true
	[[nodiscard]] const bool isRun();

	//! �쓮��Ԃ���~�Ȃ�true
	[[nodiscard]] const bool isStop();

	//! �쓮��Ԃ��폜�\��Ȃ�true
	[[nodiscard]] const bool isDestroy();

	//! ���ݍ��W���擾����
	Math::Vec& getPos();


	//! ��r���Z�q�̃I�[�o�[���[�h
	bool operator < (const TaskObject& v);
};

