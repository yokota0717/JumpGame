/**
* @file BlockManager.h
* @brief ����u���b�N�̊Ǘ�������N���X���`����
* @author yokota0717
* @date 2018.11.6
* @param history
- 2018.11.13 yokota0717
-# �u���b�N�̃R���e�i��deque�ɕύX
*/

#pragma once
#include "../../System/TaskSystem/TaskSystem.h"
#include "Block.h"
#include <deque>

class BlockManager final : public TaskObject {
private:
	std::deque<std::deque<Block*>> blocks_;
	const int BLOCKNUM_X;
	const int BLOCKNUM_Y;

	//! ��ɒǉ�����u���b�N�������󂫂��ǂ���(�Ȃ񂩂������@�Ȃ�����)
	bool nextIsCenter;

	BlockManager();

	//��ʊO�ɏo����2����폜����N���X
	struct BottomLineDeleter final {
		void deleteLine();
	};
	//��ʊO�㕔�ɐV���Ƀu���b�N�𐶐�����N���X
	struct TopLineCreator final {
		void createLine();
	};

	BottomLineDeleter bottomDeleter_;
	TopLineCreator topCreator_;
public:
	static BlockManager* create();
	~BlockManager();

	//! �u���b�N�̍��W��ݒ肷��
	void setBlockPos(Block* b, int x, int y);

	//! X�����X�N���[���Ή�
	void scrollX();

	//! Y�����X�N���[���Ή�
	void scrollY();

	//! �u���b�N��

	void update() override;
	void render() override;
};