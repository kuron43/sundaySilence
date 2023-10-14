#pragma once
#include "Input.h"
#include "DirectXCommon.h"
#include "Object3d.h"
#include "Sprite.h"
#include "SpriteCommon.h"
class Cursor
{
public:
	Cursor();
	~Cursor();
	/// シーンの初期化を行う
	void Initialize(SpriteCommon* spriteCommon);
	/// シーンの更新を行う
	void Update(Input* input);
	/// シーンの描画を行う
	void Draw();

	void CusUpdate(Input* input);
private:

	Vector2 mousepos_;
	Vector2 spritePos_;
private://リソース
	std::unique_ptr <Sprite> cursorPic_;

public:
	// カーソルと画像の当たり判定
	bool Cursor2Sprite(Sprite* sprite);
private:
	//代入演算子削除
	Cursor& operator=(const Cursor&) = delete;
	//コピーコンストラクタ削除
	Cursor(const Cursor&) = delete;
};

