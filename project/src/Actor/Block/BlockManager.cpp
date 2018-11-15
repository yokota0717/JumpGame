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
			//! 座標指定、yが偶数なら中央あき
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
	//左端のブロックの画面外チェック
	for (int y = 0; y < BLOCKNUM_Y; ++y) {
		auto left = blocks_[y][0];
		//画面外に完全に出た
		if (left->getPos().x + left->getSize().x * 2 - 1 < game->camera_.getVisibleArea().x) {
			//反対側に同じ情報のブロックを生成
			auto copy = Block::create();
			copy->setPos(
				Math::Vec(game->camera_.getVisibleArea().x + game->camera_.getVisibleArea().w, 
					left->getPos().y)
			);
			copy->setType(left->getType());
			//画面外に出たブロックは削除
			TaskSystem::getTaskSystem().killTask(left->id());
			//配列からも削除
			blocks_[y].pop_front();
			//最後尾に生成したブロックを追加
			blocks_[y].emplace_back(copy);
		}
	}
	//右端のブロックの画面外チェック
	for (int y = 0; y < BLOCKNUM_Y; ++y) {
		auto right = blocks_[y][BLOCKNUM_X - 1];
		//画面外に完全に出た
		if (right->getPos().x >= game->camera_.getVisibleArea().x + game->camera_.getVisibleArea().w + 100) {
			//反対側に同じ情報のブロックを生成
			auto copy = Block::create();
			copy->setPos(
				Math::Vec(game->camera_.getVisibleArea().x - right->getSize().x * 1,
					right->getPos().y)
			);
			copy->setType(right->getType());
			//画面外に出たブロックは削除
			TaskSystem::getTaskSystem().killTask(right->id());
			//配列からも削除
			blocks_[y].pop_back();
			//最後尾に生成したブロックを追加
			blocks_[y].push_front(copy);
		}
	}
}

void BlockManager::scrollY() {
	auto topBlock = blocks_[0][0];
	auto bottomBlock = blocks_[BLOCKNUM_Y][0];

	//上部に追加する
	if (topBlock->getPos().y <= topBlock->getSize().y) {
		
	}
	//下2列を削除する
	if (bottomBlock->getPos().y > game->camera_.getVisibleArea().y + bottomBlock->getSize().y * 10/*仮*/) {

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
