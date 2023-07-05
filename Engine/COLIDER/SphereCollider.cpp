#include "SphereCollider.h"

void SphereCollider::Update()
{
	if (object3d_)
	{
		//ワールド行列から座標を抽出
		const Matrix4& matWorld = object3d_->wtf.matWorld;

		//球のメンバ変数を更新
		Sphere::center =
		{
			matWorld.m[3][0] + offset.x ,
			matWorld.m[3][1] + offset.y ,
			matWorld.m[3][2] + offset.z
		};
	}
	else if (basisPos)
	{
		Sphere::center = *basisPos + offset;
	}
	else
	{
		Sphere::center = {0 , 0 , 0};
	}


	Sphere::radius_ = radius_;

	isHit = false;
}