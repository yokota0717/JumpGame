/**
* @file Image.h
* @brief 画像描画に関するクラスを定義する
* @author yokota0717
* @date 2018.10.27
* @param history
- 2018.11.20 yokota0717
-# 回転および拡大縮小つき描画関数を追加
-# 画像サイズの取得関数を追加
*/

#pragma once
#include <string>
#include <vector>
#include "DxLib.h"
#include "../Math/Math.h"


class Image
{
	//! 画像ハンドル
	int handle_;
	int* handleDiv_;
public:
	/**
	* @brief 画像ハンドルを設定する
	*/
	Image();
	~Image();

	/**
	* @brief 画像ハンドルを設定する
	* - 単一で使う画像の読み込みに使う
	* @param path 画像のパス
	*/
	void setHandle(const std::string& path);

	/**
	* @brief
	* - 分割して使う画像の読み込みに使う
	* @param path 画像のパス
	*/
	void setHandleDiv(const std::string& path, const int allNum, const int xNun, const int yNun, const int xSize, const int ySize);

	/**
	* @brief 単一で読み込んだ画像の描画関数、アニメーションはしない
	* @param draw 描画する座標
	* @param center ピボットを画像の中心にする
	* - trueならピボットが中央
	* - falseならピボットが左上
	*/
	void draw(const Math::Vec& pos, const bool isCenter);

	/**
	* @brief 分割して読み込んだ画像の描画関数、アニメーションはしない
	* @param draw 描画する座標
	* @param index 描画する画像のインデックス
	* @param center ピボットを画像の中心にする
	* - trueならピボットが中央
	* - falseならピボットが左上
	*/
	void draw(const Math::Vec& pos, const int index, const bool isCenter);

	/**
	* @brief 一枚絵の指定した範囲を切り出して描画
	* @param pos 描画する座標
	* @param src 元画像の描画する範囲
	* @param turnFlag 反転するかどうか
	*/
	void drawRect(const Math::Vec& pos, const Math::Box2D& src, const bool turnFlag);

	/**
	* @brief 単一で読み込んだ画像の描画、回転拡縮あり
	* @param pos 描画する座標
	* @param scale 拡大率
	* @param angle 回転角度(ラジアン)
	* @param isTurn 画像を反転するかどうか
	*/
	void drawExtRota(const Math::Vec& pos, const Math::Vec& scale, const float angle, const bool isTurn);

	/**
	* @brief 分割して読み込んだ画像の描画、回転拡縮あり
	* @param pos 描画する座標
	* @param scale 拡大率
	* @param angle 回転角度(ラジアン)
	* @param index 描画する画像のインデックス
	* @param isTurn 画像を反転するかどうか
	*/
	void drawExtRota(const Math::Vec& pos, const Math::Vec& scale, const float angle, const int index, const bool isTurn);

	/**
	* @brief 読み込み済みの画像のサイズを取得する
	* @return 画像のサイズ
	*/
	Math::Vec getGraphSize();

	//! ハンドルを取得する(要らないかも)
	int getHandle();
};