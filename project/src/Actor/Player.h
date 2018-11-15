/**
* @file	Player.h
* @brief �v���C���N���X
* @author yokota0717
* @date 2018.11.6
*/

#pragma once
#include "../System/TaskSystem/TaskObject.h"
#include "../System/Image/Image.h"
#include "../System/Collision/Collision.h"

/**
* @brief �v���C���N���X
* @todo
* - ���E�L�[�ŃW�����v�����������
* - �J�������Ǐ]����
* - �����������ɂ���ăX�R�A�����Z����
* - ���n��������̎�ނɂ���Ĕ�����ς���
* - �A�j���[�V��������
*/
class Player final : public TaskObject {
public:
	enum Angle {
		L,
		R,
		F,
	};
private:
	//! �s�N�Z���P�ʂ̌��ݍ��W
	Math::Vec draw_;
	//! ����
	Angle angle_;
	//! �摜(���摜)
	Image image_;
	//! �����蔻��(�v�邩�H)
	Math::Box2DCollider col_;

	//! �B���R���X�g���N�^
	Player();
	//! �W�����v����
	void jump(Angle angle);
public:
	//! ��������
	static Player* create();

	void update() override;
	void render() override;
};