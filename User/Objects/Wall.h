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
public:
	Object3d* object_;
	Model* model_;
private:

	//コライダー
public:
	void SetSphere(ObbCollider* obb) { obb_ = obb; }
	ObbCollider* GetSphere() { return obb_; }
private:
	ObbCollider* obb_;
	Vector3 obbPos_;
	Vector3 obbLength_;
	Object3d* coliderPosTest_;
};

