/**
* @file BlockManager.h
* @brief 足場ブロックの管理をするクラスの定義部分
* @author yokota0717
* @date 2018.11.6
* @param history
- 2018.11.15 yokota0717
-# X方向のスクロールに対応
-# Y方向のスクロールに対応
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
	//(注意)y方向下が０
	for (int y = BLOCKNUM_Y - 1; y >= 0; --y) {
		for (int x = 0; x < BLOCKNUM_X; ++x) {
			auto block = Block::create();
			blocks_[y][x] = block;
			//! 座標指定、yが偶数なら中央あき
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
	//左端のブロックの画面外チェック
	for (int y = 0; y < BLOCKNUM_Y; ++y) {
		auto left = blocks_[y][0];
		//画面外に完全に出た
		if (left->getPos().x + left->getSize().x * 2 - 1 < game->camera_.getVisibleArea().x) {
			//反対側に同じ情報のブロックを生成
			auto copy = Block::create();
			copy->setPos(
				Math::Vec(blocks_[y][BLOCKNUM_X - 1]->getPos().x + left->getSize().x * 2,
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
		if (right->getPos().x >= game->camera_.getVisibleArea().x + game->camera_.getVisibleArea().w + 50) {
			//反対側に同じ情報のブロックを生成
			auto copy = Block::create();
			copy->setPos(
				Math::Vec(blocks_[y][0]->getPos().x - right->getSize().x * 2,
					right->getPos().y)
			);
			copy->setType(right->getType());
			//画面外に出たブロックは削除
			TaskSystem::getTaskSystem().killTask(right->id());
			//配列からも削除
			blocks_[y].pop_back();
			//先頭に生成したブロックを追加
			blocks_[y].push_front(copy);
		}
	}
}

void BlockManager::scrollY() {
	auto bottomBlock = blocks_[0][0];
	//下端のブロック2列が画面外に出たら
	if (bottomBlock->getPos().y > game->camera_.getVisibleArea().y + game->camera_.getVisibleArea().h + 130) {
		//下2列を削除する
		for (int y = 0; y < 2; ++y) {
			for (int x = 0; x < BLOCKNUM_X; ++x) {
				TaskSystem::getTaskSystem().killTask(blocks_[y][0]->id());
			}
		}
		blocks_.pop_front();
		blocks_.pop_front();
		//上2列を追加する
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
