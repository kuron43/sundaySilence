#pragma once
#include"DirectXMath.h"
#include"Vector3.h"
#include"Vector4.h"

struct Sphere {
	//中心座標
	Vector3 center = { 0,0,0 };
	//半径
	float radius_ = 1.0f;
};

struct Plane {
	//法線ベクトル
	Vector3 normal = { 0,1,0 };
	//原点(0,0,0)からの距離
	float distance = 0.0f;
};

class Triangle {
public:
	//頂点座標
	Vector3 p0;
	Vector3 p1;
	Vector3 p2;
	//法線ベクトル
	Vector3 normal;

	//法線の計算
	void ComputeNormal();

};

struct Ray {
	//始点
	Vector3 start;
	//方向
	Vector3 dir;
};