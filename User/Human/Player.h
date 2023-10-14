#pragma once
/**
 * @file Player.h
 * @brief
 */
#include "Human.h"

#include "SkillIntegrate.h"


class Player :
	public Human
{
public:
	Player();
	~Player()override;
	/// シーンの更新を行う
	void Initialize()override;
	/// シーンの更新を行う
	void Update(Input* input,bool isTitle = false)override;
	/// シーンの描画を行う
	void Draw(DirectXCommon* dxCommon)override;
	/// リセットを行う
	void Reset() override;




	void SetPos(Vector3 pos) { object_->wtf.position = pos; };
	void MatUpdate() { object_->UpdateMatrix(); };
	Transform GetTransform() { return object_->wtf; };

	// 種族番号取得
	uint32_t HowTribe() { return Tribe_; };
private:
	void Move(Input* input);
	void ColisionUpdate();
	void OnColision();
private:
	const uint32_t Tribe_ = 0;
	bool nowTitle = false;

	Model* model_;
	Model* reticleMD_;
	Object3d* object_;
	Object3d* reticle;
	Transform shotPos;
	float mouseSensitivity_ = 0.099f;	//マウス感度 0.05
	//移動速度
	const float kMoveSpeed_ = 0.5f;
	//旋回速度
	const float kTurnSpeed_ = Affin::radConvert(10);
	bool isRun_ = false;
	//移動ベクトル
	Vector3 velocity_;
	Vector3 faceAngle_;


	Weapon* weapon_[2];
	bool isWeaponOn = true;
	// スキル用
private:
	PointDash* pointDash_;
	bool nowSetPoint;
	bool wallHit;
	// 前フレーム移動ベクトル
	Vector3 oldVelocity_;

	//コライダー
public:
	void SetSphere(std::vector<SphereCollider*> sphere_) { sphere = sphere_; }
	std::vector<SphereCollider*> GetSphere() { return sphere; }
private:
	uint32_t SPHERE_COLISSION_NUM;	//コライダー（スフィア）の数
	std::vector<Matrix4>* collisionBonesMat;	//当たり判定用のボーンのワールド行列 // fbx化後の仕様予定
	std::vector<SphereCollider*> sphere;
	Ray* ray;
	std::vector<Vector3> spherePos;
	std::vector<Object3d*> coliderPosTest_;

};

