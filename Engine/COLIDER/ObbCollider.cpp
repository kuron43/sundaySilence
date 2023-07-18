#include "ObbCollider.h"

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
void ObbCollider::CreateOBB(Object3d* obj) {

	Matrix4 matRot;
	rotate = obj->wtf.rotation;
	obj3d_ = obj;

	//最大値、最小値の初期値設定
	Vector3 max = Vector3(-10000.0f, -10000.0f, -10000.0f);
	Vector3 min = Vector3(10000.0f, 10000.0f, 10000.0f);

	//メッシュの頂点データ取得
	std::vector<VertexPosNormalUv> vertexBuffer = obj->model_->GetVertices();
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
	m_Pos = (min + max) * 0.5f + Affin::GetWorldTrans(obj->wtf.matWorld);
	//m_Pos = obj->wtf.m_Pos = { 0,0,0 };

	//方向ベクトル取得
	Matrix4 rotMat = Affin::matRotation(obj->wtf.rotation);
	m_NormaDirect[0] = Vector3(rotMat.m[0][0], rotMat.m[0][1], rotMat.m[0][2]);
	m_NormaDirect[1] = Vector3(rotMat.m[1][0], rotMat.m[1][1], rotMat.m[1][2]);
	m_NormaDirect[2] = Vector3(rotMat.m[2][0], rotMat.m[2][1], rotMat.m[2][2]);

	//長さ取得
	m_fLength[0] = fabsf(max.x - min.x) * 0.5f;
	m_fLength[1] = fabsf(max.y - min.y) * 0.5f;
	m_fLength[2] = fabsf(max.z - min.z) * 0.5f;

	m_fLength[0] *= obj->wtf.scale.x;
	m_fLength[1] *= obj->wtf.scale.y;
	m_fLength[2] *= obj->wtf.scale.z;
	//球形状をセット
	shapeType = COLLISIONSHAPE_OBB;
}

void ObbCollider::Update()
{
	if (obj3d_)
	{
		//ワールド行列から座標を抽出
		const Matrix4& matWorld = obj3d_->wtf.matWorld;
		const Matrix4& rotMat = Affin::matRotation(obj3d_->wtf.rotation);

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
	const Matrix4& matWorld = obj.wtf.matWorld;
	const Matrix4& rotMat = Affin::matRotation(obj.wtf.rotation);

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
