/**
* @file Camera.h
* @brief �J�����N���X���`����
* @author yokota0717
* @date 2018.11.8
* @param history
- 2018.11.11 yokota0717
-# �^�[�Q�b�g�ɒǏ]���鏈����ǉ�
- 2018.11.12 yokota0717
-# �`��͈͂̃Q�b�^�[�쐬
*/

#pragma once
#include "../Math/Math.h"
#include "../TaskSystem/TaskObject.h"

class Camera2D final {
private:
	//! �J�����̍���̍��W
	Math::Vec pos_;
	//! �J�����T�C�Y
	Math::Vec size_;
	//! �J�����ɉf��͈�
	Math::Box2D visibleArea_;
	//! �J�����̉�]�p�x(degree)(������)
	float rotation_;
	//! �J�����̊g�嗦(������)
	Math::Vec scale_;
	//! ���S�ɂƂ炦��^�[�Q�b�g
	TaskObject* target_;

public:
	Camera2D(int width, int height);
	~Camera2D() = default;

	//! �J�������w��x�N�g�����ړ�������
	void move(const Math::Vec& est);

	//! �J�������w�肵�����W�Ɉړ�������
	void setPos(const Math::Vec& pos);

	//! ���ݍ��W��Ԃ�(������W)
	Math::Vec& getPos();

	//! �T�C�Y��Ԃ�
	Math::Vec& getSize();

	//! �`��͈͂�Ԃ�
	Math::Box2D& getVisibleArea();

	//! ���S�ɂƂ炦��^�[�Q�b�g��ݒ肷��
	void setTarget(TaskObject* target);

	/**
	* @brief �^�[�Q�b�g�ɒǏ]����X�V����
	* @note �^�[�Q�b�g���w�肵���ꍇ�ɂ��̃V�[����update�ŌĂԂ���
	* �^�[�Q�b�g�̎w�肪�Ȃ��ꍇ�͉������Ȃ�
	*/
	void chaseTarget();

	void setCenter(Math::Vec& center);
};