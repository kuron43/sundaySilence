#pragma once
#include "Object3d.h"
#include "MathUtility.h"


class ObjectParticle
{
public:
	/// <summary>
	/// 作成
	/// </summary>
	/// <returns></returns>
	static ObjectParticle* Create(const Vector3& pos_,Model* model_,const Vector3& velocity);

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="pos_"></param>
	/// <param name="model_"></param>
	/// <param name="pipeline_"></param>
	void Init(const Vector3& pos_,Model* model_,const Vector3& velocity);

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="viewPro"></param>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 死んだかゲッター
	/// </summary>
	/// <returns></returns>
	const bool GetIsDead() const
	{
		return isDead;
	}

private:
	// オブジェクト
	std::unique_ptr<Object3d> object3d = nullptr;

	Vector3 velocity = { 0,0,0 };

	// 生存時間
	uint32_t lifeTimer = 0;
	const uint32_t lifeTime = 60;

	float easeTimer = 0;
	const float easeTime = 20;

	// 終了かどうか
	bool isDead = false;
};

class ObjParticleManager
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Init();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 爆発演出
	/// </summary>
	/// <param name="pos_"></param>
	void SetExp(const Vector3& pos_);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="pos_"></param>
	void SetSmallExp(const Vector3& pos_);

public:
	// インスタンス
	static ObjParticleManager* GetInstance();

	// 解放
	void Delete();

private:
	// インスタンス
	static ObjParticleManager* objParticleManager;
	std::list<std::unique_ptr<ObjectParticle>> objParticles;

	// モデル
	Model* model = nullptr;

private:
	ObjParticleManager() = default;
	~ObjParticleManager() = default;
	ObjParticleManager(const ObjParticleManager&) = default;
	const ObjParticleManager& operator=(const ObjParticleManager&) = delete;
};