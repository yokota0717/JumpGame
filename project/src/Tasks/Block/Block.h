/**
* @file Block.h
* @brief ����u���b�N�N���X���`����
* @author yokota0717
* @date 2018.11.6
*/

#pragma once
#include "../../System/TaskSystem/TaskSystem.h"
#include "../../System/Math/Math.h"
#include "../../System/Image/Image.h"
#include "../../System/Collision/Collision.h"

class Block final : public TaskObject {
public:
	enum Type {
		NOMAL,
		COIN,
		NEEDLE,
	};
private:
	//! �傫��
	Math::Vec size_;
	//! �u���b�N�^�C�v
	Type type_;
	//! �摜
	Image image_;
	//! �����蔻���`
	Math::Box2DCollider col_;
	//! �J�����Ɉ�x�ł��f���true(�J��������o������̂���) �g���ĂȂ�
	bool inCamera_;


	//! �B���R���X�g���N�^
	Block();
	//! �J�����ɉf���Ă��邩���肷��
	bool isInCamera();
public:
	//! ��������
	static Block* create();
	~Block();

	void setType(const Type type);
	void setPos(const Math::Vec& pos);

	bool getIsInCamera() const;  //�g���ĂȂ�

	Math::Vec& getSize();
	Type getType() const;

	void update() override;
	void render() override;
};