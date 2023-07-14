#include "Collision.h"
using namespace DirectX;

bool Collision::CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB, Vector3* inter, Vector3* reject)
{
	float dist = sqrtf(float(
		pow(sphereB.center.x - sphereA.center.x, 2) +
		pow(sphereB.center.y - sphereA.center.y, 2) +
		pow(sphereB.center.z - sphereA.center.z, 2)
		));

	if (dist > sphereA.radius_ + sphereB.radius_)
	{
		return false;
	}
	*inter = sphereA.center + (sphereB.center - sphereA.center) / 2;
	//押し出すベクトルを計算
	if (reject) {
		Vector3 normaVec = { 0,0,0 };
		float rejectLen = sphereA.radius_ + sphereB.radius_ - sqrtf(dist);
		normaVec = sphereA.center - sphereB.center;
		normaVec.nomalize();
		*reject = normaVec;
		*reject *= rejectLen;
	}
	return true;
}

bool Collision::CheckSphere2Plane(const Sphere& sphere, const Plane& plane, Vector3* inter, Vector3* reject)
{
	//座標系の原点から球の中心座標への距離
	float distV = sphere.center.dot(plane.normal);

	//平面の原点距離を減算することで、平面と級の中心との距離が出る
	float dist = distV - plane.distance;

	//距離の絶対値が半径より大きければ当たっていない
	if (fabs(dist) > sphere.radius_) return false;

	//疑似交点
	if (inter)
	{
		//平面上の最近接点を疑似交点とする
		*inter = -dist * plane.normal + sphere.center;
	}
	if (reject) {

	}

	return true;
}

void Collision::ClosestPtPoint2Triangle(const Vector3& point, const Triangle& triangle, Vector3* closest, Vector3* reject)
{
	if (reject) {

	}
	// pointがp0の外側の頂点領域の中にあるかどうかチェック
	Vector3 p0_p1 = triangle.p1 - triangle.p0;
	Vector3 p0_p2 = triangle.p2 - triangle.p0;
	Vector3 p0_pt = point - triangle.p0;

	float d1 = p0_p1.dot(p0_pt);
	float d2 = p0_p2.dot(p0_pt);

	if (d1 <= 0.0f && d2 <= 0.0f)
	{
		// p0が最近傍
		*closest = triangle.p0;
		return;
	}

	// pointがp1の外側の頂点領域の中にあるかどうかチェック
	Vector3 p1_pt = point - triangle.p1;

	float d3 = p0_p1.dot(p1_pt);
	float d4 = p0_p2.dot(p1_pt);

	if (d3 >= 0.0f && d4 <= d3)
	{
		// p1が最近傍
		*closest = triangle.p1;
		return;
	}

	// pointがp0_p1の辺領域の中にあるかどうかチェックし、あればpointのp0_p1上に対する射影を返す
	float vc = d1 * d4 - d3 * d2;
	if (vc <= 0.0f && d1 >= 0.0f && d3 <= 0.0f)
	{
		float v = d1 / (d1 - d3);
		*closest = triangle.p0 + v * p0_p1;
		return;
	}

	// pointがp2の外側の頂点領域の中にあるかどうかチェック
	Vector3 p2_pt = point - triangle.p2;

	float d5 = p0_p1.dot(p2_pt);
	float d6 = p0_p2.dot(p2_pt);
	if (d6 >= 0.0f && d5 <= d6)
	{
		*closest = triangle.p2;
		return;
	}

	// pointがp0_p2の辺領域の中にあるかどうかチェックし、あればpointのp0_p2上に対する射影を返す
	float vb = d5 * d2 - d1 * d6;
	if (vb <= 0.0f && d2 >= 0.0f && d6 <= 0.0f)
	{
		float w = d2 / (d2 - d6);
		*closest = triangle.p0 + w * p0_p2;
		return;
	}

	// pointがp1_p2の辺領域の中にあるかどうかチェックし、あればpointのp1_p2上に対する射影を返す
	float va = d3 * d6 - d5 * d4;
	if (va <= 0.0f && (d4 - d3) >= 0.0f && (d5 - d6) >= 0.0f)
	{
		float w = (d4 - d3) / ((d4 - d3) + (d5 - d6));
		*closest = triangle.p1 + w * (triangle.p2 - triangle.p1);
		return;
	}

	float denom = 1.0f / (va + vb + vc);
	float v = vb * denom;
	float w = vc * denom;
	*closest = triangle.p0 + p0_p1 * v + p0_p2 * w;
}

bool Collision::CheckSphere2Triangle(const Sphere& sphere, const Triangle& triangle, Vector3* inter, Vector3* reject)
{
	Vector3 p;
	//球の中心に対する接点である三角形上にある点pを見つける
	ClosestPtPoint2Triangle(sphere.center, triangle, &p);
	//点pと球の中心の差分ベクトル
	Vector3 v = p - sphere.center;
	//距離の二乗を求める
	float powDist = powf(v.length(), 2);

	if (powDist > powf(sphere.radius_, 2))
	{
		return false;
	}

	if (inter)
	{
		*inter = p;
	}
	if (reject) {
		float ds = sphere.center.dot(triangle.normal);
		float dt = triangle.p0.dot(triangle.normal);
		float rejectLen = dt - ds + sphere.radius_;
		*reject = triangle.normal * rejectLen;
	}

	return true;
}

bool Collision::CheckRay2Plane(const Ray& ray, const Plane& plane, float* distance, Vector3* inter, Vector3* reject)
{
	//誤差吸収用の微小な値
	const float epsilon = 1.0e-5f;
	//面法線とレイの方向ベクトルの内積
	float d1 = plane.normal.dot(ray.dir);
	//裏面には当たらない
	if (d1 > -epsilon)
	{
		return false;
	}

	//面法線とレイの視点座標の内積
	float d2 = plane.normal.dot(ray.start);
	//始点と平面の距離(平面の法線方向)
	float dist = d2 - plane.distance;
	//始点と平面の距離(レイ方向)
	float t = dist / -d1;
	//交点が視点より後ろにあるので当たらない
	if (t < 0)
	{
		return false;
	}

	//距離を書き込む
	if (distance)
	{
		*distance = t;
	}

	//交点を計算
	if (inter)
	{
		*inter = ray.start + t * ray.dir;
	}
	if (reject) {

	}

	return true;
}

bool Collision::CheckRay2Triangle(const Ray& ray, const Triangle& triangle, float* distance, Vector3* inter, Vector3* reject)
{
	if (reject) {

	}
	//三角形が乗っている平面を算出
	Plane plane;
	Vector3 interPlane;
	plane.normal = triangle.normal;
	plane.distance = triangle.normal.dot(triangle.p0);

	//レイと平面が当たっていなければ当たっていない
	if (!CheckRay2Plane(ray, plane, distance, &interPlane))
	{
		return false;
	}

	//レイと平面が当たっていたので、距離と交点が書き込まれた
	//レイと平面の交点が三角形の内側にあるか判定
	const float epsilon = 1.0e-5f;//誤差吸収用の微小な値
	Vector3 m;

	//辺p0_p1について
	Vector3 pt_p0 = triangle.p0 - interPlane;
	Vector3 p0_p1 = triangle.p1 - triangle.p0;
	m = pt_p0.cross(p0_p1);
	//辺の外側であれば当たっていないので判定を打ち切る
	if (m.dot(triangle.normal) < -epsilon)
	{
		return false;
	}

	//辺p1_p2について
	Vector3 pt_p1 = triangle.p1 - interPlane;
	Vector3 p1_p2 = triangle.p2 - triangle.p1;
	m = pt_p1.cross(p1_p2);
	//辺の外側であれば当たっていないので判定を打ち切る
	if (m.dot(triangle.normal) < -epsilon)
	{
		return false;
	}

	//辺p2_p0について
	Vector3 pt_p2 = triangle.p2 - interPlane;
	Vector3 p2_p0 = triangle.p0 - triangle.p2;
	m = pt_p2.cross(p2_p0);
	//辺の外側であれば当たっていないので判定を打ち切る
	if (m.dot(triangle.normal) < -epsilon)
	{
		return false;
	}

	if (inter)
	{
		*inter = interPlane;
	}

	return true;
}

bool Collision::CheckRay2Sphere(const Ray& ray, const Sphere& sphere, float* distance, Vector3* inter, Vector3* reject)
{
	if (reject) {

	}
	Vector3 m = ray.start - sphere.center;
	float b = m.dot(ray.dir);
	float c = m.dot(m) - powf(sphere.radius_, 2);

	//レイの始点が球の外にあり(c>0)、レイが球から離れている方向を指している場合(b>0)、当たらない
	if (c > 0.0f && b > 0.0f)
	{
		return false;
	}

	float discr = b * b - c;
	//負の判別式はレイが球を外れていることに一致
	if (discr < 0.0f)
	{
		return false;
	}

	//レイと球は交差している
	//交差する場合の最小の値tを計算
	float t = -b - sqrtf(discr);
	//tが負である場合、レイは球の内部から開始しているのでtをゼロにクランプ
	if (t < 0)
	{
		t = 0.0f;
	}

	if (distance)
	{
		*distance = t;
	}

	if (inter)
	{
		*inter = ray.start + t * ray.dir;
	}

	return true;
}

// 3次元OBBと点の最短距離算出関数
float Collision::LenOBBToPoint(OBB& obb, Vector3& p)
{
	Vector3 Vec(0, 0, 0);   // 最終的に長さを求めるベクトル
	float result = 0;

	// 各軸についてはみ出た部分のベクトルを算出
	for (int i = 0; i < 3; i++)
	{
		float L = obb.m_fLength[i];
		// L=0は計算できない
		if (L <= 0) {
			continue;
		}
		float s = Vector3(p - obb.m_Pos).dot(obb.m_NormaDirect[i]) / L;

		// sの値から、はみ出した部分があればそのベクトルを加算
		s = (float)fabs(s);
		if (s > 1) {
			Vec += (1 - s) * L * obb.m_NormaDirect[i];   // はみ出した部分のベクトル算出
		}
	}
	result = Vec.length();

	return result;   // 長さを出力
}

bool Collision::CheckOBB2OBB(const OBB& obb1, const OBB& obb2, Vector3* inter, Vector3* reject) {
	if (reject) {

	}
	// 各方向ベクトルの確保
// （N***:標準化方向ベクトル）
	Vector3 NAe1 = obb1.m_NormaDirect[0], Ae1 = NAe1 * obb1.m_fLength[0];
	Vector3 NAe2 = obb1.m_NormaDirect[1], Ae2 = NAe2 * obb1.m_fLength[1];
	Vector3 NAe3 = obb1.m_NormaDirect[2], Ae3 = NAe3 * obb1.m_fLength[2];
	Vector3 NBe1 = obb2.m_NormaDirect[0], Be1 = NBe1 * obb2.m_fLength[0];
	Vector3 NBe2 = obb2.m_NormaDirect[1], Be2 = NBe2 * obb2.m_fLength[1];
	Vector3 NBe3 = obb2.m_NormaDirect[2], Be3 = NBe3 * obb2.m_fLength[2];
	Vector3 Interval = obb1.m_Pos - obb2.m_Pos;

	// 分離軸 : Ae1
	float rA = Ae1.length();
	float rB = LenSegOnSeparateAxis(NAe1, Be1, Be2, Be3);
	float L = (float)fabs(Interval.dot(NAe1));
	if (L > rA + rB) {
		return false;
	}// 衝突していない

	// 分離軸 : Ae2
	rA = Ae2.length();
	rB = LenSegOnSeparateAxis(NAe2, Be1, Be2, Be3);
	L = (float)fabs(Interval.dot(NAe2));
	if (L > rA + rB) {
		return false;
	}

	// 分離軸 : Ae3
	rA = Ae3.length();
	rB = LenSegOnSeparateAxis(NAe3, Be1, Be2, Be3);
	L = (float)fabs(Interval.dot(NAe3));
	if (L > rA + rB) {
		return false;
	}

	// 分離軸 : Be1
	rA = LenSegOnSeparateAxis(NBe1, Ae1, Ae2, Ae3);
	rB = Be1.length();
	L = (float)fabs(Interval.dot(NBe1));
	if (L > rA + rB) {
		return false;
	}

	// 分離軸 : Be2
	rA = LenSegOnSeparateAxis(NBe2, Ae1, Ae2, Ae3);
	rB = Be2.length();
	L = (float)fabs(Interval.dot(NBe2));
	if (L > rA + rB) {
		return false;
	}

	// 分離軸 : Be3
	rA = LenSegOnSeparateAxis(NBe3, Ae1, Ae2, Ae3);
	rB = Be3.length();
	L = (float)fabs(Interval.dot(NBe3));
	if (L > rA + rB) {
		return false;
	}

	// 分離軸 : C11
	Vector3 Cross;
	Cross = NAe1.cross(NBe1);
	rA = LenSegOnSeparateAxis(Cross, Ae2, Ae3);
	rB = LenSegOnSeparateAxis(Cross, Be2, Be3);
	L = (float)fabs((float)Interval.dot(Cross));
	if (L > rA + rB) {
		return false;
	}

	// 分離軸 : C12
	Cross = NAe1.cross(NBe2);
	rA = LenSegOnSeparateAxis(Cross, Ae2, Ae3);
	rB = LenSegOnSeparateAxis(Cross, Be1, Be3);
	L = (float)fabs((float)Interval.dot(Cross));
	if (L > rA + rB) {
		return false;
	}

	// 分離軸 : C13
	Cross = NAe1.cross(NBe3);
	rA = LenSegOnSeparateAxis(Cross, Ae2, Ae3);
	rB = LenSegOnSeparateAxis(Cross, Be1, Be2);
	L = (float)fabs((float)Interval.dot(Cross));
	if (L > rA + rB) {
		return false;
	}

	// 分離軸 : C21
	Cross = NAe2.cross(NBe1);
	rA = LenSegOnSeparateAxis(Cross, Ae1, Ae3);
	rB = LenSegOnSeparateAxis(Cross, Be2, Be3);
	L = (float)fabs((float)Interval.dot(Cross));
	if (L > rA + rB) {
		return false;
	}

	// 分離軸 : C22
	Cross = NAe2.cross(NBe2);
	rA = LenSegOnSeparateAxis(Cross, Ae1, Ae3);
	rB = LenSegOnSeparateAxis(Cross, Be1, Be3);
	L = (float)fabs((float)Interval.dot(Cross));
	if (L > rA + rB) {
		return false;
	}

	// 分離軸 : C23
	Cross = NAe2.cross(NBe3);
	rA = LenSegOnSeparateAxis(Cross, Ae1, Ae3);
	rB = LenSegOnSeparateAxis(Cross, Be1, Be2);
	L = (float)fabs((float)Interval.dot(Cross));
	if (L > rA + rB) {
		return false;
	}

	// 分離軸 : C31
	Cross = NAe3.cross(NBe1);
	rA = LenSegOnSeparateAxis(Cross, Ae1, Ae2);
	rB = LenSegOnSeparateAxis(Cross, Be2, Be3);
	L = (float)fabs((float)Interval.dot(Cross));
	if (L > rA + rB) {
		return false;
	}

	// 分離軸 : C32
	Cross = NAe3.cross(NBe2);
	rA = LenSegOnSeparateAxis(Cross, Ae1, Ae2);
	rB = LenSegOnSeparateAxis(Cross, Be1, Be3);
	L = (float)fabs((float)Interval.dot(Cross));
	if (L > rA + rB) {
		return false;
	}

	// 分離軸 : C33
	Cross = NAe3.cross(NBe3);
	rA = LenSegOnSeparateAxis(Cross, Ae1, Ae2);
	rB = LenSegOnSeparateAxis(Cross, Be1, Be2);
	L = (float)fabs((float)Interval.dot(Cross));
	if (L > rA + rB) {
		return false;
	}
	//疑似交点
	if (inter)
	{
		//平面上の最近接点を疑似交点とする
		//*inter = 
	}
	// 分離平面が存在しないので「衝突している」
	return true;
}

bool Collision::CheckOBB2Sphere(const OBB& obb, const Sphere& sphere, Vector3* inter, Vector3* reject) {
	if (reject) {

	}
	float length;
	OBB obb_ = obb;
	Vector3 spherePos = sphere.center;
	length = LenOBBToPoint(obb_, spherePos);
	if ((float)fabs(length) <= sphere.radius_) {
		return false;
	}
	//疑似交点
	if (inter)
	{
		//平面上の最近接点を疑似交点とする
		//*inter = 
	}

	return true;
}