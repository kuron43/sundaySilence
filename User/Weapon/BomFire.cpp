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
void BomFire::Update(Input* input) {
	if (input) {

	}
	if (_isSlow == true) {
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
		for (int i = 0; i < 3; i++) {
			std::unique_ptr<FireBottle> newBullet = std::make_unique<FireBottle>();
			Vector3 startPos, reticleVec, moveVec, velo;
			float veloLen;
			startPos = Affin::GetWorldTrans(shooter.matWorld); // 発射座標
			startPos.y += 1.0f;
			reticleVec = Affin::GetWorldTrans(reticle.matWorld);	// レティクルの3D座標
			velo = reticleVec - startPos;
			veloLen = velo.length();
			velo.nomalize();
			if (i == 1) {
				velo = Affin::VecMat(velo, Affin::matRotateY(Affin::radConvert(30.0f)));
			}if (i == 2) {
				velo = Affin::VecMat(velo, Affin::matRotateY(Affin::radConvert(-30.0f)));
			}
			moveVec = velo * speed_;
			moveVec.nomalize();
			newBullet->Initialize(model_, startPos + velo, moveVec, team);
			newBullet->SetDeathTime(600);
			newBullet->SetLength(veloLen);

			//弾を登録
			BulletManager::GetInstance()->AddBullet(std::move(newBullet));
		}
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

	bottleObj_->transForm.scale = Vector3(0.5f, 0.5f, 0.5f);
	bottleObj_->transForm.position = position;
	deathCount = 0;
	timeCount = 0;
	isDead = false;
	if (team_ == PLAYER) {
		bottleObj_->SetColor({ 0,1,1,1 }); // カラー?RGB の順番
	}if (team_ == ENEMY) {
		bottleObj_->SetColor({ 1,0,0,1 });
	}

	//当たり判定用
	sphere = new SphereCollider;
	CollisionManager::GetInstance()->AddCollider(sphere);
	spherePos = Affin::GetWorldTrans(bottleObj_->transForm.matWorld);
	sphere->SetObject3d(bottleObj_);
	//sphere->SetBasisPos(&spherePos[i]);
	sphere->SetRadius(bottleObj_->transForm.scale.x);
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
		bottleObj_->transForm.position.y = 0.0f;
	}
	else {
		// Y速度を計算(鉛直投げ上げ)
		bottleYSpeed = 2.5f - 9.8f * (static_cast<float>(timeCount) / 120.0f);
		bottleObj_->transForm.position.x += (moveVec.x * (vecLength / 70.0f));
		bottleObj_->transForm.position.y += (bottleYSpeed);
		bottleObj_->transForm.position.z += (moveVec.z * (vecLength / 70.0f));
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
	if (bottleObj_->transForm.position.y <= 0) {
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
		bottleObj_->transForm.scale = Vector3(0.5f, 0.5f, 0.5f);
		sphere->SetRadius(5.0f);
		ObjParticleManager::GetInstance()->SetAnyExp(bottleObj_->transForm.position,
			{ -0.2f,0.2f }, 2, 0.1f,{1,0,0,1});
	}
	else {
		bottleObj_->transForm.scale = Vector3(0.05f, 0.05f, 0.05f);
		sphere->SetRadius(0.5f);
	}
	bottleObj_->SetColor(Vector4(1.0f, 0.0f, 0.0f,1.0f));
	sphere->Update();

////IMGUI
	//Vector4 col = bulletObj_->GetColor();
	//ImGui::Begin("bullet");
	//ImGui::InputFloat4("color", &col.x);
	//ImGui::End();
	//bulletObj_->SetColor(col);

}

void FireBottle::DeadUpdate() {
	if (isDead == true) {
		CollisionManager::GetInstance()->RemoveCollider(sphere);
		//delete sphere;
	}
}

void FireBottle::Draw()
{
	//colliderPosTest_->Draw();
	//モデルの描画
	bottleObj_->Draw();
}

void FireBottle::OnCollision() {
	//isDead = true;
	isExplosion = true;
}

bool FireBottle::IsDead()
{
	return isDead;
}
