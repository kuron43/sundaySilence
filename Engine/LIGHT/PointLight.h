#pragma once

#include <DirectXMath.h>

class PointLight
{
private://エイリアス
	//Microsoft::WRL::を省略
	template <class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirecX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public://サブクラス
	struct ConstBufferData
	{
		XMFLOAT3 lightpos;
		float pad1;

		XMFLOAT3 lightcolor;
		float pad2;

		XMFLOAT3 lightatten;
		unsigned int active;
	};

public:

	inline void SetLightPos(const XMFLOAT3& lightpos) {
		lightpos_ = lightpos;
	}
	inline const XMFLOAT3& GetLightPos() { return lightpos_; }
	inline void SetLightColor(const XMFLOAT3& lightcolor) {
		lightcolor_ = lightcolor;
	}
	inline const XMFLOAT3& GetLightColor() { return lightcolor_; }
	inline void SetLightAtten(const XMFLOAT3& lightAtten) {
		lightAtten_ = lightAtten;
	}
	inline const XMFLOAT3& GetLightAtten() { return lightAtten_; }
	inline void SetActive(bool active) { active_ = active; }
	inline bool IsActive() { return active_; }



private:

	XMFLOAT3 lightpos_ = { 0,0,0 };
	XMFLOAT3 lightcolor_ = { 1,1,1 };
	XMFLOAT3 lightAtten_ = { 1.0f,1.0f,1.0f };
	bool active_ = false;

};