/**
 * @file Boss.cpp
 * @brief
 */
#include "Boss.h"

Boss::Boss() {

}
Boss::~Boss() {
	delete model_;
	delete modelCol_;
	delete weapon_;
	delete rayHit;
	for (uint32_t i = 0; i < SPHERE_COLLISION_NUM; i++) {
		CollisionManager::GetInstance()->RemoveCollider(sphere[i]);
		delete sphere[i];
		delete colliderPosTest_[i];
	}
	CollisionManager::GetInstance()->RemoveCollider(ray);
	delete ray;
	delete object_;
	delete reticle;
}

///
void Boss::Initialize() {
	isBlocked = false;
	isFound = false;
	isFire = false;
	isDead = false;
	nowTitle = false;
	model_ = Model::LoadFromOBJ("REX");
	modelCol_ = Model::LoadFromOBJ("sphere");

	bossFbxO_ = std::make_unique<FBXObject3d>();
	bossFbxO_->Initialize();
	bossFbxO_->SetModel(bossFbxM_);
	bossFbxO_->SetPosition({ 0,0,0 });
	bossFbxO_->SetScale({ 0.8f,0.8f,0.8f });
	bossFbxO_->PlayAnimation(0);
	bossFbxO_->AnimIsRotateChange(false);

	object_ = Object3d::Create();
	object_->SetModel(model_);
	object_->Initialize();
	object_->transForm.scale = Vector3(0.3f, 0.3f, 0.3f);

	reticle = Object3d::Create();
	reticle->SetModel(model_);
	reticle->Initialize();

	if (useWeapon_ == WP_SHOTGUN) {
		weapon_ = new Shotgun();
	}
	else if (useWeapon_ == WP_ASSAULT) {
		weapon_ = new Assault();
	}
	else if (useWeapon_ == WP_BOMFIRE)
	{
		weapon_ = new BomFire();
	}
	weapon_->Initialize();

	patPreset_.pos_ = object_->transForm.position;
	patPreset_.velocityMinMax = { -0.5,0.5 };
	patPreset_.scale = 0.5f;
	patPreset_.volume = 10;
	patPreset_.color = { 1,0,0,1 };
	onPatTime_ = 0;
	onPat_ = false;

	manager_ = std::make_unique<BossManager>();
	manager_->SetBoss(this);

	//当たり判定用
	SPHERE_COLLISION_NUM = 1;
	sphere.resize(SPHERE_COLLISION_NUM);
	spherePos.resize(SPHERE_COLLISION_NUM);
	//FbxO_.get()->isBonesWorldMatCalc = true;	// ボーンの行列を取得するか
	colliderPosTest_.resize(SPHERE_COLLISION_NUM);

	//rayvec = Affin::GetWorldTrans(reticle->transForm.matWorld) - Affin::GetWorldTrans(object_->transForm.matWorld);
	rayvec = -(Affin::GetWorldTrans(object_->transForm.matWorld) - Affin::GetWorldTrans(reticle->transForm.matWorld));

	for (uint32_t i = 0; i < SPHERE_COLLISION_NUM; i++) {
		sphere[i] = new SphereCollider;
		CollisionManager::GetInstance()->AddCollider(sphere[i]);
		spherePos[i] = Affin::GetWorldTrans(object_->transForm.matWorld);
		sphere[i]->SetObject3d(object_);
		sphere[i]->SetBasisPos(&spherePos[i]);
		sphere[i]->SetRadius(3.0f);
		sphere[i]->Update();
		sphere[i]->SetAttribute(COLLISION_ATTR_ENEMIES);
		//test
		colliderPosTest_[i] = Object3d::Create();
		colliderPosTest_[i]->SetModel(modelCol_);
		colliderPosTest_[i]->transForm.position = rayvec;
		colliderPosTest_[i]->transForm.scale = Vector3{ sphere[i]->GetRadius(),sphere[i]->GetRadius() ,sphere[i]->GetRadius() };
		colliderPosTest_[i]->transForm.rotation = { 0,0,0 };
		colliderPosTest_[i]->Update();
	}
	ray = new RayCollider;

	ray->SetStart(Affin::GetWorldTrans(object_->transForm.matWorld));
	ray->SetDir(rayvec);
	ray->SetObject3d(object_);
	CollisionManager::GetInstance()->AddCollider(ray);
	rayHit = new RaycastHit;
	hp = 10;
}

///
void Boss::Update(Input* input, bool isTitle) {
	object_->transForm.scale = Vector3(0.5f, 0.5f, 0.5f);
	nowTitle = false;
	nowTitle = !isTitle;
	/*if (Input::get_instance().KeyboardPush(DIK_1)) {
		stateNum_ = 0;
	}
	if (Input::get_instance().KeyboardPush(DIK_2)) {
		stateNum_ = 1;
	}
	if (Input::get_instance().KeyboardPush(DIK_3)) {
		stateNum_ = 2;
	}*/

	manager_->Update(stateNum_);

	HitMyColor();
	object_->Update();
	reticle->Update();
	bossFbxO_->SetPosition(object_->transForm.position);
	bossFbxO_->SetRotate(object_->transForm.rotation);
	bossFbxO_->Update();


	if (isFire == true && isDead == false) {
		//bossFbxO_->PlayAnimation(4);
		//bossFbxO_->AnimIsRotateChange(true);
		//isFireOld = true;
		/*if (bossFbxO_->GetEndTime() == bossFbxO_->GetCurrentTimer()) {
			weapon_->Shot(object_->transForm, reticle->transForm, Team::ENEMY);
		}*/
		stateNum_ = 2;
	}
	else {
		stateNum_ = 0;
	}
	if (isFireOld == true && isFire == false && isDead == false && bossFbxO_->GetEndTime() == bossFbxO_->GetCurrentTimer()) {
		/*bossFbxO_->AnimIsRotateChange(true);
		bossFbxO_->PlayAnimation(4);*/
		isFireOld = false;
	}
	weapon_->Update(input);

	FrontFace();
	ColliderUpdate();

}

///
void Boss::Draw(DirectXCommon* dxCommon) {

	if (isDead == false) {
		bossFbxO_->Draw(dxCommon->GetCommandList());
		Object3d::PreDraw(dxCommon->GetCommandList());
		//object_->Draw();
		if (nowTitle) {
			//reticle->Draw();
		}
		for (uint32_t i = 0; i < SPHERE_COLLISION_NUM; i++) {
			//colliderPosTest_[i]->Draw();
		}
		Object3d::PostDraw();
		if (nowTitle) {
			weapon_->Draw(dxCommon);
		}
	}
}

/// リセットを行う
void Boss::Reset() {

}

/// 武器の番号セット
void Boss::SetWeaponNum(uint32_t WeaponNum)
{
	useWeapon_ = WeaponNum;
}

/// <summary>
/// 撃つ方向に向かせる
/// </summary>
void Boss::FrontFace() {
	Vector3 faceAngle = { 0,0,0 };
	faceAngle.y = (float)atan2(reticle->transForm.position.x - object_->transForm.position.x, reticle->transForm.position.z - object_->transForm.position.z);
	if (isFire == true) {
		frontVec_ = faceAngle;
	}if (isFire == false) {
		frontVec_ = restRotate_;
	}
	object_->transForm.rotation = frontVec_;
	bossFbxO_->transform_.rotation = frontVec_;
}

void Boss::ColliderUpdate() {

	isBlocked = false;
	isFound = false;
	isFire = false;

	rayvec = -(Affin::GetWorldTrans(object_->transForm.matWorld) - Affin::GetWorldTrans(reticle->transForm.matWorld));
	ray->SetDir(Affin::GetWorldTrans(reticle->transForm.matWorld));

	for (uint32_t i = 0; i < SPHERE_COLLISION_NUM; i++) {
		if (sphere[i]->GetIsHit() == true && sphere[i]->GetCollisionInfo().collider_->GetAttribute() == COLLISION_ATTR_PLAYERBULLETS) {
			OnCollision();
		}
	}

	for (uint32_t i = 0; i < SPHERE_COLLISION_NUM; i++) {
		spherePos[i] = object_->transForm.position;
		colliderPosTest_[i]->transForm.position = ray->GetDir();
		sphere[i]->Update();
		colliderPosTest_[i]->Update();
	}
	// クエリーコールバッククラス
	{
		class BossQueryCallback :public QueryCallback
		{
		public:
			BossQueryCallback(Sphere* sphere) :sphereQ(sphere) {};
			// 衝突時コールバック
			bool OnQueryHit(const QueryHit& info) {
				// ワールドの上方向
				const Vector3 up = { 0,1,0 };
				// 排斥方向			
				Vector3 rejectDir = info.reject;
				rejectDir.nomalize();
				// 上方向と排斥方向の角度差のコサイン値
				float cos = rejectDir.dot(up);

				// 地面判定しきい値
				const float threshold = cosf(Affin::radConvert(NUM_THIRTY));
				// 角度差によって天井または地面と判定される場合を除いて
				if (-threshold < cos && cos < threshold) {
					// 球を排斥 （押し出す）
					sphereQ->center += info.reject;
					move += info.reject;
					colider_ = info.coloder;
				}
				return true;
			}

			// クエリーに使用する球
			Sphere* sphereQ = nullptr;
			// 排斥による移動量
			Vector3 move = {};
			// 衝突相手のコライダー
			BaseCollider* colider_ = nullptr;
		};

		//クエリーコールバックの関数オブジェクト
		for (uint32_t i = NONE; i < SPHERE_COLLISION_NUM; i++) {
			BossQueryCallback callback(sphere[i]);
			CollisionManager::GetInstance()->QuerySphere(*sphere[i], &callback, COLLISION_ATTR_BARRIEROBJECT);
			object_->transForm.position.x += callback.move.x;
			object_->transForm.position.y += callback.move.y;
			object_->transForm.position.z += callback.move.z;

			object_->UpdateMatrix();
			sphere[i]->Update();
		}
	}
	// レイ関係
	{
		ray->Update();
		isFound = false;
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
	}
	if (isDead) {
		for (uint32_t i = 0; i < SPHERE_COLLISION_NUM; i++) {
			CollisionManager::GetInstance()->RemoveCollider(sphere[i]);
			//delete sphere[i];
		}
		CollisionManager::GetInstance()->RemoveCollider(ray);
		if (onPat_) {
			onPatTime_--;
			ObjParticleManager::GetInstance()->SetAnyExp(patPreset_);
		}
	}
	if (onPatTime_ < 1) {
		onPat_ = false;
	}
}

void Boss::OnCollision()
{
	hp -= 1;
	isHitEffect = true;
	ObjParticleManager::GetInstance()->SetAnyExp(patPreset_);
	if (hp < 1) {
		isDead = true;
		onPat_ = true;
		onPatTime_ = 5;
	}
}
void Boss::HitMyColor()
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
		object_->SetColor({ 0.8f,0.8f,0.8f,1.0f });
	}
}