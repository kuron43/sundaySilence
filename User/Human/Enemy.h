#pragma once
#include "Human.h"
class Enemy :
    public Human
{
public:
	Enemy();
	~Enemy()override;


	/// シーンの更新を行う
	void Initialize()override;

	/// シーンの更新を行う
	void Update(Input* input)override;

	/// シーンの描画を行う
	void Draw(DirectXCommon* dxCommon)override;

	/// リセットを行う
	void Reset() override;

private:
	Model* model_;
	Object3d* object_;
	Vector3 faceAngle_;

};

