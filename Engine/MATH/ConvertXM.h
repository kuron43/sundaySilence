#pragma once
#pragma warning(push)
#pragma warning(disable: 4819)
#pragma warning(disable: 4514)
#include <DirectXMath.h>
#pragma warning(pop)

#include "Matrix4.h"
#include "Vector4.h"

using namespace DirectX;

namespace ConvertXM
{
	 Matrix4 ConvertXMMATtoMat4( XMMATRIX XMMat);
	 XMMATRIX ConvertMat4toXMMAT(Matrix4 Mat4);

	 Vector3 ConvertXMFlo3toVec3(XMFLOAT3 XMFlo3);
	 XMFLOAT3 ConvertVec3toXMFlo3(Vector3 vec3);

	 Vector4 XMVECToVec4(XMVECTOR XMVEC);
	 XMVECTOR Vec4ToXMVEC(Vector4 Vec4);
};

