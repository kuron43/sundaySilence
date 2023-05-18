#pragma once
#include <DirectXMath.h>
#include <d3d12.h>
#include <wrl.h>

#include "Affin.h"

class DirectionalLight {
private: //静的メンバ変数
	//デバイス
	static ID3D12Device* device;

private://エイリアス
	////Microsoft::WRL::を省略
	template <class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	////DirecX::を省略
	//using XMFLOAT2 = DirectX::XMFLOAT2;
	//using XMFLOAT3 = DirectX::XMFLOAT3;
	//using XMFLOAT4 = DirectX::XMFLOAT4;
	//using XMVECTOR = DirectX::XMVECTOR;
	//using XMMATRIX = DirectX::XMMATRIX;

public://サブクラス　
	//定数バッファ用データ構造
	struct ConstBufferData
	{
		Vector4 lightv; //ライトへの方向を表すベクトル
		Vector3 lightcolor; //ライトの色
		unsigned int active;
	};

	HRESULT result;

public://静的メイバ関数
	/// <summary>
	/// 静的初期化
	/// </summary>
	static void StaticInitialize(ID3D12Device* device);

	/// <summary>
	/// 初期化
	/// </summary>
	bool Initialize();

	/// <summary>
	/// 定数バッファ転送
	/// </summary>
	void TransferConstBuffer();

	/// <summary>
	/// ライト方向をセット
	/// </summary>
	void SetLightDir(const Vector4& lightdir);

	/// <summary>
	/// ライト色をセット
	/// </summary>
	void SetLightColor(const Vector3& lightcolor);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndex);

	/// <summary>
	/// 有効フラグをセット
	/// </summary>
	/// <param name="active">有効フラグ</param>
	inline void SetActive(bool active) { this->active = active; }


	/// <summary>
	/// 有効チェック
	/// </summary>
	/// <returns>有効フラグ</returns>
	inline bool IsActive() { return active; }

	Vector4 GetLightDir() { return lightdir; }
	Vector3 GetLightColor() { return lightcolor; }

	/// <summary>
	/// インスタンス生成
	/// </summary>
	static DirectionalLight* Create();
private://メンバ変数
	//定数バッファ
	ComPtr<ID3D12Resource> constBuff;
	//ライト光線方向
	Vector4 lightdir = { 1,0,0,0 };
	//ライト色
	Vector3 lightcolor = { 1,1,1, };
	//ダーティフラグ
	bool dirty = false;

	//有効フラグ
	bool active = false;
};

