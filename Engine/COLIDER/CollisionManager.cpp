#include "CollisionManager.h"
#include "BaseCollider.h"
#include "MeshCollider.h"
#include "Collision.h"
#include "Vector3.h"
#include "imgui.h"

CollisionManager* CollisionManager::GetInstance()
{
	static CollisionManager instance;
	return &instance;
}

void CollisionManager::CheckAllCollisions()
{
	std::forward_list<BaseCollider*>::iterator itA;
	std::forward_list<BaseCollider*>::iterator itB;

	itA = colliders.begin();
	for (; itA != colliders.end(); ++itA)
	{

		itB = itA;
		++itB;

		for (; itB != colliders.end(); ++itB)
		{
			BaseCollider* colA = *itA;
			BaseCollider* colB = *itB;

			if (colA->attribute_ == colB->attribute_)
			{
				continue;
			}

			if (colA->GetShapeType() == COLLISIONSHAPE_SPHERE &&
				colB->GetShapeType() == COLLISIONSHAPE_SPHERE)
			{

				Sphere* sphereA = dynamic_cast<Sphere*>(colA);
				Sphere* sphereB = dynamic_cast<Sphere*>(colB);
				Vector3 inter;

				if (Collision::CheckSphere2Sphere(*sphereA, *sphereB, &inter))
				{
					colA->OnCllision(CollisionInfo(colB->GetObject3d(), colB, inter));
					colB->OnCllision(CollisionInfo(colA->GetObject3d(), colA, inter));
				}

			}
			if (colA->GetShapeType() == COLLISIONSHAPE_SPHERE &&
				colB->GetShapeType() == COLLISIONSHAPE_OBB)
			{
				Sphere* sphere = dynamic_cast<Sphere*>(colA);
				OBB* obb = dynamic_cast<OBB*>(colB);

				//ImGui::Begin("Sphere2Obb");
				//ImGui::Text("T pos:A,%f,%f,%f", obb->m_Pos.x, obb->m_Pos.y, obb->m_Pos.z);
				//ImGui::Text("T pos:B,%f,%f,%f\n", sphere->center.x, sphere->center.y, sphere->center.z);
				//ImGui::End();

				Vector3 inter;
				if (Collision::CheckOBB2Sphere(*obb, *sphere, &inter)) {
					colA->OnCllision(CollisionInfo(colB->GetObject3d(), colB, inter));
					colB->OnCllision(CollisionInfo(colA->GetObject3d(), colA, inter));
				}

			}

			else if (colA->GetShapeType() == COLLISIONSHAPE_MESH &&
				colB->GetShapeType() == COLLISIONSHAPE_SPHERE)
			{
				MeshCollider* meshCollider = dynamic_cast<MeshCollider*>(colA);
				Sphere* sphere = dynamic_cast<Sphere*>(colB);
				Vector3 inter;

				if (meshCollider->CheckCollisionSphere(*sphere, &inter))
				{
					colA->OnCllision(CollisionInfo(colB->GetObject3d(), colB, inter));
					colB->OnCllision(CollisionInfo(colA->GetObject3d(), colA, inter));
				}
			}

			else if (colA->GetShapeType() == COLLISIONSHAPE_SPHERE &&
				colB->GetShapeType() == COLLISIONSHAPE_MESH)
			{
				Sphere* sphere = dynamic_cast<Sphere*>(colA);
				MeshCollider* meshCollider = dynamic_cast<MeshCollider*>(colB);
				Vector3 inter;
				if (meshCollider->CheckCollisionSphere(*sphere, &inter))
				{
					colA->OnCllision(CollisionInfo(colB->GetObject3d(), colB, inter));
					colB->OnCllision(CollisionInfo(colA->GetObject3d(), colA, inter));
				}
			}

			if (colA->GetShapeType() == COLLISIONSHAPE_OBB &&
				colB->GetShapeType() == COLLISIONSHAPE_OBB)
			{
				OBB* obbA = dynamic_cast<OBB*>(colA);
				OBB* obbB = dynamic_cast<OBB*>(colB);
				Vector3 inter;
				if (Collision::CheckOBB2OBB(*obbA, *obbB)) {
					colA->OnCllision(CollisionInfo(colB->GetObject3d(), colB, inter));
					colB->OnCllision(CollisionInfo(colA->GetObject3d(), colA, inter));
				}

			}
		}
	}		
}

bool CollisionManager::Raycast(const Ray& ray, unsigned short attribute, RaycastHit* hitInfo, float maxDistance)
{
	bool result = false;
	//走査用のイテレータ
	std::forward_list<BaseCollider*>::iterator it;
	//今までで最も近いコライダーを記録するためのイテレータ
	std::forward_list<BaseCollider*>::iterator it_hit;
	//今までで最も近いコライダーの距離を記録する変数
	float distance = maxDistance;
	//今までで最も近いコライダーとの交点を記録する変数
	Vector3 inter;

	it = colliders.begin();
	for (; it != colliders.end(); ++it)
	{
		BaseCollider* colA = *it;
		//球の場合
		if (colA->GetShapeType() == COLLISIONSHAPE_SPHERE)
		{
			Sphere* sphere = dynamic_cast<Sphere*>(colA);
			float tempDistance;
			Vector3 tempInter;
			//当たらなければ除外
			if (!Collision::CheckRay2Sphere(ray, *sphere, &tempDistance, &tempInter))
			{
				continue;
			}
			//距離が最小でなければ除外
			if (tempDistance >= distance)
			{
				continue;
			}
			if (!(colA->attribute_ & attribute))
			{
				continue;
			}
			//今までで最も近いので記録をとる
			result = true;
			distance = tempDistance;
			inter = tempInter;
			it_hit = it;
			if (distance >= 10) {

			//ImGui::Begin("RayDis");
			//ImGui::Text("dis0: %f", distance);
			//ImGui::End();
			}
		}
		else if (colA->GetShapeType() == COLLISIONSHAPE_MESH)
		{
			MeshCollider* meshCollider = dynamic_cast<MeshCollider*>(colA);

			float tempDistance;
			Vector3 tempInter;
			if (!meshCollider->CheckCollisionRay(ray, &tempDistance, &tempInter))
			{
				continue;
			}
			if (tempDistance >= distance)
			{
				continue;
			}
			if (!(colA->attribute_ & attribute))
			{
				continue;
			}
			result = true;
			distance = tempDistance;
			inter = tempInter;
			it_hit = it;
			if (distance >= 10) {
				//ImGui::Begin("RayDis");
				//ImGui::Text("dis1: %f", distance);
				//ImGui::End();
			}
		}
		else if (colA->GetShapeType() == COLLISIONSHAPE_OBB)
		{
			OBB* obb = dynamic_cast<OBB*>(colA);

			float tempDistance;
			Vector3 tempInter;
			if (!ObbCollider::GetInstance()->CheckOBB2RAY(*obb, ray, &tempDistance, &tempInter))
			{
				continue;
			}
			if (tempDistance >= distance)
			{
				continue;
			}
			if (!(colA->attribute_ & attribute))
			{
				continue;
			}
			result = true;
			distance = tempDistance;
			inter = tempInter;
			it_hit = it;
			if (distance >= 10) {
				//ImGui::Begin("RayDis");
				//ImGui::Text("dis2: %f", distance);
				//ImGui::End();
			}
		}
	}
	if (result && hitInfo)
	{
		hitInfo->distance = distance;
		hitInfo->inter = inter;
		hitInfo->collider = *it_hit;
		hitInfo->collider->OnCllision(CollisionInfo(hitInfo->collider->GetObject3d(), hitInfo->collider, inter, distance));
		hitInfo->object = hitInfo->collider->GetObject3d();
		//ImGui::Begin("RayDis");
		//ImGui::Text("disRes: %f,%d", distance,hitInfo->collider->GetAttribute());
		//ImGui::End();
	}

	return result;
}

bool CollisionManager::Raycast(const Ray& ray, RaycastHit* hitInfo, float maxDistance)
{
	return Raycast(ray, 0xffff, hitInfo, maxDistance);
}

void CollisionManager::QuerySphere(const Sphere& sphere, QueryCallback* callback, unsigned short attribute) {
	assert(callback);

	std::forward_list<BaseCollider*>::iterator it;

	// すべてのコライダーと総当たりチェック
	it = colliders.begin();
	for (; it != colliders.end(); ++it)
	{
		BaseCollider* col = *it;

		if (!(col->attribute_ & attribute)) {
			continue;
		}
		//球
		if (col->GetShapeType() == COLLISIONSHAPE_SPHERE) {
			Sphere* sphereB = dynamic_cast<Sphere*>(col);

			Vector3 tempInter;
			Vector3 tempReject;
			if (!Collision::CheckSphere2Sphere(sphere, *sphereB, &tempInter, &tempReject))continue;

			// 交差情報をセット
			QueryHit info;
			info.coloder = col;
			info.object = col->GetObject3d();
			info.inter = tempInter;
			info.reject = tempReject;

			// クエリーコールバック呼び出し
			if (!callback->OnQueryHit(info)) {
				// 戻り値がfalseの場合、継続せず終了
				return;
			}
		}// メッシュ
		else if (col->GetShapeType() == COLLISIONSHAPE_MESH) {
			MeshCollider* meshCollider = dynamic_cast<MeshCollider*>(col);

			Vector3 tempInter;
			Vector3 tempReject;
			if (!meshCollider->CheckCollisionSphere(sphere, &tempInter, &tempReject))continue;

			// 交差情報をセット
			QueryHit info;
			info.coloder = col;
			info.object = col->GetObject3d();
			info.inter = tempInter;
			info.reject = tempReject;

			// クエリーコールバック呼び出し
			if (!callback->OnQueryHit(info)) {
				// 戻り値がfalseの場合、継続せず終了
				return;
			}
		}//OBB
		else if (col->GetShapeType() == COLLISIONSHAPE_OBB) {
			OBB* sphereB = dynamic_cast<OBB*>(col);

			Vector3 tempInter;
			Vector3 tempReject;
			if (!Collision::CheckOBB2Sphere(*sphereB, sphere, &tempInter, &tempReject))continue;

			// 交差情報をセット
			QueryHit info;
			info.coloder = col;
			info.object = col->GetObject3d();
			info.inter = tempInter;
			info.reject = tempReject;

			// クエリーコールバック呼び出し
			if (!callback->OnQueryHit(info)) {
				// 戻り値がfalseの場合、継続せず終了
				return;
			}
		}
	}
}





/*===============================================================================================================
	機能	：	傾いた直方体の衝突面判定
	引数	：	立方体の位置と方向ベクトルとベクトルの長さ、球2のマトリクスと半径
	戻り値	：	int型(1：上面が当たっている	2：下面が当たっている	4：左面が当たっている
					  8：右面が当たっている	16：前面が当たっている	32：背面が当たっている
					  64：当っていない)
===============================================================================================================-----------*/
int CollisionManager::OBBHitFace(OBB& obb, Sphere& sphere)
{
	if (!OBBToSphereCollision(obb, sphere))
	{
		/*return IMPINGEMENT_FACE::NOT_HIT */;
	}

	int result = 0;

	for (int i = 0; i < 6; i++)
	{
		(PlaneToSphere(obb.plane[i], sphere))
			? result += 1 << i : false;
	}

	return result;
}

/*===============================================================================================================
	機能	：	傾いた立方体と球の衝突判定を取る
	引数	：	立方体の位置と方向ベクトルとベクトルの長さ、球2のマトリクスと半径
	戻り値	：	bool型(true:当たっている	false:当っていない)
===============================================================================================================*/
bool CollisionManager::OBBToSphereCollision(OBB& obb, Sphere& sphere)
{
	float length = LenOBBToPoint(obb, sphere.center);

	return (length <= sphere.radius_) ? true : false;
}

/*===============================================================================================================
	機能	：	傾いた立方体と点の最短距離を求める
	引数	：	立方体の位置と方向ベクトルとベクトルの長さ、点の座標
	戻り値	：	float型(傾いた直方体と点の最短距離)
===============================================================================================================*/
float CollisionManager::LenOBBToPoint(OBB& obb, Vector3& p)
{
	Vector3 Vec(0.0f, 0.0f, 0.0f);   //　最終的に長さを求めるベクトル

	// 各軸についてはみ出た部分のベクトルを算出
	for (int i = 0; i < 3; i++)
	{
		float L = obb.m_fLength[i] / 2;

		// L=0は計算できない
		if (L <= 0) continue;

		float s = obb.m_NormaDirect[i].dot(p - obb.m_Pos) / L;

		// sの値から、はみ出した部分があればそのベクトルを加算
		s = fabsf(s);
		if (s > 1)
		{
			// はみ出した部分のベクトル算出
			Vec = Vec + ((1 - s) * L * obb.m_NormaDirect[i]);
		}
	}

	return Vec.length();   // 長さを出力
}

/*===============================================================================================================
	機能	:	有限平面と球の衝突判定
	引数	:	有限平面、球の位置、半径
	戻り値	:	bool型(true:当たっている	false:当っていない)
===============================================================================================================*/
bool CollisionManager::PlaneToSphere(FinitePlane plane, Sphere& sphere)
{
	float angle = 0.0f;

	float len = PlaneToPointLeng(plane, sphere.center, sphere.radius_, angle);

	return (len <= sphere.radius_) ? true : false;
}

/*===============================================================================================================
	機能	:	有限平面と点の最短距離を求める
	引数	:	有限平面、球の位置
	戻り値	:	float型(有限平面と点の最短距離)
===============================================================================================================*/
float CollisionManager::PlaneToPointLeng(FinitePlane plane, Vector3 pos, float radius, float& angle)
{
	if (radius) {

	}
	// 平面のベクトル
	Vector3 vec1 = plane.vertex[1] - plane.vertex[0];

	Vector3 vec2 = plane.vertex[3] - plane.vertex[0];

	// 平面の法線ベクトル
	Vector3 cross = vec2.cross(vec1);

	// ベクトルの正規化
	Vector3 nomalizeCross = cross;
	nomalizeCross.nomalize();

	// 無限平面の法線と座標Aの計算を行う
	float planeD = -((nomalizeCross.x * plane.vertex[0].x) + (nomalizeCross.y * plane.vertex[0].y) +
		(nomalizeCross.z * plane.vertex[0].z));

	// 線分と平面の垂直距離を求める
	float L = abs((nomalizeCross.x * pos.x + nomalizeCross.y * pos.y + nomalizeCross.z * pos.z) + planeD) /
		sqrtf(powf(nomalizeCross.x, 2.0f) + powf(nomalizeCross.y, 2.0f) + powf(nomalizeCross.z, 2.0f));

	// 面と球のベクトル
	Vector3 v2 = pos - plane.vertex[0];
	v2.nomalize();

	// 平面の上下判定
	angle = acosf(v2.dot(nomalizeCross));

	bool result = false;

	// 平面との内外判定を行う
	if (angle < DirectX::XM_PIDIV2)
	{
		result |= PlaneToPointInside(plane, pos - (nomalizeCross * L));
	}
	else if (angle > DirectX::XM_PIDIV2)
	{
		result |= PlaneToPointInside(plane, pos + (nomalizeCross * L));
	}
	else
	{
		result |= PlaneToPointInside(plane, pos);
	}

	// 平面内ならそのまま垂直距離を返す
	if (result)
	{
		return L;
	}

	// 平面の各辺との最短距離を求め最小直を返す
	L = LineToPointLeng(plane.vertex[0], plane.vertex[1], pos);
	L = min(LineToPointLeng(plane.vertex[1], plane.vertex[2], pos), L);
	L = min(LineToPointLeng(plane.vertex[2], plane.vertex[3], pos), L);
	L = min(LineToPointLeng(plane.vertex[3], plane.vertex[0], pos), L);

	return L;
}

/*===============================================================================================================
	機能	:	有限平面と点の内外判定
	引数	:	有限平面、点の位置
	戻り値	:	bool型(true:中にある	false:外にある)
===============================================================================================================*/
bool CollisionManager::PlaneToPointInside(FinitePlane plane, Vector3 pos)
{
	// 有限平面を二枚の三角ポリゴンにする

	// 三角ポリゴン1
	std::vector<Vector3> vertex1;

	vertex1.push_back(plane.vertex[0]);
	vertex1.push_back(plane.vertex[3]);
	vertex1.push_back(plane.vertex[1]);

	// 三角ポリゴン2
	std::vector<Vector3> vertex2;

	vertex2.push_back(plane.vertex[2]);
	vertex2.push_back(plane.vertex[1]);
	vertex2.push_back(plane.vertex[3]);

	bool result = false;

	// 三角ポリゴンと点の内外判定を行う
	result |= PolygonToPointInside(vertex1, pos);
	result |= PolygonToPointInside(vertex2, pos);

	return result;
}

/*===============================================================================================================
	機能	:	三角ポリゴンと点の内外判定
	引数	:	三角ポリゴンの頂点情報、点の位置
	戻り値	:	bool型(true:中にある	false:外にある)
===============================================================================================================*/
bool CollisionManager::PolygonToPointInside(std::vector<Vector3> polygonPos, Vector3 pos)
{
	// 交点とポリゴンの頂点との外積結果を入れるための変数
	Vector3 normalA;
	Vector3 normalB;
	Vector3 normalC;

	// 一つ目の三角形法線の算出
	Vector3 vec_PTo1 = polygonPos[0] - pos;
	Vector3 vec_1To2 = polygonPos[1] - polygonPos[0];

	normalA.x = vec_PTo1.y * vec_1To2.z - vec_PTo1.z * vec_1To2.y;
	normalA.y = vec_PTo1.z * vec_1To2.x - vec_PTo1.x * vec_1To2.z;
	normalA.z = vec_PTo1.x * vec_1To2.y - vec_PTo1.y * vec_1To2.x;

	// 二つ目の三角形法線の算出
	vec_PTo1 = polygonPos[1] - pos;
	vec_1To2 = polygonPos[2] - polygonPos[1];

	normalB.x = vec_PTo1.y * vec_1To2.z - vec_PTo1.z * vec_1To2.y;
	normalB.y = vec_PTo1.z * vec_1To2.x - vec_PTo1.x * vec_1To2.z;
	normalB.z = vec_PTo1.x * vec_1To2.y - vec_PTo1.y * vec_1To2.x;

	// 三つ目の三角形法線の算出
	vec_PTo1 = polygonPos[2] - pos;
	vec_1To2 = polygonPos[0] - polygonPos[2];

	normalC.x = vec_PTo1.y * vec_1To2.z - vec_PTo1.z * vec_1To2.y;
	normalC.y = vec_PTo1.z * vec_1To2.x - vec_PTo1.x * vec_1To2.z;
	normalC.z = vec_PTo1.x * vec_1To2.y - vec_PTo1.y * vec_1To2.x;

	//内積で順方向か逆方向か調べる
	float dot1 = normalA.dot(normalB);
	float dot2 = normalA.dot(normalC);

	return (dot1 >= 0 && dot2 >= 0) ? true : false;
}

/*===============================================================================================================
	機能	:	線分と点の最短距離
	引数	:	線分の頂点1、線分の頂点2、点の位置
	戻り値	:	bool型(true:中にある	false:外にある)
===============================================================================================================*/
float CollisionManager::LineToPointLeng(Vector3 lineVertex1, Vector3 lineVertex2, Vector3 pointPos)
{
	Vector3 v = lineVertex1 - lineVertex2;
	Vector3 vNorm = v;
	vNorm.nomalize();

	// 線分の頂点1との距離
	Vector3 v1 = pointPos - lineVertex2;

	float t = vNorm.dot(v1) / v.length();

	float result = 0.0f;

	// 垂直におろせるなら垂直距離を、おろせないなら近い側の線分の頂点との距離を返す
	if (t < 0)
	{
		result = v1.length();
	}
	else if (t > 1)
	{
		// 線分の頂点2との距離
		Vector3 v2 = pointPos - lineVertex1;
		result = v2.length();
	}
	else
	{
		// 垂直距離を求める
		Vector3 h = v * t - v1;
		result = h.length();
	}

	return result;
}