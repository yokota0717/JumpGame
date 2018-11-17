/**
* @file BlockManager.h
* @brief ����u���b�N�̊Ǘ�������N���X�̒�`����
* @author yokota0717
* @date 2018.11.6
* @param history
- 2018.11.15 yokota0717
-# X�����̃X�N���[���ɑΉ�
-# Y�����̃X�N���[���ɑΉ�
*/



#include "BlockManager.h"
#include "../../define.h"
#include "../../Scene/GameManager.h"

BlockManager::BlockManager()
	:
	TaskObject("blockManager", "block", TaskObject::State::RUN),
	BLOCKNUM_X(4),
	BLOCKNUM_Y(10)
{
	blocks_.resize(BLOCKNUM_Y);
	for (int y = 0; y < BLOCKNUM_Y; ++y) {
		blocks_[y].resize(BLOCKNUM_X);
	}
	//(����)y���������O
	for (int y = BLOCKNUM_Y - 1; y >= 0; --y) {
		for (int x = 0; x < BLOCKNUM_X; ++x) {
			auto block = Block::create();
			blocks_[y][x] = block;
			//! ���W�w��Ay�������Ȃ璆������
			block->setPos(
				Math::Vec(-50 + (y % 2 * 100) + (block->getSize().x + 100)*x,
					SCREEN_HEIGHT - 281 - (block->getSize().y + 130) * y)
			);
			block->setType(Block::Type::NOMAL);
			if (x == 0) {
				block->setType(Block::Type::COIN);
			}
			if (x == BLOCKNUM_X-1) {
				block->setType(Block::Type::NEEDLE);
			}
		}
	}
}

BlockManager* BlockManager::create() {
	auto b = new BlockManager();
	TaskSystem::getTaskSystem().addTask(b);
	return b;
}

BlockManager::~BlockManager() {

}

void BlockManager::setBlockPos(Block* b, int x, int y) {

}

void BlockManager::scrollX() {
	//���[�̃u���b�N�̉�ʊO�`�F�b�N
	for (int y = 0; y < BLOCKNUM_Y; ++y) {
		auto left = blocks_[y][0];
		//��ʊO�Ɋ��S�ɏo��
		if (left->getPos().x + left->getSize().x * 2 - 1 < game->camera_.getVisibleArea().x) {
			//���Α��ɓ������̃u���b�N�𐶐�
			auto copy = Block::create();
			copy->setPos(
				Math::Vec(blocks_[y][BLOCKNUM_X - 1]->getPos().x + left->getSize().x * 2,
					left->getPos().y)
			);
			copy->setType(left->getType());
			//��ʊO�ɏo���u���b�N�͍폜
			TaskSystem::getTaskSystem().killTask(left->id());
			//�z�񂩂���폜
			blocks_[y].pop_front();
			//�Ō���ɐ��������u���b�N��ǉ�
			blocks_[y].emplace_back(copy);
		}
	}
	//�E�[�̃u���b�N�̉�ʊO�`�F�b�N
	for (int y = 0; y < BLOCKNUM_Y; ++y) {
		auto right = blocks_[y][BLOCKNUM_X - 1];
		//��ʊO�Ɋ��S�ɏo��
		if (right->getPos().x >= game->camera_.getVisibleArea().x + game->camera_.getVisibleArea().w + 50) {
			//���Α��ɓ������̃u���b�N�𐶐�
			auto copy = Block::create();
			copy->setPos(
				Math::Vec(blocks_[y][0]->getPos().x - right->getSize().x * 2,
					right->getPos().y)
			);
			copy->setType(right->getType());
			//��ʊO�ɏo���u���b�N�͍폜
			TaskSystem::getTaskSystem().killTask(right->id());
			//�z�񂩂���폜
			blocks_[y].pop_back();
			//�擪�ɐ��������u���b�N��ǉ�
			blocks_[y].push_front(copy);
		}
	}
}

void BlockManager::scrollY() {
	auto bottomBlock = blocks_[0][0];
	//���[�̃u���b�N2�񂪉�ʊO�ɏo����
	if (bottomBlock->getPos().y > game->camera_.getVisibleArea().y + game->camera_.getVisibleArea().h + 130) {
		//��2����폜����
		for (int y = 0; y < 2; ++y) {
			for (int x = 0; x < BLOCKNUM_X; ++x) {
				TaskSystem::getTaskSystem().killTask(blocks_[y][0]->id());
			}
		}
		blocks_.pop_front();
		blocks_.pop_front();
		//��2���ǉ�����
		auto nowTop = blocks_[BLOCKNUM_Y - 3][0];
 		for (int y = 0; y < 2; ++y) {
			std::deque<Block*> line;
			for (int x = 0; x < BLOCKNUM_X; ++x) {
				auto block = Block::create();
				block->setPos(
					Math::Vec(
						nowTop->getPos().x + 100 * (1 - y) + 200 * x,
						nowTop->getPos().y - 160 * (y + 1))
				);
				block->setType(Block::Type(x%3));
				line.push_back(block);
			}
			blocks_.push_back(line);
		}
	}
}

void BlockManager::update() {
	scrollX();
	scrollY();
}

void BlockManager::render() {}

void BlockManager::BottomLineDeleter::deleteLine() {

}

void BlockManager::TopLineCreator::createLine() {

}
