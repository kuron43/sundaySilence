#include "ObbCollider.h"

ObbCollider* ObbCollider::GetInstance()
{
	static ObbCollider instance;
	return &instance;
}

ObbCollider::ObbCollider(Vector3 offset, Vector3 length, Matrix4 rotMat)
{
	m_Pos = offset;
	m_fLength[0] = length.x;
	m_fLength[1] = length.y;
	m_fLength[2] = length.z;
	m_NormaDirect[0] = Vector3(rotMat.m[0][0], rotMat.m[0][1], rotMat.m[0][2]);
	m_NormaDirect[1] = Vector3(rotMat.m[1][0], rotMat.m[1][1], rotMat.m[1][2]);
	m_NormaDirect[2] = Vector3(rotMat.m[2][0], rotMat.m[2][1], rotMat.m[2][2]);
	//球形状をセット
	shapeType = COLLISIONSHAPE_OBB;
}
void ObbCollider::CreateOBB(std::vector<VertexPosNormalUv> vertices, Transform* wtfP) {

	Matrix4 matRot;
	wtf_ = wtfP;
	rotate = wtf_->rotation;

	//最大値、最小値の初期値設定
	Vector3 max = Vector3(-10000.0f, -10000.0f, -10000.0f);
	Vector3 min = Vector3(10000.0f, 10000.0f, 10000.0f);

	//メッシュの頂点データ取得
	std::vector<VertexPosNormalUv> vertexBuffer = vertices;
	//最大値、最小値取得ループ
	for (size_t i = 0; i < vertexBuffer.size(); i++)
	{
		Vector3 pos = vertexBuffer[i].pos;
		if (pos.x < min.x) { min.x = pos.x; }
		if (pos.x > max.x) { max.x = pos.x; }
		if (pos.y < min.y) { min.y = pos.y; }
		if (pos.y > max.y) { max.y = pos.y; }
		if (pos.z < min.z) { min.z = pos.z; }
		if (pos.z > max.z) { max.z = pos.z; }
	}

	//中心点取得
	m_Pos = (min + max) * 0.5f + Affin::GetWorldTrans(wtf_->matWorld);
	//m_Pos = obj->transForm.m_Pos = { 0,0,0 };

	//方向ベクトル取得
	Matrix4 rotMat = Affin::matRotation(wtf_->rotation);
	m_NormaDirect[0] = Vector3(rotMat.m[0][0], rotMat.m[0][1], rotMat.m[0][2]);
	m_NormaDirect[1] = Vector3(rotMat.m[1][0], rotMat.m[1][1], rotMat.m[1][2]);
	m_NormaDirect[2] = Vector3(rotMat.m[2][0], rotMat.m[2][1], rotMat.m[2][2]);

	//長さ取得
	m_fLength[0] = fabsf(max.x - min.x) * 0.5f;
	m_fLength[1] = fabsf(max.y - min.y) * 0.5f;
	m_fLength[2] = fabsf(max.z - min.z) * 0.5f;

	m_fLength[0] *= wtf_->scale.x;
	m_fLength[1] *= wtf_->scale.y;
	m_fLength[2] *= wtf_->scale.z;
	//球形状をセット
	shapeType = COLLISIONSHAPE_OBB;
	for (uint32_t i = 0; i < 6; i++) {
		plane[i].pos = m_Pos;
	}

	plane[0].normal = m_NormaDirect[0];
	plane[1].normal = m_NormaDirect[1];
	plane[2].normal = m_NormaDirect[2];
	plane[3].normal = -m_NormaDirect[0];
	plane[4].normal = -m_NormaDirect[1];
	plane[5].normal = -m_NormaDirect[2];

	plane[0].distance = m_fLength[0] / 2;
	plane[1].distance = m_fLength[1] / 2;
	plane[2].distance = m_fLength[2] / 2;
	plane[3].distance = -m_fLength[0] / 2;
	plane[4].distance = -m_fLength[1] / 2;
	plane[5].distance = -m_fLength[2] / 2;

	{// (仮)法線基準

		plane[0].vertex[0] = { +1.0f, -1.0f, +1.0f }; // 左下  I
		plane[0].vertex[1] = { +1.0f, +1.0f, +1.0f }; // 左上  D
		plane[0].vertex[2] = { +1.0f, -1.0f, -1.0f }; // 右下  J
		plane[0].vertex[3] = { +1.0f, +1.0f, -1.0f }; // 右上  E

		plane[1].vertex[0] = { -1.0f, +1.0f, +1.0f }; // 左下 C
		plane[1].vertex[1] = { -1.0f, +1.0f, -1.0f }; // 左上 A
		plane[1].vertex[2] = { +1.0f, +1.0f, +1.0f }; // 右下 D
		plane[1].vertex[3] = { +1.0f, +1.0f, -1.0f }; // 右上 B

		plane[2].vertex[0] = { -1.0f, -1.0f, +1.0f }; // 左下  H
		plane[2].vertex[1] = { -1.0f, +1.0f, +1.0f }; // 左上  C
		plane[2].vertex[2] = { +1.0f, -1.0f, +1.0f }; // 右下  I
		plane[2].vertex[3] = { +1.0f, +1.0f, +1.0f }; // 右上  D

		plane[3].vertex[0] = { -1.0f, -1.0f, -1.0f }; // 左下  K
		plane[3].vertex[1] = { -1.0f, +1.0f, -1.0f }; // 左上  F
		plane[3].vertex[2] = { -1.0f, -1.0f, +1.0f }; // 右下  L
		plane[3].vertex[3] = { -1.0f, +1.0f, +1.0f }; // 右上  G

		plane[4].vertex[0] = { +1.0f, -1.0f, -1.0f }; // 左下  M
		plane[4].vertex[1] = { -1.0f, -1.0f, -1.0f }; // 左上  K
		plane[4].vertex[2] = { +1.0f, -1.0f, +1.0f }; // 右下  N
		plane[4].vertex[3] = { -1.0f, -1.0f, +1.0f }; // 右上  L

		plane[5].vertex[0] = { +1.0f, -1.0f, -1.0f }; // 左下  J
		plane[5].vertex[1] = { +1.0f, +1.0f, -1.0f }; // 左上  E
		plane[5].vertex[2] = { -1.0f, -1.0f, -1.0f }; // 右下  K
		plane[5].vertex[3] = { -1.0f, +1.0f, -1.0f }; // 右上  F
	}
}

void ObbCollider::Update()
{
	if (wtf_)
	{
		//ワールド行列から座標を抽出
		const Matrix4& matWorld = wtf_->matWorld;
		const Matrix4& rotMat = Affin::matRotation(wtf_->rotation);

		//球のメンバ変数を更新
		m_Pos =
		{
			matWorld.m[3][0]  ,
			matWorld.m[3][1]  ,
			matWorld.m[3][2]
		};
		OBB::m_Pos =
		{
			matWorld.m[3][0]  ,
			matWorld.m[3][1]  ,
			matWorld.m[3][2]
		};
		OBB::m_NormaDirect[0] = Vector3(rotMat.m[0][0], rotMat.m[0][1], rotMat.m[0][2]);
		OBB::m_NormaDirect[1] = Vector3(rotMat.m[1][0], rotMat.m[1][1], rotMat.m[1][2]);
		OBB::m_NormaDirect[2] = Vector3(rotMat.m[2][0], rotMat.m[2][1], rotMat.m[2][2]);
		m_NormaDirect[0] = Vector3(rotMat.m[0][0], rotMat.m[0][1], rotMat.m[0][2]);
		m_NormaDirect[1] = Vector3(rotMat.m[1][0], rotMat.m[1][1], rotMat.m[1][2]);
		m_NormaDirect[2] = Vector3(rotMat.m[2][0], rotMat.m[2][1], rotMat.m[2][2]);

		OBB::m_fLength[0] = m_fLength[0];
		OBB::m_fLength[1] = m_fLength[1];
		OBB::m_fLength[2] = m_fLength[2];

		// 平面用
		{
			for (uint32_t i = 0; i < 6; i++) {
				OBB::plane[i].pos = m_Pos;
			}

			OBB::plane[0].normal = m_NormaDirect[0];
			OBB::plane[1].normal = m_NormaDirect[1];
			OBB::plane[2].normal = m_NormaDirect[2];
			OBB::plane[3].normal = -m_NormaDirect[0];
			OBB::plane[4].normal = -m_NormaDirect[1];
			OBB::plane[5].normal = -m_NormaDirect[2];

			OBB::plane[0].distance = m_fLength[0] / 2;
			OBB::plane[1].distance = m_fLength[1] / 2;
			OBB::plane[2].distance = m_fLength[2] / 2;
			OBB::plane[4].distance = -m_fLength[1] / 2;
			OBB::plane[5].distance = -m_fLength[2] / 2;
			OBB::plane[3].distance = -m_fLength[0] / 2;

			{// (仮)法線基準

				OBB::plane[0].vertex[0] = { +1.0f, -1.0f, +1.0f }; // 左下  I
				OBB::plane[0].vertex[1] = { +1.0f, +1.0f, +1.0f }; // 左上  D
				OBB::plane[0].vertex[2] = { +1.0f, -1.0f, -1.0f }; // 右下  J
				OBB::plane[0].vertex[3] = { +1.0f, +1.0f, -1.0f }; // 右上  E

				OBB::plane[1].vertex[0] = { -1.0f, +1.0f, +1.0f }; // 左下 C
				OBB::plane[1].vertex[1] = { -1.0f, +1.0f, -1.0f }; // 左上 A
				OBB::plane[1].vertex[2] = { +1.0f, +1.0f, +1.0f }; // 右下 D
				OBB::plane[1].vertex[3] = { +1.0f, +1.0f, -1.0f }; // 右上 B

				OBB::plane[2].vertex[0] = { -1.0f, -1.0f, +1.0f }; // 左下  H
				OBB::plane[2].vertex[1] = { -1.0f, +1.0f, +1.0f }; // 左上  C
				OBB::plane[2].vertex[2] = { +1.0f, -1.0f, +1.0f }; // 右下  I
				OBB::plane[2].vertex[3] = { +1.0f, +1.0f, +1.0f }; // 右上  D

				OBB::plane[3].vertex[0] = { -1.0f, -1.0f, -1.0f }; // 左下  K
				OBB::plane[3].vertex[1] = { -1.0f, +1.0f, -1.0f }; // 左上  F
				OBB::plane[3].vertex[2] = { -1.0f, -1.0f, +1.0f }; // 右下  L
				OBB::plane[3].vertex[3] = { -1.0f, +1.0f, +1.0f }; // 右上  G

				OBB::plane[4].vertex[0] = { +1.0f, -1.0f, -1.0f }; // 左下  M
				OBB::plane[4].vertex[1] = { -1.0f, -1.0f, -1.0f }; // 左上  K
				OBB::plane[4].vertex[2] = { +1.0f, -1.0f, +1.0f }; // 右下  N
				OBB::plane[4].vertex[3] = { -1.0f, -1.0f, +1.0f }; // 右上  L

				OBB::plane[5].vertex[0] = { +1.0f, -1.0f, -1.0f }; // 左下  J
				OBB::plane[5].vertex[1] = { +1.0f, +1.0f, -1.0f }; // 左上  E
				OBB::plane[5].vertex[2] = { -1.0f, -1.0f, -1.0f }; // 右下  K
				OBB::plane[5].vertex[3] = { -1.0f, +1.0f, -1.0f }; // 右上  F
			}
		}
	}
	else
	{
		OBB::m_Pos = { 0 , 0 , 0 };

		OBB::m_NormaDirect[0] = Vector3(1.0f, 1.0f, 1.0f);
		OBB::m_NormaDirect[1] = Vector3(1.0f, 1.0f, 1.0f);
		OBB::m_NormaDirect[2] = Vector3(1.0f, 1.0f, 1.0f);

		OBB::m_fLength[0] = m_fLength[0];
		OBB::m_fLength[1] = m_fLength[1];
		OBB::m_fLength[2] = m_fLength[2];
	}

	isHit = false;
}

void ObbCollider::UpdateObb(Object3d& obj)
{
	//ワールド行列から座標を抽出
	const Matrix4& matWorld = obj.transForm.matWorld;
	const Matrix4& rotMat = Affin::matRotation(obj.transForm.rotation);

	//球のメンバ変数を更新
	OBB::m_Pos = Affin::GetWorldTrans(matWorld);
	m_Pos = Affin::GetWorldTrans(matWorld);

	OBB::m_NormaDirect[0] = Vector3(rotMat.m[0][0], rotMat.m[0][1], rotMat.m[0][2]);
	OBB::m_NormaDirect[1] = Vector3(rotMat.m[1][0], rotMat.m[1][1], rotMat.m[1][2]);
	OBB::m_NormaDirect[2] = Vector3(rotMat.m[2][0], rotMat.m[2][1], rotMat.m[2][2]);
	m_NormaDirect[0] = Vector3(rotMat.m[0][0], rotMat.m[0][1], rotMat.m[0][2]);
	m_NormaDirect[1] = Vector3(rotMat.m[1][0], rotMat.m[1][1], rotMat.m[1][2]);
	m_NormaDirect[2] = Vector3(rotMat.m[2][0], rotMat.m[2][1], rotMat.m[2][2]);

	OBB::m_fLength[0] = m_fLength[0];
	OBB::m_fLength[1] = m_fLength[1];
	OBB::m_fLength[2] = m_fLength[2];

	isHit = false;
}

bool ObbCollider::CheckOBB2RAY(const OBB& obb, const Ray& ray, float* distance, Vector3* inter, Vector3* reject) {
	const float EPSILON = (float)1.175494e-37;

	Vector3 m = (ray.start_ + ray.dir_) * 0.5f;
	Vector3 d = ray.dir_ - m;
	m = m - obb.m_Pos;
	m = Vector3(obb.m_NormaDirect[0].dot(m), obb.m_NormaDirect[1].dot(m), obb.m_NormaDirect[2].dot(m));
	d = Vector3(obb.m_NormaDirect[0].dot(d), obb.m_NormaDirect[1].dot(d), obb.m_NormaDirect[2].dot(d));

	float adx = fabsf(d.x);
	if (fabsf(m.x) > obb.m_fLength[0] + adx) {
		return false;
	}

	float ady = fabsf(d.y);
	if (fabsf(m.y) > obb.m_fLength[1] + ady) {
		return false;
	}

	float adz = fabsf(d.z);
	if (fabsf(m.z) > obb.m_fLength[2] + adz) {
		return false;
	}
	adx += EPSILON;
	ady += EPSILON;
	adz += EPSILON;

	if (fabsf(m.y * d.z - m.z * d.y) > obb.m_fLength[1] * adz + obb.m_fLength[2] * ady) {
		return false;
	}
	if (fabsf(m.z * d.x - m.x * d.z) > obb.m_fLength[0] * adz + obb.m_fLength[2] * adx) {
		return false;
	}
	if (fabsf(m.x * d.y - m.y * d.x) > obb.m_fLength[0] * ady + obb.m_fLength[1] * adx) {
		return false;
	}
	if (distance)
	{
		*distance = Vector3(ray.start_ - obb.m_Pos).length();
	}
	if (inter) {

	}
	if (reject) {

	}

	return true;
}