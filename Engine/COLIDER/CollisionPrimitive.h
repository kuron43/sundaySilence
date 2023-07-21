#pragma once
#include"DirectXMath.h"
#include "Affin.h"

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

struct OBB
{
public:
	Vector3 m_Pos;              // 位置
	Vector3 m_NormaDirect[3];   // 方向ベクトル
	float m_fLength[3];             // 各軸方向の長さ
};
//	http://marupeke296.com/COL_3D_No13_OBBvsOBB.html