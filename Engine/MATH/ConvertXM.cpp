#include "ConvertXM.h"

Matrix4 ConvertXM::ConvertXMMATtoMat4(XMMATRIX XMMat) {
	Matrix4 result;
	for (uint32_t i = 0; i < 4; i++) {

		result.m[i][0] = XMVectorGetX(XMMat.r[i]);
		result.m[i][1] = XMVectorGetY(XMMat.r[i]);
		result.m[i][2] = XMVectorGetZ(XMMat.r[i]);
		result.m[i][3] = XMVectorGetW(XMMat.r[i]);
	}


	return result;
}

XMMATRIX ConvertXM::ConvertMat4toXMMAT(Matrix4 m) {
	XMMATRIX result;
	result = XMMatrixSet(
		m.m[0][0], m.m[0][1], m.m[0][2], m.m[0][3],
		m.m[1][0], m.m[1][1], m.m[1][2], m.m[1][3],
		m.m[2][0], m.m[2][1], m.m[2][2], m.m[2][3],
		m.m[3][0], m.m[3][1], m.m[3][2], m.m[3][3]);

	return result;
}

Vector3 ConvertXM::ConvertXMFlo3toVec3(XMFLOAT3 XMFlo3) {
	Vector3 result;
	result.x = XMFlo3.x;
	result.y = XMFlo3.y;
	result.z = XMFlo3.z;

	return result;
}

XMFLOAT3 ConvertXM::ConvertVec3toXMFlo3(Vector3 vec3) {
	XMFLOAT3 result;
	result.x = vec3.x;
	result.y = vec3.y;
	result.z = vec3.z;

	return result;
}

Vector4 ConvertXM::XMVECToVec4(XMVECTOR XMVEC) {
	Vector4 result;
	result.x = XMVEC.m128_f32[0];
	result.y = XMVEC.m128_f32[1];
	result.z = XMVEC.m128_f32[2];
	result.w = XMVEC.m128_f32[3];

	return result;
}

XMVECTOR ConvertXM::Vec4ToXMVEC(Vector4 Vec4) {
	XMVECTOR result;
	result.m128_f32[0] = Vec4.x;
	result.m128_f32[1] = Vec4.y;
	result.m128_f32[2] = Vec4.z;
	result.m128_f32[3] = Vec4.w;

	return result;
}