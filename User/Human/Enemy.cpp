#include "Enemy.h"

Enemy::Enemy() {

}
Enemy::~Enemy() {
	delete model_;
	delete weapon_;
	delete rayHit;
	for (int i = 0; i < SPHERE_COLISSION_NUM; i++) {
		CollisionManager::GetInstance()->RemoveCollider(sphere[i]);
		delete sphere[i];

	}
	CollisionManager::GetInstance()->RemoveCollider(ray);
	delete ray;
}

///
void Enemy::Initialize() {
	isFound = false;
	isDead = false;
	nowTitle = false;
	model_ = Model::LoadFromOBJ("Cube2");

	object_ = Object3d::Create();
	object_->SetModel(model_);
	object_->Initialize();

	reticle = Object3d::Create();
	reticle->SetModel(model_);
	reticle->Initialize();

	weapon_ = new Assault();
	weapon_->Initialize();

	particle_ = new ParticleManager();
	particle_->Initialize();
	particle_->LoadTexture("red.png");
	particle_->Update();
	onPatTime_ = 0;
	onPat_ = false;

	//当たり判定用
	SPHERE_COLISSION_NUM = 1;
	sphere.resize(SPHERE_COLISSION_NUM);
	spherePos.resize(SPHERE_COLISSION_NUM);
	//FbxO_.get()->isBonesWorldMatCalc = true;	// ボーンの行列を取得するか
	coliderPosTest_.resize(SPHERE_COLISSION_NUM);

	//rayvec = Affin::GetWorldTrans(reticle->wtf.matWorld) - Affin::GetWorldTrans(object_->wtf.matWorld);
	rayvec = -(Affin::GetWorldTrans(object_->wtf.matWorld) - Affin::GetWorldTrans(reticle->wtf.matWorld));

	for (int i = 0; i < SPHERE_COLISSION_NUM; i++) {
		sphere[i] = new SphereCollider;
		CollisionManager::GetInstance()->AddCollider(sphere[i]);
		spherePos[i] = Affin::GetWorldTrans(object_->wtf.matWorld);
		sphere[i]->SetObject3d(object_);
		sphere[i]->SetBasisPos(&spherePos[i]);
		sphere[i]->SetRadius(1.0f);
		sphere[i]->Update();
		sphere[i]->SetAttribute(COLLISION_ATTR_ENEMIES);
		//test
		coliderPosTest_[i] = Object3d::Create();
		coliderPosTest_[i]->SetModel(model_);
		coliderPosTest_[i]->wtf.position = rayvec;
		coliderPosTest_[i]->wtf.scale = Vector3{ sphere[i]->GetRadius(),sphere[i]->GetRadius() ,sphere[i]->GetRadius() };
		coliderPosTest_[i]->wtf.rotation = { 0,0,0 };
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
	object_->SetColor({ 0,0,0 });
	assert(input);
	nowTitle = false;
	nowTitle = !isTitle;

	object_->Update();
	reticle->Update();

	//particle_->SetTransform(object_->wtf);
	particle_->Update();

	if (isFire == true && isDead == false) {
		weapon_->Shot(object_->wtf, reticle->wtf, ENEMY);
	}
	weapon_->Update(input, isSlow);

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
		for (int i = 0; i < SPHERE_COLISSION_NUM; i++) {
			//coliderPosTest_[i]->Draw();
		}
		Object3d::PostDraw();
		if (nowTitle) {
			weapon_->Draw(dxCommon);
		}
	}
	particle_->Draw();
}

/// リセットを行う
void Enemy::Reset() {
	//delete model_;
	//delete weapon_;
	for (int i = 0; i < SPHERE_COLISSION_NUM; i++) {
		CollisionManager::GetInstance()->RemoveCollider(sphere[i]);
		//delete sphere[i];

	}
}

/// <summary>
/// 撃つ方向に向かせる
/// </summary>
void Enemy::FrontFace() {
	Vector3 faceAngle = { 0,0,0 };
	faceAngle.y = (float)atan2(object_->wtf.position.x - reticle->wtf.position.x, object_->wtf.position.z - reticle->wtf.position.z);
	if (isFire == true) {
		frontVec_ = faceAngle;
	}if (isFire == false) {
		frontVec_ = restRotate_;
	}
	if (!isDead) {
		ImGui::Begin("faceAngle_Y");
		ImGui::Text("Angle : Y %f", faceAngle.y);
		ImGui::End();

	}

	object_->wtf.rotation = frontVec_;
}

void Enemy::ColiderUpdate() {

	isBlocked = false;
	isFound = false;
	isFire = false;

	//rayvec = Affin::GetWorldTrans(reticle->wtf.matWorld) - Affin::GetWorldTrans(object_->wtf.matWorld);
	rayvec = -(Affin::GetWorldTrans(object_->wtf.matWorld) - Affin::GetWorldTrans(reticle->wtf.matWorld));
	ray->SetDir(Affin::GetWorldTrans(reticle->wtf.matWorld));

	for (int i = 0; i < SPHERE_COLISSION_NUM; i++) {
		if (sphere[i]->GetIsHit() == true && sphere[i]->GetCollisionInfo().collider_->GetAttribute() == COLLISION_ATTR_PLAYERBULLETS) {
			OnColision();
			// パーティクルなぜかXそのままYZ入れ替えると治る
			Vector3 patPos = { object_->wtf.position.x,object_->wtf.position.z,object_->wtf.position.y };
			particle_->RandParticle(patPos);
		}
	}

	for (int i = 0; i < SPHERE_COLISSION_NUM; i++) {
		spherePos[i] = object_->wtf.position;
		coliderPosTest_[i]->wtf.position = ray->GetDir();
		sphere[i]->Update();
		coliderPosTest_[i]->Update();
	}
	ray->Update();

	if (CollisionManager::GetInstance()->Raycast(*ray, COLLISION_ATTR_BARRIEROBJECT, rayHit)) {
		isFound = false;
		isBlocked = true;

		//ImGui::Begin("eneRayHitBarrier");
		//ImGui::Text("HIT : dis %f", rayHit->distance);
		//ImGui::End();

	}
	if (CollisionManager::GetInstance()->Raycast(*ray, COLLISION_ATTR_PLAYER, rayHit)) {
		isFound = true;
		if (isBlocked == false) {
			isFire = true;
			//ImGui::Begin("eneRayHitPlayer");
			//ImGui::Text("HIT : dis %f", rayHit->distance);
			//ImGui::End();
		}
	}
	if (isDead) {
		for (int i = 0; i < SPHERE_COLISSION_NUM; i++) {
			CollisionManager::GetInstance()->RemoveCollider(sphere[i]);
			//delete sphere[i];
		}
		CollisionManager::GetInstance()->RemoveCollider(ray);
		if (onPat_) {
			onPatTime_--;
			Vector3 patPos = { object_->wtf.position.x,object_->wtf.position.z,object_->wtf.position.y };
			particle_->RandParticle(patPos, 15);
		}
	}
	if (onPatTime_ < 1) {
		onPat_ = false;
	}
}

void Enemy::OnColision()
{
	object_->SetColor({ 1,0,0 });
	hp -= 1;
	if (hp < 1) {
		isDead = true;
		onPat_ = true;
		onPatTime_ = 5;
	}
}
