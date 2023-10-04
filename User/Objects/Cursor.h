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
	/// シーンの更新を行う
	void Initialize(SpriteCommon* spriteCommon);
	/// シーンの更新を行う
	void Update(Input* input);
	/// シーンの描画を行う
	void Draw(DirectXCommon* dxCommon);

	void CusUpdate(Input* input);

	Vector2 GetCursorPos() { return cursorPic_->GetPosition(); };
private:
	Model* model_;
	Object3d* object_;

	Vector2 mousepos_;
	float mouseSensitivity_ = 0.05f;	//マウス感度 0.05
	Vector2 spritePos_;
private://リソース
	std::unique_ptr <Sprite> cursorPic_;

public:
	bool Cursor2Sprite(Sprite sprite);
};

