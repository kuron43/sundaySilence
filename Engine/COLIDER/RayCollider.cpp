#include "RayCollider.h"

void RayCollider::Update() {
	if (object3d_)
	{
		//ワールド行列から座標を抽出
		const Matrix4& matWorld = object3d_->wtf.matWorld;

		//球のメンバ変数を更新
		Ray::start_ = Affin::GetWorldTrans(matWorld);
		Ray::dir_ = dir_;
		
	}
	else
	{
		Ray::start_ = {0,0,0};
		Ray::dir_ = { 1,0,0 };
	}

	isHit = false;
}