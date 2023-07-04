#include "MeshCollider.h"
#include "Collision.h"
#include "imgui.h"

//三角形の配列を構築する
void MeshCollider::ConstructTriangles(Mesh* model)
{
	//三角形リストをクリア
	triangles.clear();

	//インデックス配列を取得
	const std::vector<unsigned short>& indices = model->GetInidices();
	const std::vector<Mesh::VertexPosNormalUv>& vertices = model->GetVertices();

	int start = 0;

	std::vector<unsigned short>::const_iterator it = indices.cbegin();

	for (; it != indices.cend(); it += 3)
	{
		size_t triangleNum = indices.size() / 3;

		triangles.resize(triangles.size() + triangleNum);

		for (int i = 0; i < triangleNum; i++)
		{
			Triangle& tri = triangles[start + i];
			int idx0 = indices[i * 3 + 0];
			int idx1 = indices[i * 3 + 1];
			int idx2 = indices[i * 3 + 2];

			tri.p0 = {vertices[idx0].pos.x , vertices[idx0].pos.y , vertices[idx0].pos.z};
			tri.p1 = {vertices[idx1].pos.x , vertices[idx1].pos.y , vertices[idx1].pos.z};
			tri.p2 = {vertices[idx2].pos.x , vertices[idx2].pos.y , vertices[idx2].pos.z};

			tri.ComputeNormal();
		}

		start += (int)triangleNum;
	}

}

//更新処理
void MeshCollider::Update()
{
	objectMatWorld = GetObject3d()->GetMatWorld();
}

//球との当たり判定
bool MeshCollider::CheckCollisionSphere(const Sphere& sphere , Vector3* inter)
{
	Sphere localSphere;

	localSphere.center = {
		sphere.center.x - objectMatWorld.m[3][0] ,
		sphere.center.y - objectMatWorld.m[3][1] ,
		sphere.center.z - objectMatWorld.m[3][2]};

	localSphere.radius *= sphere.radius;

	std::vector<Triangle>::const_iterator it = triangles.cbegin();

	if (localSphere.radius < 1.0f)
	{
		int a = 0;
		a++;
	}

	for (; it != triangles.cend(); ++it)
	{
		const Triangle& triangle = *it;
		if (Collision::CheckSphere2Triangle(localSphere , triangle , inter))
		{
			if (inter)
			{
				const Matrix4& matWorld = GetObject3d()->GetMatWorld();

				Matrix4 interMat;
				interMat.identity();
				interMat.m[3][0] = inter->x;
				interMat.m[3][1] = inter->y;
				interMat.m[3][2] = inter->z;
				interMat *= matWorld;

				inter->x = interMat.m[3][0];
				inter->y = interMat.m[3][1];
				inter->z = interMat.m[3][2];

			}

			return true;
		}
	}

	return false;
}

bool MeshCollider::CheckCollisionRay(const Ray& ray , float* distance , Vector3* inter)
{
	Ray localRay;

	localRay.start.x = ray.start.x - objectMatWorld.m[3][0];
	localRay.start.y = ray.start.y - objectMatWorld.m[3][1];
	localRay.start.z = ray.start.z - objectMatWorld.m[3][2];

	localRay.dir = ray.dir;

	std::vector<Triangle>::const_iterator it = triangles.cbegin();


	for (; it != triangles.cend(); ++it)
	{
		const Triangle& triangle = *it;

		Vector3 tempInter;

		if (Collision::CheckRay2Triangle(localRay , triangle , nullptr , &tempInter))
		{
			const Matrix4& matWorld = GetObject3d()->GetMatWorld();

			Matrix4 interMat;
			interMat.identity();
			interMat.m[3][0] = tempInter.x;
			interMat.m[3][1] = tempInter.y;
			interMat.m[3][2] = tempInter.z;
			interMat *= matWorld;

			tempInter.x = interMat.m[3][0];
			tempInter.y = interMat.m[3][1];
			tempInter.z = interMat.m[3][2];
			if (distance)
			{
				Vector3 sub = tempInter - ray.start;
				*distance = sub.dot(ray.dir);
			}

			if (inter)
			{
				*inter = tempInter;

			}


			return true;
		}

	}

	return false;
}
