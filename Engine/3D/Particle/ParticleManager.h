#pragma once
#pragma warning(push)
#pragma warning(disable: 4819)
#pragma warning(disable: 4820)
#pragma warning(disable: 4061)
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>
#include <forward_list>
#include <array>

#pragma warning(pop)

#include "Affin.h"
#include "Transform.h"
#include "Camera.h"

/// <summary>
/// 3Dオブジェクト
/// </summary>
class ParticleManager
{
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	

public: // サブクラス
	// 定数バッファ用データ構造体（マテリアル）
	struct ConstBufferDataMaterial {
		Vector4 color; // 色 (RGBA)
	};

	// 頂点データ構造体
	struct VertexPos
	{
		Vector3 pos; // xyz座標
		float scale;
	};

	// 定数バッファ用データ構造体
	struct ConstBufferData
	{
		Matrix4 mat;
		Matrix4 matBillboard;	// ビルボード行列
	};

	//パーティクル一粒
	struct Particle {
		
		//座標
		Vector3 position = {};
		//速度
		Vector3 velocity = {};
		//加速度
		Vector3 accel = {};
		//現在フレーム
		uint32_t frame = 0;
		//過去フレーム
		uint32_t num_frame = 0;

		//スケール
		float scale = 1.0f;
		//初期値
		float s_scale = 1.0f;
		//最終値
		float e_scale = 0.0f;

		Vector4 color; // 色 (RGBA)

	};

private: // 定数
	//const uint32_t division = 50;					// 分割数
	//const float radius;				// 底面の半径
	//const float prizmHeight;			// 柱の高さ
	//const uint32_t planeCount = division * 2 + division * 2;		// 面の数
	//static const uint32_t vertexCount = 30;//頂点数
	const uint32_t vertexCount = _countof(vertices);

public: // 静的メンバ関数
	/// <summary>
	/// 静的初期化
	/// </summary>
	/// <param name="device">デバイス</param>
	/// <param name="window_width">画面幅</param>
	/// <param name="window_height">画面高さ</param>
	static void StaticInitialize(ID3D12Device* device, ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// グラフィックパイプライン生成
	/// </summary>
	/// <returns>成否</returns>
	static void InitializeGraphicsPipeline();

private: // 静的メンバ変数
	
	// デバイス
	static Microsoft::WRL::ComPtr<ID3D12Device> device;
	// コマンドリスト
	static Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> cmdList;
	// ルートシグネチャ
	static ComPtr<ID3D12RootSignature> rootsignature;
	// パイプラインステートオブジェクト
	static ComPtr<ID3D12PipelineState> pipelinestate;

	// デスクリプタサイズ
	UINT descriptorHandleIncrementSize;
	// デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> descHeap;
	// 頂点バッファ
	ComPtr<ID3D12Resource> vertBuff;
	// テクスチャバッファ
	ComPtr<ID3D12Resource>texbuff;
	// シェーダリソースビューのハンドル(CPU)
	CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV;
	// シェーダリソースビューのハンドル(CPU)
	CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;
	
	// 頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView;
	// 頂点データ配列
	VertexPos vertices[2024];
	// 定数バッファ
	ComPtr<ID3D12Resource> constBuff; 

	//パーティクル配列
	std::forward_list<Particle>particles;

private:// メンバ関数

	

	/// <summary>
	/// デスクリプタヒープの初期化
	/// </summary>
	void InitializeDescriptorHeap();

	/// <summary>
	/// テクスチャ読み込み
	/// </summary>
	void LoadTexture();

	/// <summary>
	/// モデル作成
	/// </summary>
	void CreateModel();

public: // メンバ関数
	/// <summary>
	/// 3Dオブジェクト生成
	/// </summary>
	/// <returns></returns>
	ParticleManager* Create();
	static ParticleManager* GetInstance();

	ParticleManager();
	~ParticleManager();

	void LoadTexture(const std::string& fileName);
	bool Initialize();
	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// マネージャーの座標をもとにランダムに放出する
	/// </summary>
	void RandParticle();
	void RandParticle(Vector3 pos, uint32_t life = 10);

	/// <summary>
	/// パーティクルの追加
	/// </summary>
	///	<param name="life">生存時間</param>
	///	<param name="m_Pos">初期座標</param>
	///	<param name="velocity">速度</param>
	///	<param name="accel">加速度</param>
	void Add(uint32_t life, Vector3 position, Vector3 velociy, Vector3 accel, float start_scale, float end_scale);

	static void SetCamera(Camera* camera) { ParticleManager::camera_ = camera; }

	void SetTransform(Transform wtf) { wtf_ = wtf; };

	void Setposition(Vector3 position) { wtf_.position = position; };
private: // メンバ変数
	static Camera* camera_;
	// ローカルスケール
	Transform wtf_;

	ConstBufferDataMaterial* constMapMaterial = nullptr;
};