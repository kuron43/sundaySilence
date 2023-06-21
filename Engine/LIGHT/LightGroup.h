#pragma once
#include <DirectXMath.h>
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "CircleShadow.h"

#include"Affin.h"

class LightGroup
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

public: 
	static const int DirLightNum = 1;

	//点光源の数
	static const int PointLightNum = 3;

	//スポットライトの数
	static const int SpotLightNum = 3;

	//丸影の数
	static const int CircleShadowNum = 1;

public://サブクラス
	struct ConstBufferData
	{
		XMFLOAT3 ambientColor;
		float pad1;

		//平行光源
		DirectionalLight::ConstBufferData dirLights[DirLightNum];
		//点光源用
		PointLight::ConstBufferData pointLights[PointLightNum];
		//スポットライト用
		SpotLight::ConstBufferData spotLights[SpotLightNum];
		//丸影用
		CircleShadow::ConstBufferData circleShadows[CircleShadowNum];
	};
	HRESULT result;

private://静的メンバ変数
	//デバイス
	static ID3D12Device* device;

public:
	//静的メンバ関数

	static void StaticInitialize(ID3D12Device* device);

public:
	/// <summary>
	/// インスタンスの生成
	/// </summary>
	/// <returns></returns>
	static LightGroup* Create();

	/// <summary>
	/// 初期化
	/// </summary>
	bool Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 定数バッファ転送
	/// </summary>
	void TransferConstBuffer();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndex);

	//標準ライト
	void DefaultLightSetting();

	//平行
	void SetAmbientColor(const XMFLOAT3& color) {
		ambientColor = color;
		dirty = true;
	}

	void SetDirLightActive(int index, bool active) {
		assert(0 <= index && index < DirLightNum);
		dirLights[index].SetActive(active);
	}

	void SetDirLightDir(int index, const Vector4& lightdir) {
		assert(0 <= index && index < DirLightNum);
		dirLights[index].SetLightDir(lightdir);
		dirty = true;
	}
	void SetDirLightColor(int index, const Vector3& lightcolor) {
		assert(0 <= index && index < DirLightNum);
		dirLights[index].SetLightColor(lightcolor);
		dirty = true;
	}

	//点光源
	void SetPointLightActive(int index, bool active) {
		assert(0 <= index && index < PointLightNum);
		pointLights[index].SetActive(active);
	}

	void SetPointLightPos(int index, const XMFLOAT3& lightpos) {
		assert(0 <= index && index < PointLightNum);
		pointLights[index].SetLightPos(lightpos);
		dirty = true;
	}

	void SetPointLightColor(int index, const XMFLOAT3& lightcolor) {
		assert(0 <= index && index < PointLightNum);
		pointLights[index].SetLightColor(lightcolor);
		dirty = true;
	}

	void SetPointLightAtten(int index, const XMFLOAT3& lightAtten) {
		assert(0 <= index && index < PointLightNum);
		pointLights[index].SetLightAtten(lightAtten);
		dirty = true;
	}

	//スポットライト
	void SetSpotLightActive(int index, bool active) {
		assert(0 <= index && index < SpotLightNum);
		spotLights[index].SetActive(active);
	}
	void SetSpotLightDir(int index, const XMVECTOR& lightdir) {
		assert(0 <= index && index < SpotLightNum);
		spotLights[index].SetLightDir(lightdir);
		dirty = true;
	}
	void SetSpotLightPos(int index, const XMFLOAT3& lightpos) {
		assert(0 <= index && index < SpotLightNum);
		spotLights[index].SetLightPos(lightpos);
		dirty = true;
	}
	void SetSpotLightColor(int index, const XMFLOAT3& lightcolor) {
		assert(0 <= index && index < SpotLightNum);
		spotLights[index].SetLightColor(lightcolor);
		dirty = true;
	}
	void SetSpotLightAtten(int index, const XMFLOAT3& lightAtten) {
		assert(0 <= index && index < SpotLightNum);
		spotLights[index].SetLightAtten(lightAtten);
		dirty = true;
	}
	void SetSpotLightFactorAngle(int index, const XMFLOAT2& lightFactorAngle) {
		assert(0 <= index && index < SpotLightNum);
		spotLights[index].SetLightFactorAngle(lightFactorAngle);
		dirty = true;
	}


	//シャドウ
	void SetCircleShadowActive(int index, bool active) {
		assert(0 <= index && index < CircleShadowNum);
		circleShadows[index].SetActive(active);
	}

	void SetCircleShadowCasterPos(int index, const XMFLOAT3& casterPos) {
		assert(0 <= index && index < CircleShadowNum);
		circleShadows[index].SetCasterPos(casterPos);
		dirty = true;
	}

	void SetCircleShadowDir(int index, const XMVECTOR& lightdir) {
		assert(0 <= index && index < CircleShadowNum);
		circleShadows[index].SetDir(lightdir);
		dirty = true;
	}

	void SetCircleShadowDistanceCasterLight(int index, float distanceCasterLight) {
		assert(0 <= index && index < CircleShadowNum);
		circleShadows[index].SetDistanceCasterLight(distanceCasterLight);
		dirty = true;
	}

	void SetCircleShadowAtten(int index, const XMFLOAT3& lightAtten) {
		assert(0 <= index && index < CircleShadowNum);
		circleShadows[index].SetAtten(lightAtten);
		dirty = true;
	}

	void SetCircleShadowFactorAngle(int index, const XMFLOAT2& lightFactorAngle) {
		assert(0 <= index && index < CircleShadowNum);
		circleShadows[index].SetFactorAngle(lightFactorAngle);
		dirty = true;
	}



private:
	//メンバ変数
	//定数バッファ
	ComPtr<ID3D12Resource> constBuff;
	//環境光の色
	XMFLOAT3 ambientColor = { 1,1,1 };

	//平行光源の配列
	DirectionalLight dirLights[DirLightNum];
	//点光源の配列
	PointLight pointLights[PointLightNum];
	//スポットライト配列
	SpotLight spotLights[SpotLightNum];
	//丸影の配列
	CircleShadow circleShadows[CircleShadowNum];

	//ダーティフラグ
	bool dirty = false;

};