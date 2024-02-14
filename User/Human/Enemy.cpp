/**
 * @file Enemy.cpp
 * @brief
 */
#include "Enemy.h"
#include <random>

Enemy::Enemy() {

}
Enemy::~Enemy() {
	delete model_;
	delete weapon_;
	delete rayHit;
	for (uint32_t i = 0; i < SPHERE_COLISSION_NUM; i++) {
		CollisionManager::GetInstance()->RemoveCollider(sphere[i]);
		delete sphere[i];
		delete coliderPosTest_[i];
	}
	CollisionManager::GetInstance()->RemoveCollider(ray);
	delete ray;
	delete object_;
	delete reticle;
}
	//乱数生成装置
	std::random_device seed_gen;
	std::mt19937_64 engine(seed_gen());
	std::uniform_real_distribution<float>dist(0.0f, 50.0f);

///
void Enemy::Initialize() {
	isFound = false;
	isDead = false;
	nowTitle = false;
	model_ = Model::LoadFromOBJ("ene");

	object_ = Object3d::Create();
	object_->SetModel(model_);
	object_->Initialize();

	reticle = Object3d::Create();
	reticle->SetModel(model_);
	reticle->Initialize();


	if (useWeapon_ == WP_SHOTGUN) {
		weapon_ = new Shotgun();
	}
	else if(useWeapon_ == WP_ASSAULT){
		weapon_ = new Assault();
	}
	else if (useWeapon_ == WP_BOMFIRE)
	{
		weapon_ = new BomFire();
	}
	weapon_->Initialize();

	particle_ = std::make_unique<ParticleManager>();
	particle_->Initialize();
	particle_->LoadTexture("red.png");
	particle_->Update();
	onPatTime_ = 0;
	onPat_ = false;

	//当たり判定用
	sphere.resize(SPHERE_COLISSION_NUM);
	spherePos.resize(SPHERE_COLISSION_NUM);
	//FbxO_.get()->isBonesWorldMatCalc = true;	// ボーンの行列を取得するか
	coliderPosTest_.resize(SPHERE_COLISSION_NUM);

	rayvec = -(Affin::GetWorldTrans(object_->wtf.matWorld) - Affin::GetWorldTrans(reticle->wtf.matWorld));

	for (uint32_t i = 0; i < SPHERE_COLISSION_NUM; i++) {
		sphere[i] = new SphereCollider;
		CollisionManager::GetInstance()->AddCollider(sphere[i]);
		spherePos[i] = Affin::GetWorldTrans(object_->wtf.matWorld);
		sphere[i]->SetObject3d(object_);
		sphere[i]->SetBasisPos(&spherePos[i]);
		sphere[i]->SetRadius(2.0f);
		sphere[i]->Update();
		sphere[i]->SetAttribute(COLLISION_ATTR_ENEMIES);
		//test
		coliderPosTest_[i] = Object3d::Create();
		coliderPosTest_[i]->SetModel(Model::LoadFromOBJ("sphere"));
		coliderPosTest_[i]->wtf.position = Affin::GetWorldTrans(object_->wtf.matWorld);
		coliderPosTest_[i]->wtf.scale = Vector3{ sphere[i]->GetRadius(),sphere[i]->GetRadius() ,sphere[i]->GetRadius() };
		coliderPosTest_[i]->wtf.rotation.InIt();
		coliderPosTest_[i]->Update();
	}
	ray = new RayCollider;

	ray->SetStart(Affin::GetWorldTrans(object_->wtf.matWorld));
	ray->SetDir(rayvec);
	ray->SetObject3d(object_);
	CollisionManager::GetInstance()->AddCollider(ray);
	rayHit = new RaycastHit;
	hp = 3;
}

///
void Enemy::Update(Input* input, bool isTitle) {
	nowTitle = false;
	nowTitle = !isTitle;

	HitMyColor();
	object_->Update();
	reticle->Update();

	//particle_->SetTransform(object_->wtf);
	particle_->Update();

	if (isFire == true && isDead == false) {
		weapon_->Shot(object_->wtf, reticle->wtf, ENEMY);
	}
	weapon_->Update(input, _isSlow);

	FrontFace();
	ColiderUpdate();

}

///
void Enemy::Draw(DirectXCommon* dxCommon) {

	if (isDead == false) {
		Object3d::PreDraw(dxCommon->GetCommandList());
		object_->Draw();
		if (nowTitle) {
			//reticle->Draw();
		}
#ifdef _DEBUG
		for (uint32_t i = 0; i < SPHERE_COLISSION_NUM; i++) {
			coliderPosTest_[i]->Draw();
		}
#endif // DEBUG
		Object3d::PostDraw();
		if (nowTitle) {
			weapon_->Draw(dxCommon);
		}
	}
	particle_->Draw();
}

/// リセットを行う
void Enemy::Reset() {

}

/// 武器の番号セット
void Enemy::SetWeaponNum(uint32_t WeaponNum)
{
	useWeapon_ = WeaponNum;
}

/// <summary>
/// 撃つ方向に向かせる
/// </summary>
void Enemy::FrontFace() {
	Vector3 faceAngle, resultRot;
	faceAngle.InIt();
	faceAngle.y = (float)atan2(reticle->wtf.position.x - object_->wtf.position.x, reticle->wtf.position.z - object_->wtf.position.z);
	if (isFound == true) {
		stateRotate_ = object_->wtf.rotation;
		frontVec_ = faceAngle;
	}
	else {
		stateRotate_ = faceAngle;
		frontVec_ = restRotate_;
	}
	if (isLost == true) {
		stateRotate_ = object_->wtf.rotation;
		easeTimer++;

		easetime = (float)easeTimer / easeMaxTime;
		if (easeTimer <= easeMaxTime) {
			frontVec_ = Easing::InQuintVec3({ 0,(faceAngle.y + 3.141592f / 2) * 1,0}, restRotate_, (float)easetime);
			if (easeTimer == easeMaxTime) {
				easeTimer = 1;
				easetime = 0;
				isEaseEnd = true;
				isLost = false;
			}
		}
	}
	resultRot = frontVec_;
	object_->wtf.rotation = resultRot;
}

void Enemy::ColiderUpdate() {
	oldFound = isFound;
	isFound = false;
	isBlocked = false;
	isFire = false;

	//rayvec = Affin::GetWorldTrans(reticle->wtf.matWorld) - Affin::GetWorldTrans(object_->wtf.matWorld);
	rayvec = -(Affin::GetWorldTrans(object_->wtf.matWorld) - Affin::GetWorldTrans(reticle->wtf.matWorld));
	ray->SetDir(Affin::GetWorldTrans(reticle->wtf.matWorld));

	for (uint32_t i = 0; i < SPHERE_COLISSION_NUM; i++) {
		if (sphere[i]->GetIsHit() == true) {
			if (sphere[i]->GetCollisionInfo().collider_->GetAttribute() == COLLISION_ATTR_PLAYERBULLETS) {
				OnColision();
				// パーティクルなぜかXそのままYZ入れ替えると治る
				Vector3 patPos = { object_->wtf.position.x,object_->wtf.position.z,object_->wtf.position.y };
				particle_->RandParticle(10, patPos);
			}
		}
	}

	for (uint32_t i = 0; i < SPHERE_COLISSION_NUM; i++) {
		spherePos[i] = object_->wtf.position;
		coliderPosTest_[i]->wtf.position = Affin::GetWorldTrans(object_->wtf.matWorld);
		sphere[i]->Update();
		coliderPosTest_[i]->Update();
	}
	ray->Update();


	if (CollisionManager::GetInstance()->Raycast(*ray, COLLISION_ATTR_PLAYER, rayHit)) {
		isFound = true;
		if (CollisionManager::GetInstance()->Raycast(*ray, COLLISION_ATTR_BARRIEROBJECT, rayHit)) {
			isFound = false;
			isBlocked = true;
		}
	}
	if (isBlocked == false && isFound == true) {
		isFire = true;
	}
	if (isBlocked == true && oldFound == true) {
		isLost = true;
	}
	if (isDead) {
		for (uint32_t i = 0; i < SPHERE_COLISSION_NUM; i++) {
			CollisionManager::GetInstance()->RemoveCollider(sphere[i]);
			//delete sphere[i];
		}
		CollisionManager::GetInstance()->RemoveCollider(ray);
		if (onPat_) {
			onPatTime_--;
			Vector3 patPos = { object_->wtf.position.x,object_->wtf.position.z,object_->wtf.position.y };
			particle_->RandParticle(15, patPos);
		}
	}
	if (onPatTime_ < 1) {
		onPat_ = false;
	}
}

void Enemy::OnColision()
{
	hp--;
	isHitEffect = true;
	if (hp < 1) {
		isDead = true;
		onPat_ = true;
		onPatTime_ = 5;
	}
}
void Enemy::HitMyColor()
{
	if (isHitEffect == true) {
		object_->SetColor({ 1,0,0,1.0f });
		hitTime_++;
		if (hitTime_ >= MAX_HITTIME) {
			isHitEffect = false;
			hitTime_ = 0;
		}
	}
	else {
		if (useWeapon_ == WP_ASSAULT) {
			object_->SetColor({ 0.8f,0.8f,0.8f,1 });
		}
		else if (useWeapon_ == WP_SHOTGUN) {
			object_->SetColor({ 0,0.5f,0,1 });
		}
		else if (useWeapon_ == WP_BOMFIRE) {
			object_->SetColor({ 0.8f,0.1f,0.1f,1 });
		}
	}
}