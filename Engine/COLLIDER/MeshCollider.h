#pragma once
#include "BaseCollider.h"
#include "CollisionPrimitive.h"

class MeshCollider:public BaseCollider
{
public:
	MeshCollider()
	{
		shapeType = COLLISIONSHAPE_MESH;
	}

	//三角形の配列を構築する
	void ConstructTriangles(Model* model);

	//更新処理
	void Update() override;

	//球との当たり判定
	bool CheckCollisionSphere(const Sphere& sphere , Vector3* inter = nullptr,Vector3* reject = nullptr);

	//レイとの当たり判定
	bool CheckCollisionRay(const Ray& ray , float* distance = nullptr , Vector3* inter = nullptr);

private:
	std::vector<Triangle> triangles;

	//ワールド行列の逆行列
	Matrix4 objectMatWorld;

};

