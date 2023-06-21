#include "Affin.h"
#include "math.h"
#include <cmath>

/// <summary>
/// 単位行列設定
/// </summary>
Matrix4 Affin::matUnit() {
	Matrix4 matUnit;

	matUnit = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			   0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };

	return matUnit;
}

/// <summary>
/// 平行移動
/// </summary>
Matrix4 Affin::matTrans(float moveX, float moveY, float moveZ) {
	Matrix4 matTrans;

	matTrans = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,  1.0f,  0.0f,  0.0f,
				0.0f, 0.0f, 1.0f, 0.0f, moveX, moveY, moveZ, 1.0f };

	return matTrans;
}

/// <summary>
/// 平行移動
/// </summary>
Matrix4 Affin::matTrans(Vector3 move) {
	Matrix4 matTrans;

	matTrans = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,   1.0f,   0.0f,   0.0f,
				0.0f, 0.0f, 1.0f, 0.0f, move.x, move.y, move.z, 1.0f };

	return matTrans;
}

/// <summary>
/// 度数法 -> ラジアン
/// </summary>
float Affin::radConvert(float value) {
	float radValue;

	radValue = value * (PI / 180);

	return radValue;
}

/// <summary>
/// ラジアン -> 度数法
/// </summary>
float Affin::degConvert(float value) {
	float degValue;

	degValue = value * (180 / PI);

	return degValue;
}

/// <summary>
/// 回転 X方向
/// </summary>
Matrix4 Affin::matRotateX(float rotationX) {
	float cosRad = cos(rotationX);
	float sinRad = sin(rotationX);
	Matrix4 matRotX;

	matRotX = { 1.0f, 0.0f,    0.0f,   0.0f, 0.0f, cosRad, sinRad, 0.0f,
			   0.0f, -sinRad, cosRad, 0.0f, 0.0f, 0.0f,   0.0f,   1.0f };

	return matRotX;
}

/// <summary>
/// 回転 Y方向
/// </summary>
Matrix4 Affin::matRotateY(float rotationY) {
	float cosRad = cos(rotationY);
	float sinRad = sin(rotationY);
	Matrix4 matRotY;

	matRotY = { cosRad, 0.0f, -sinRad, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			   sinRad, 0.0f, cosRad,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f };

	return matRotY;
}

/// <summary>
/// 回転 Z方向
/// </summary>
Matrix4 Affin::matRotateZ(float rotationZ) {
	float cosRad = cos(rotationZ);
	float sinRad = sin(rotationZ);
	Matrix4 matRotZ;

	matRotZ = { cosRad, sinRad, 0.0f, 0.0f, -sinRad, cosRad, 0.0f, 0.0f,
			   0.0f,   0.0f,   1.0f, 0.0f, 0.0f,    0.0f,   0.0f, 1.0f };

	return matRotZ;
}

/// <summary>
/// 回転 Z->X->Y
/// </summary>
Matrix4 Affin::matRotation(float rotateX, float rotateY, float rotateZ) {

	Matrix4 x = matRotateX(rotateX);
	Matrix4 y = matRotateY(rotateY);
	Matrix4 z = matRotateZ(rotateZ);
	Matrix4 matRot;

	x *= z;
	y *= x;
	matRot = y;

	return matRot;
}

/// <summary>
/// 回転 Z->X->Y
/// </summary>
Matrix4 Affin::matRotation(Vector3 rotate) {

	Matrix4 x = matRotateX(rotate.x);
	Matrix4 y = matRotateY(rotate.y);
	Matrix4 z = matRotateZ(rotate.z);
	Matrix4 matRot;

	x *= z;
	y *= x;
	matRot = y;

	return matRot;
}

/// <summary>
/// 拡縮
/// </summary>
Matrix4 Affin::matScale(float scaleX, float scaleY, float scaleZ) {

	Matrix4 matScale = { scaleX, 0.0f, 0.0f,   0.0f, 0.0f, scaleY, 0.0f, 0.0f,
						0.0f,   0.0f, scaleZ, 0.0f, 0.0f, 0.0f,   0.0f, 1.0f };

	return matScale;
}

/// <summary>
/// 拡縮
/// </summary>
Matrix4 Affin::matScale(Vector3 scale) {

	Matrix4 matScale = { scale.x, 0.0f, 0.0f,    0.0f, 0.0f, scale.y, 0.0f, 0.0f,
						0.0f,    0.0f, scale.z, 0.0f, 0.0f, 0.0f,    0.0f, 1.0f };

	return matScale;
}

/// <summary>
/// 拡縮*回転*移動
/// </summary>
Matrix4 Affin::matWorld(Vector3 move, Vector3 rotate, Vector3 scale) {
	Matrix4 scaleM = matScale(scale);
	Matrix4 rotateM = matRotation(rotate);
	Matrix4 moveM = matTrans(move);
	Matrix4 matWorld = matUnit();

	matWorld *= scaleM;
	matWorld *= rotateM;
	matWorld *= moveM;

	return matWorld;
}

/// <summary>
///	ベクトルと行列の掛け算
/// </summary>
Vector3 Affin::VecMat(Vector3 vec, Matrix4 mat) {

	float x = vec.x * mat.m[0][0] + vec.y * mat.m[1][0] + vec.z * mat.m[2][0] + 0 * mat.m[3][0];

	float y = vec.x * mat.m[0][1] + vec.y * mat.m[1][1] + vec.z * mat.m[2][1] + 0 * mat.m[3][1];

	float z = vec.x * mat.m[0][2] + vec.y * mat.m[1][2] + vec.z * mat.m[2][2] + 0 * mat.m[3][2];

	Vector3 re = { x, y, z };

	return re;
}

Vector3 Affin::VecMat3D(Vector3 vec, Matrix4 mat) {
	Vector3 Result = { 0, 0, 0 };

	Result.x = vec.x * mat.m[0][0] + vec.y * mat.m[1][0] + vec.z * mat.m[2][0] * 1 * mat.m[3][0];

	Result.y = vec.x * mat.m[0][1] + vec.y * mat.m[1][1] + vec.z * mat.m[2][1] * 1 * mat.m[3][1];

	Result.z = vec.x * mat.m[0][2] + vec.y * mat.m[1][2] + vec.z * mat.m[2][2] * 1 * mat.m[3][2];

	return Result;
}

/// <summary>
///	ワールド座標取得
/// </summary>
Vector3 Affin::GetWorldTrans(Matrix4 matrix) {
	Vector3 mat;

	mat.x = matrix.m[3][0];
	mat.y = matrix.m[3][1];
	mat.z = matrix.m[3][2];

	return mat;
}

/// <summary>
///	W 除算
/// </summary>
Vector3 Affin::wDivision(Vector3 vector, Matrix4 matrix) {
	Vector3 result;
	float w;

	w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] +
		matrix.m[3][3];

	result = {
	  (vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] +
	   matrix.m[3][0]) /
		w,
	  (vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] +
	   matrix.m[3][1]) /
		w,
	  (vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] +
	   matrix.m[3][2]) /
		w };

	return result;
}

//sin、cosを両方出す
void Affin::SinCos(float& sin_, float& cos_, float angle)
{
	sin_ = sin(angle);
	cos_ = cos(angle);
}

