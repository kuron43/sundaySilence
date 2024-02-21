/**
 * @file BomFire.cpp
 * @brief
 */
#include "BomFire.h"


BomFire::BomFire() {
}
BomFire::~BomFire() {
	delete model_;
}

/// 更新を行う
bool BomFire::Initialize() {
	model_ = Model::LoadFromOBJ("stage");
	goShot = true;
	return true;
}

/// 更新を行う
void BomFire::Update(Input* input, bool isSlow) {

	_isSlow = isSlow;
	if (input) {

	}
	if (isSlow == true) {
		speed_ = nomalSpeed * _slowSpeed;
	}
	else
	{
		speed_ = nomalSpeed;
	}
	// 
	if (roadingTime <= 0) {
		if (mag < 10) {
			goShot = true;
		}
		if (mag >= 10) {
			if (_isSlow == true) {
				roadingTime = 150;
				goShot = false;
				mag = 0;
			}
			else {
				roadingTime = 50;
				goShot = false;
				mag = 0;
			}
		}
	}
	if (coolTime > 0) {
		coolTime--;
	}

	roadingTime--;



	BulletManager::GetInstance()->SetSpeed(speed_);
}

/// 描画を行う
void BomFire::Draw(DirectXCommon* dxCommon) {
	Object3d::PreDraw(dxCommon->GetCommandList());
	Object3d::PostDraw();
}

/// リセットを行う
void BomFire::Reset() {

}

// 発射を行う
void BomFire::Shot(Transform& shooter, Transform& reticle, uint32_t team) {

	if (coolTime <= 0 && goShot == true) {
		//弾を生成し、初期化
		std::unique_ptr<FireBottle> newBullet = std::make_unique<FireBottle>();
		Vector3 startPos, reticleVec, moveVec, velo;
		float veloLen;
		startPos = Affin::GetWorldTrans(shooter.matWorld); // 発射座標
		startPos.y += 1.0f;
		reticleVec = Affin::GetWorldTrans(reticle.matWorld);	// レティクルの3D座標
		velo = reticleVec - startPos;
		veloLen = velo.length();
		velo.nomalize();
		moveVec = velo * speed_;
		moveVec.nomalize();
		newBullet->Initialize(model_, startPos + velo, moveVec, team);
		newBullet->SetDeathTime(600);
		newBullet->SetLength(veloLen);

		//弾を登録
		BulletManager::GetInstance()->AddBullet(std::move(newBullet));
		mag++;

		//クールタイムをリセット
		if (team == PLAYER) {
			coolTime = 120;
		}if (team == ENEMY) {
			if (_isSlow == true) {
				coolTime = 48 * 5;
			}
			else {
				coolTime = 24 * 5;
			}
		}
	}
}

FireBottle::FireBottle()
{

}

FireBottle::~FireBottle() {
	CollisionManager::GetInstance()->RemoveCollider(sphere);
	delete sphere;
	delete bottleObj_;
}
void FireBottle::Initialize(Model* model, const Vector3& position, Vector3 move, uint32_t team)
{
	//NULLチェック
	assert(model);
	team_ = team;
	moveVec = move;

	bottleObj_ = Object3d::Create();
	bottleObj_->SetModel(model);

	bottleObj_->wtf.scale = Vector3(0.5f, 0.5f, 0.5f);
	bottleObj_->wtf.position = position;
	deathCount = 0;
	timeCount = 0;
	isDead = false;
	if (team_ == PLAYER) {
		bottleObj_->SetColor({ 0,1,1,1 }); // カラー?RGB の順番
	}if (team_ == ENEMY) {
		bottleObj_->SetColor({ 1,1,0,1 });
	}

	//当たり判定用
	sphere = new SphereCollider;
	CollisionManager::GetInstance()->AddCollider(sphere);
	spherePos = Affin::GetWorldTrans(bottleObj_->wtf.matWorld);
	sphere->SetObject3d(bottleObj_);
	//sphere->SetBasisPos(&spherePos[i]);
	sphere->SetRadius(bottleObj_->wtf.scale.x);
	sphere->Update();

	if (team_ == PLAYER) { // 自機弾
		sphere->SetAttribute(COLLISION_ATTR_PLAYERBULLETS);
	}
	else if (team_ == ENEMY) { // 敵弾
		sphere->SetAttribute(COLLISION_ATTR_ENEMIEBULLETS);
	}
	else {
		sphere->SetAttribute(COLLISION_ATTR_UNKNOWN);
	}


	////test
	//coliderPosTest_ = Object3d::Create();
	//coliderPosTest_->SetModel(model);
	//coliderPosTest_->wtf.position = (sphere->center);
	//coliderPosTest_->wtf.scale = Vector3(sphere->GetRadius(), sphere->GetRadius(), sphere->GetRadius());
	//coliderPosTest_->wtf.rotation = (Vector3{ 0,0,0 });
	//coliderPosTest_->Update();
}

void FireBottle::Update(float speed)
{
	if (speed) {

	}
	timeCount++;
	if (isExplosion) {
		deathCount++;
	}
	if (deathCount >= DEATH_TIME_BOTTLE) {
		Dead();
	}
	if (isExplosion) {
		bottleObj_->wtf.position.y = 0.0f;
	}
	else {
		// Y速度を計算(鉛直投げ上げ)
		bottleYSpeed = 2.5f - 9.8f * (static_cast<float>(timeCount) / 120.0f);
		bottleObj_->wtf.position.x += (moveVec.x * (vecLength / 70.0f));
		bottleObj_->wtf.position.y += (bottleYSpeed);
		bottleObj_->wtf.position.z += (moveVec.z * (vecLength / 70.0f));
	}

	//行列の再計算
	bottleObj_->Update();

	if (sphere->GetIsHit() == true) {

		if (sphere->GetCollisionInfo().collider_->GetAttribute() == COLLISION_ATTR_ENEMIES && team_ == PLAYER) {
			//isDead = true;
			isExplosion = true;
			sphere->SetAttribute(COLLISION_ATTR_PLAYERFIRE);
		}
		if (sphere->GetCollisionInfo().collider_->GetAttribute() == COLLISION_ATTR_PLAYER && team_ == ENEMY) {
			//isDead = true;
			isExplosion = true;
			sphere->SetAttribute(COLLISION_ATTR_ENEMIESFIRE);
		}
	}
	if (bottleObj_->wtf.position.y <= 0) {
		if (team_ == PLAYER) {
			//isDead = true;
			isExplosion = true;
			sphere->SetAttribute(COLLISION_ATTR_PLAYERFIRE);
		}
		if (team_ == ENEMY) {
			//isDead = true;
			isExplosion = true;
			sphere->SetAttribute(COLLISION_ATTR_ENEMIESFIRE);
		}
	}
	if (isExplosion) {
		bottleObj_->wtf.scale = Vector3(0.5f, 0.5f, 0.5f);
		sphere->SetRadius(5.0f);
	}
	else {
		bottleObj_->wtf.scale = Vector3(0.05f, 0.05f, 0.05f);
		sphere->SetRadius(0.5f);
	}
	bottleObj_->SetColor(Vector4(1.0f, 0.0f, 0.0f,0.8f));
	sphere->Update();

	//ImGui::Begin("bullet");
	//ImGui::SetWindowPos({ 600,50 });
	//ImGui::SetWindowSize({500.0f,200.0f});
	//ImGui::InputFloat4("color", &bulletObj_->color_.x);
	//ImGui::End();
}

void FireBottle::DeadUpdate() {
	if (isDead == true) {
		CollisionManager::GetInstance()->RemoveCollider(sphere);
		//delete sphere;
	}
}

void FireBottle::Draw()
{
	//coliderPosTest_->Draw();
	//モデルの描画
	bottleObj_->Draw();
}

void FireBottle::OnColision() {
	//isDead = true;
	isExplosion = true;
}

bool FireBottle::IsDead()
{
	return isDead;
}
