/**
* @file BlockManager.h
* @brief 足場ブロックの管理をするクラスを定義する
* @author yokota0717
* @date 2018.11.6
* @param history
- 2018.11.13 yokota0717
-# ブロックのコンテナをdequeに変更
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

	//! 上に追加するブロックが中央空きかどうか(なんかいい方法ないかな)
	bool nextIsCenter;

	BlockManager();

	//画面外に出た下2列を削除するクラス
	struct BottomLineDeleter final {
		void deleteLine();
	};
	//画面外上部に新たにブロックを生成するクラス
	struct TopLineCreator final {
		void createLine();
	};

	BottomLineDeleter bottomDeleter_;
	TopLineCreator topCreator_;
public:
	static BlockManager* create();
	~BlockManager();

	//! ブロックの座標を設定する
	void setBlockPos(Block* b, int x, int y);

	//! X方向スクロール対応
	void scrollX();

	//! Y方向スクロール対応
	void scrollY();

	//! ブロックを

	void update() override;
	void render() override;
};