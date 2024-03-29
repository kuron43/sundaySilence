#pragma once
#include "BaseCollider.h"
#include "CollisionPrimitive.h"
#include "Model.h"


// OBBとは何ぞや
// http://distancevector.web.fc2.com/collision.html
class ObbCollider : public BaseCollider, public OBB
{
public:
	/// <summary>
	/// OBB作成
	/// </summary>
	/// <param name="offset">位置</param>
	/// <param name="length">軸方向の長さ</param>
	/// <param name="rotMat">回転行列から方向ベクトルの取得用</param>
	ObbCollider(Vector3 offset = { 0 , 0 , 0 }, Vector3 length = { 0.0f,0.0f,0.0f }, Matrix4 rotMat = Affin::matUnit());

	//更新
	void Update() override;
	//更新
	void UpdateObb(Object3d& obj);

	bool CheckOBB2RAY(const OBB& obb, const Ray& ray, float* distance = nullptr, Vector3* inter = nullptr, Vector3* reject = nullptr);
	static ObbCollider* GetInstance();
public:
	//void CreateOBB(Object3d* obj);
	void CreateOBB(std::vector<VertexPosNormalUv> vertices, Transform* wtfP);

	// 指定軸番号の方向ベクトルを取得
	Vector3 GetDirect(uint32_t elem) {
		return m_NormaDirect[elem];
	}
	// 指定軸方向の長さを取得
	float GetLength(uint32_t elem) {
		return m_fLength[elem];
	}
	Vector3 GetVec3Length() {
		Vector3 result = { m_fLength[0] ,m_fLength[1] ,m_fLength[2] };
		return result;
	}
	// 位置を取得
	Vector3 GetPos_() {
		return m_Pos;
	}
	Vector3 Getrotate_() {
		return rotate;
	}

private:
	Transform* wtf_;
	Vector3 rotate;

	Vector3 m_Pos;              // 位置
	Vector3 m_NormaDirect[3];   // 方向ベクトル
	float m_fLength[3];             // 各軸方向の長さ

	FinitePlane plane[6];

//	http://marupeke296.com/COL_3D_No13_OBBvsOBB.html
};
