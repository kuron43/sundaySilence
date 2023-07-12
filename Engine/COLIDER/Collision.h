#pragma once
#include "CollisionPrimitive.h"

class Collision
{
public:
	//球と球の当たり判定
	static bool CheckSphere2Sphere(const Sphere& sphereA , const Sphere& sphereB , Vector3* inter = nullptr, Vector3* reject = nullptr);

	//弾と平面の当たり判定
	static bool CheckSphere2Plane(const Sphere& sphere , const Plane& plane , Vector3* inter = nullptr, Vector3* reject = nullptr);

	//点と三角形の最近接点を求める
	static void ClosestPtPoint2Triangle(const Vector3& point , const Triangle& triangle , Vector3* closest, Vector3* reject = nullptr);
	//レイと三角形の当たり判定
	static bool CheckSphere2Triangle(const Sphere& sphere , const Triangle& triangle , Vector3* inter = nullptr, Vector3* reject = nullptr);

	//レイと平面の当たり判定
	static bool CheckRay2Plane(const Ray& ray , const Plane& plane , float* distance = nullptr , Vector3* inter = nullptr, Vector3* reject = nullptr);

	//レイと三角形の当たり判定
	static bool CheckRay2Triangle(const Ray& ray , const Triangle& triangle , float* distance = nullptr , Vector3* inter = nullptr, Vector3* reject = nullptr);

	static bool CheckRay2Sphere(const Ray& ray , const Sphere& sphere , float* distance = nullptr , Vector3* inter = nullptr, Vector3* reject = nullptr);

};

