#pragma once
/**
 * @file Floor.h
 * @brief
 */
#include "Objects.h"

class Floor :
	public Objects
{
public:
	Floor();
	~Floor()override;


	/// シーンの初期化を行う
	void Initialize(Model* model)override;

	void CollideInitialize();

	/// シーンの更新を行う
	void Update()override;

	/// シーンの描画を行う
	void Draw(DirectXCommon* dxCommon)override;

	/// リセットを行う
	void Reset() override;


public:
	Object3d* object_;
private:
	bool isHit;
};

