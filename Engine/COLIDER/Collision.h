#pragma once
#include "CollisionPrimitive.h"
#include <vector>

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

	// OBB

	static bool CheckOBB2Sphere(const OBB& obb, const Sphere& sphere,Vector3* inter = nullptr, Vector3* reject = nullptr);

	static bool CheckOBB2OBB(const OBB& obb1,const OBB& obb2, Vector3* inter = nullptr, Vector3* reject = nullptr);

	static bool CheckOBB2RAY(const OBB& obb, const Ray& ray, Vector3* inter = nullptr, Vector3* reject = nullptr);

private:

	// 3次元OBBと点の最短距離算出関数
	static float LenOBBToPoint(OBB& obb, Vector3& p, Vector3* reject = nullptr);
	// http://marupeke296.com/COL_3D_No12_OBBvsPoint.html
	

	// 分離軸に投影された軸成分から投影線分長を算出
	static float LenSegOnSeparateAxis(Vector3& Sep, Vector3& e1, Vector3& e2, Vector3& e3)
	{
		// 3つの内積の絶対値の和で投影線分長を計算
		// 分離軸Sepは標準化されていること
		float r1 = (float)fabs((double)Sep.dot(e1));
		float r2 = (float)fabs((double)Sep.dot(e2));
		float r3 =  (float)fabs((double)Sep.dot(e3));
		return r1 + r2 + r3;
	}

	static float LenSegOnSeparateAxis(Vector3& Sep, Vector3& e1, Vector3& e2)
	{
		// 3つの内積の絶対値の和で投影線分長を計算
		// 分離軸Sepは標準化されていること
		float r1 = (float)fabs((double)Sep.dot(e1));
		float r2 = (float)fabs((double)Sep.dot(e2));
		return r1 + r2;
	}// http://k3tec.net/neko_wiki/index.php?DirectX%B9%D6%BA%C222%B2%F3
};

