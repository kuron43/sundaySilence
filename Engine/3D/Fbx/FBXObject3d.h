/**
 * @file FBXObject3d.h
 * @brief FBXSDKオブジェクトを初期化、更新、描画するクラス
 */
#pragma once
#include "FBXModel.h"
#include "fbx/FBXLoader.h"
#include "Transform.h"
#include "Camera.h"

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>
#include <DirectXMath.h>
#include <string>

class FBXObject3d
{
protected: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public: // サブクラス
	// 定数バッファ用データ構造体（座標変換行列用）
	struct ConstBufferDataTransform
	{
		XMMATRIX viewproj;    // ビュープロジェクション行列
		XMMATRIX world; // ワールド行列
		XMFLOAT3 cameraPos; // カメラ座標（ワールド座標）
	};
	//ボーンの最大数
	static const int MAX_BONES = 320;

	//定数バッファ用のデータ構造体(スキニング)
	struct ConstBufferDataSkin
	{
		XMMATRIX bones[MAX_BONES];
	};


public: // 静的メンバ関数
	/// <summary>
	/// グラフィックパイプラインの生成
	/// </summary>
	static void CreateGraphicsPipeline();

	/// <summary>
	/// グラフィックパイプラインの生成
	/// </summary>
	// setter
	static void SetDevice(ID3D12Device* deviceArg) { FBXObject3d::device = deviceArg; }
	static void SetCamera(Camera* cameraArg) { FBXObject3d::camera = cameraArg; }


private: // 静的メンバ変数
	// デバイス
	static ID3D12Device* device;
	// カメラ
	static Camera* camera;
	// ルートシグネチャ
	static ComPtr<ID3D12RootSignature> rootsignature;
	// パイプラインステートオブジェクト
	static ComPtr<ID3D12PipelineState> pipelinestate;


public: // メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	bool Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// インスタンス取得
	/// </summary>
	static std::unique_ptr<FBXObject3d>Create();


	/// <summary>
	/// 大きさの設定
	/// </summary>
	/// <param name="position">座標</param>
	void SetScale(const Vector3& scale) { this->transform_.scale = scale; }


	/// <summary>
	/// 回転の設定
	/// </summary>
	/// <param name="position">座標</param>
	void SetRotate(const Vector3& rotation) { this->transform_.rotation = rotation; }

	/// <summary>
	/// 座標の設定
	/// </summary>
	/// <param name="position">座標</param>
	void SetPosition(const Vector3& position) { this->transform_.position = position; }

	/// <summary>

	/// 座標の取得
	/// </summary>
	/// <returns>座標</returns>
	const Vector3& GetPosition() const { return transform_.position; }
	const Vector3& GetRotate() const { return transform_.rotation; }
	const Vector3& GetScale() const { return transform_.scale; }

	/// <summary>
	/// モデルをセット
	/// </summary>
	/// <param name="fbxmodel"></param>
	void SetModel(FBXModel* fbxmodelArg) { this->fbxmodel = fbxmodelArg; }

	/// <summary>
	/// フレームカウント指定
	/// </summary>
	/// <param name="flame"></param>
	void SetFlame(int flame);

	/// <summary>
	/// アニメーション再生用
	/// </summary>
	void AnimPlay();
	void AnimStop();
	void AnimIsRotateChange(bool isRotate = true);

	/// <summary>
	/// カメラのゲッター
	/// </summary>
	/// <returns></returns>
	Camera GetCamera();

	/// <summary>
	/// アニメーションタイムゲッター
	/// </summary>
	/// <returns></returns>
	FbxTime GetCurrentTimer();
	// 終了時間ゲット
	FbxTime GetEndTime();
	// アニメーション繰り返し状況ゲット
	bool GetIsAnimRot();
	// FbxTime型をintに変換(なくてもオーバーライドされる)
	int ConvertFbxTimeToInt(FbxTime time);
	// animNumのリセットとアニメーション処理
	void ResetCurrentTime(int animNum);
	// 定数バッファゲッタ
	ID3D12Resource* GetConstBuff() { return constBuffTransform.Get(); };

	/// <summary>
	/// ワールドトランスフォーム取得
	/// </summary>
	/// <returns></returns>
	Transform GetWorldTransform();
	/// <summary>
	/// ワールドトランスフォーム取得
	/// </summary>
	/// <returns></returns>
	Transform* GetWorldTransformPtr();

	/// <summary>
	/// ボーン用
	/// </summary>
	std::vector<Matrix4> bonesMat;
	void ResizeBonesMat(std::vector<FBXModel::Bone> bones);	//ボーンのサイズをクラスターボーンに合わせる
	bool isBonesWorldMatCalc = false;	//ボーンのワールド座標上での計算をするかどうか

	std::vector<Matrix4>* GetBonesMatPtr();	//ボーンのワールド行列ポインタを渡す
	void SetIsBonesWorldMatCalc(bool isCalc);	//ボーン計算フラグのセッター

	/// <summary>
	/// アニメーション開始
	/// </summary>
	void PlayAnimation(int animationNum);

	//補間アニメーションカウント
	void AnimFlameInter(FbxTime nowCount, FbxTime maxCount);

	Transform transform_;

protected: // メンバ変数
	// 定数バッファ
	ComPtr<ID3D12Resource> constBuffTransform;
	// 定数バッファ(スキン)
	ComPtr<ID3D12Resource> constBuffSkin;

	// モデル
	FBXModel* fbxmodel = nullptr;

	//1フレームの時間
	FbxTime frameTime;
	//アニメーション開始時間
	FbxTime startTime;
	//アニメーション終了時間
	FbxTime endTime;
	//現在時間(アニメーション)
	FbxTime currentTime;
	//アニメーション再生中
	bool isPlay = false;
	//アニメーションフレーム指定時フラグ
	bool isChangeFlame = false;
	//アニメーションフラグ
	bool isAnim = true;
	//アニメーション繰り返すか
	bool animRot = true;

};