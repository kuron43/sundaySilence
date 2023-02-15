#pragma once
#include <DirectXMath.h>
#include "Matrix4.h"

using namespace DirectX;

class ConvertXM
{

public:
	static Matrix4 ConvertXMMATtoMat4( XMMATRIX XMMat);
	static XMMATRIX ConvertMat4toXMMAT(Matrix4 Mat4);

	static Vector3 ConvertXMFlo3toVec3(XMFLOAT3 XMFlo3);
	static XMFLOAT3 ConvertVec3toXMFlo3(Vector3 vec3);
private:
	
	XMMATRIX xmMat;
	Matrix4 mat4;

	XMFLOAT3 xmFlo3;
	Vector3 vec3;

};

