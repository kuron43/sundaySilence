#include "RayCollider.h"

RayCollider::RayCollider(Vector3 start, Vector3 dir) :
	start_(start),
	dir_(dir)
{
	//球形状をセット
	shapeType = COLLISIONSHAPE_RAY;
}

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

void RayCollider::SetStart(Vector3 start)
{
	start_ = start;
}

Vector3 RayCollider::GetStart()
{
	return 	start_;
}

void RayCollider::SetDir(Vector3 dir)
{
	dir_ = dir;
}

Vector3 RayCollider::GetDir()
{
	return dir_;
}
