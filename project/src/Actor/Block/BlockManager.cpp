#include "BlockManager.h"
#include "../../define.h"
#include "../../Scene/GameManager.h"

BlockManager::BlockManager()
	:
	TaskObject("blockManager", "block", TaskObject::State::RUN),
	BLOCKNUM_X(4),
	BLOCKNUM_Y(5),
	nextIsCenter(false)
{
	blocks_.resize(BLOCKNUM_Y);
	for (int y = 0; y < BLOCKNUM_Y; ++y) {
		blocks_[y].resize(BLOCKNUM_X);
	}
	for (int y = 0; y < BLOCKNUM_Y; ++y) {
		for (int x = 0; x < BLOCKNUM_X; ++x) {
			auto block = Block::create();
			blocks_[y][x] = block;
			//! ���W�w��Ay�������Ȃ璆������
			block->setPos(
				Math::Vec(-50 + (y % 2 * 100) + (block->getSize().x + 100)*x,
					100 + (block->getSize().y + 130) * y)
			);
			block->setType(Block::Type::NOMAL);
			if (x == 0) {
				block->setType(Block::Type::COIN);
			}
			if (x == 3) {
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
				Math::Vec(game->camera_.getVisibleArea().x + game->camera_.getVisibleArea().w, 
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
		if (right->getPos().x >= game->camera_.getVisibleArea().x + game->camera_.getVisibleArea().w + 100) {
			//���Α��ɓ������̃u���b�N�𐶐�
			auto copy = Block::create();
			copy->setPos(
				Math::Vec(game->camera_.getVisibleArea().x - right->getSize().x * 1,
					right->getPos().y)
			);
			copy->setType(right->getType());
			//��ʊO�ɏo���u���b�N�͍폜
			TaskSystem::getTaskSystem().killTask(right->id());
			//�z�񂩂���폜
			blocks_[y].pop_back();
			//�Ō���ɐ��������u���b�N��ǉ�
			blocks_[y].push_front(copy);
		}
	}
}

void BlockManager::scrollY() {
	auto topBlock = blocks_[0][0];
	auto bottomBlock = blocks_[BLOCKNUM_Y][0];

	//�㕔�ɒǉ�����
	if (topBlock->getPos().y <= topBlock->getSize().y) {
		
	}
	//��2����폜����
	if (bottomBlock->getPos().y > game->camera_.getVisibleArea().y + bottomBlock->getSize().y * 10/*��*/) {

	}
}

void BlockManager::update() {
	scrollX();
	DOUT << blocks_[1][3]->getIsInCamera() << std::endl;
}

void BlockManager::render()
{
}

void BlockManager::BottomLineDeleter::deleteLine() {

}

void BlockManager::TopLineCreator::createLine() {

}
