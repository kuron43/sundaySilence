#pragma once
#include "Objects.h"

class Wall :
    public Objects
{
public:
	Wall();
	~Wall()override;


	/// シーンの更新を行う
	void Initialize(Model* model)override;

	void CollideInitialize();

	/// シーンの更新を行う
	void Update()override;

	/// シーンの描画を行う
	void Draw(DirectXCommon* dxCommon)override;

	/// リセットを行う
	void Reset() override;

	//コライダー
public:
	void SetSphere(ObbCollider* obb) { obb_ = obb; }
	ObbCollider* GetSphere() { return obb_; }
private:

	ObbCollider* obb_;
	Object3d* coliderPosTest_;
public:
	Object3d* object_;
	Model* model_;
private:
	ObbCollider GetObb() { return *obb_; }
	bool isHit;
};

