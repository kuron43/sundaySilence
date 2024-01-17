/**
 * @file Player.cpp
 * @brief
 */
#include "Player.h"
#include "Weaponlist.h"

Player::Player() {

}
Player::~Player() {
	delete model_;
	delete reticleMD_;
	delete reticleXMD_;
	delete pointDash_;
	delete weapon_[0];
	for (uint32_t i = 0; i < SPHERE_COLISSION_NUM; i++) {
		CollisionManager::GetInstance()->RemoveCollider(sphere[i]);
		delete sphere[i];
	}
}

///
void Player::Initialize() {
	model_ = Model::LoadFromOBJ("player");
	reticleMD_ = Model::LoadFromOBJ("cursor");
	reticleXMD_ = Model::LoadFromOBJ("cursolX");

	object_ = Object3d::Create();
	object_->SetModel(model_);
	object_->Initialize();

	reticle = Object3d::Create();
	reticle->SetModel(reticleMD_);
	reticle->Initialize();

	weapon_[WP_ASSAULT] = new Assault();
	weapon_[WP_SHOTGUN] = new Shotgun();
	//weapon_[WP_SHOTGUN] = new BomFire();
	weapon_[WP_ASSAULT]->Initialize();
	weapon_[WP_SHOTGUN]->Initialize();
	useWeapon_ = WP_SHOTGUN;

	pointDash_ = new PointDash();
	pointDash_->Initialize();
	pointDash_->points.resize(pointDash_->MAX_POINTNUM);

	for (uint32_t i = 0; i < 4; i++)
	{
		phantom_[i] = Object3d::Create();
	}
	//phantomAlpha_[0] = 1.0f;
	for (uint32_t i = 0; i < 4; i++)
	{
		phantomAlpha_[i] = 0.2f;
	}
	for (uint32_t i = 0; i < 4; i++)
	{
		phantom_[i]->SetModel(model_);
		phantom_[i]->Initialize();
		phantom_[i]->SetColor(Vector4(0.8f, 0.8f, 0.8f, phantomAlpha_[i]));
	}

	hp_ = MAX_HP;

	//当たり判定用
	coolTimeFB_ = 0;
	sphere.resize(SPHERE_COLISSION_NUM);
	spherePos.resize(SPHERE_COLISSION_NUM);
	//FbxO_.get()->isBonesWorldMatCalc = true;	// ボーンの行列を取得するか
	coliderPosTest_.resize(SPHERE_COLISSION_NUM);

	for (uint32_t i = 0; i < SPHERE_COLISSION_NUM; i++) {
		sphere[i] = new SphereCollider;
		CollisionManager::GetInstance()->AddCollider(sphere[i]);
		spherePos[i] = Affin::GetWorldTrans(object_->wtf.matWorld);
		sphere[i]->SetObject3d(object_);
		sphere[i]->SetBasisPos(&spherePos[i]);
		sphere[i]->SetRadius(1.0f);
		sphere[i]->Update();
		sphere[i]->SetAttribute(COLLISION_ATTR_PLAYER);
		//test
		coliderPosTest_[i] = Object3d::Create();
		coliderPosTest_[i]->SetModel(Model::LoadFromOBJ("sphere"));
		coliderPosTest_[i]->wtf.position = (sphere[i]->center);
		coliderPosTest_[i]->wtf.scale = Vector3(sphere[i]->GetRadius(), sphere[i]->GetRadius(), sphere[i]->GetRadius());
		coliderPosTest_[i]->wtf.rotation = (Vector3{ 0,0,0 });
		coliderPosTest_[i]->Update();
	}

}

///
void Player::Update(Input* input, bool isTitle) {
	nowTitle = isTitle;
	FaceAngleUpdate();
	if (pointDash_->isActive == false) {
		Move(input);
	}
	Vector2 mousepos = input->GetMousePosition();
	object_->wtf.position.y = NONE;
	reticle->wtf.position += { mousepos.x* mouseSensitivity_, NONE, mousepos.y* mouseSensitivity_ };
	reticle->Update();
	// 武器の切り替え処理
	if (input->KeyboardTrigger(DIK_E)) {
		if (useWeapon_ == WP_SHOTGUN) {
			useWeapon_ = WP_ASSAULT;
		}
		else if (useWeapon_ == WP_ASSAULT) {
			useWeapon_ = WP_SHOTGUN;
		}
		else {

		}
	}
	// 弾発射
	if (input->MouseButtonPush(0) && !isTitle && _isSlow == false) {
		weapon_[useWeapon_]->Shot(object_->wtf, reticle->wtf, PLAYER);
		isOnFire = true;
	}
	else {
		isOnFire = false;
	}
	for (uint32_t i = 0; i < 2; i++) {
		weapon_[i]->Update(input, _isSlow);
	}

	if (_isSlow == true) {
		if (pointDash_->PointRayUpdate(Affin::GetWorldTrans(object_->wtf.matWorld), Affin::GetWorldTrans(reticle->wtf.matWorld))) {
			if (input->MouseButtonTrigger(LEFT_MOUSE) && !nowTitle) {
				pointDash_->SetPoint(reticle->wtf.position, input);
				nowSetPoint = true;
			}
			reticle->SetModel(reticleMD_);
			reticle->wtf.rotation.y += 0.05f;
		}
		else {
			reticle->SetModel(reticleXMD_);
			reticle->wtf.rotation.y = 0;
		}
	}
	else {
		reticle->SetModel(reticleMD_);
		reticle->wtf.rotation.y = 0;
	}
	//object_->camera_->SetFocalLengs(pointDash_->F_lengs);

	if (!nowTitle && pointDash_->isActive == true) {
		pointDash_->GoToPoint();
		object_->wtf.position = pointDash_->resultVec;
	}


	PhantomUpdate();
	ColisionUpdate();
	HitMyColor();
	object_->Update();
	Vector4 skaliCol = object_->GetColor();
	ImGui::Begin("player");
	ImGui::Text("window W :%d", WinApp::window_width);
	ImGui::Text("window H :%d", WinApp::window_height);
	ImGui::Text("Palams");
	ImGui::Text("ph:%d", countPH_);
	ImGui::InputFloat3("Position", &object_->wtf.position.x);
	ImGui::Text("PointDash");
	ImGui::InputFloat3("Vec", &pointDash_->resultVec.x);
	ImGui::InputFloat3("Vec", &pointDash_->resultVec.x);
	ImGui::InputFloat4("Col", &skaliCol.x);
	ImGui::InputFloat("spe :%f", &pointDash_->easeSpeed);
	ImGui::End();

}

///
void Player::Draw(DirectXCommon* dxCommon) {
	pointDash_->Draw(dxCommon);
	Object3d::PreDraw(dxCommon->GetCommandList());
	for (uint32_t i = 0; i < 4; i++)
	{
		if (isPhantom_) {
			phantom_[i]->Draw();
		}
	}
	object_->Draw();
	if (!nowTitle) {
		reticle->Draw();
	}
	for (uint32_t i = NONE; i < SPHERE_COLISSION_NUM; i++) {
		//coliderPosTest_[i]->Draw();
	}
	Object3d::PostDraw();
	/*if (!nowTitle) {
		weapon_[useWeapon_]->Draw(dxCommon);
	}*/
}

/// リセットを行う
void Player::Reset() {

	hp_ = MAX_HP;
	hit_ = NONE;
	isDeath_ = false;
	_isSlow = false;
	object_->wtf.Initialize();
	reticle->wtf.Initialize();
	object_->SetColor({ 0.8f,0.8f,0.8f,1.0f });
	pointDash_->Reset();
	isHitEffect = false;
	hitTime_ = NONE;

}

/// 武器の番号セット
void Player::SetWeaponNum(uint32_t WeaponNum)
{
	useWeapon_ = WeaponNum;
}

void Player::Move(Input* input) {

	//-----行動処理-----//
	//速度を0にする
	velocity_.InIt();
	Vector3 speed;
	speed.InIt();

	//キー入力があったら
	if (input->KeyboardPush(DIK_W) ||
		input->KeyboardPush(DIK_A) ||
		input->KeyboardPush(DIK_S) ||
		input->KeyboardPush(DIK_D)) {

		if (input->KeyboardPush(DIK_W)) {
			speed.z += kMoveSpeed_;
		}
		if (input->KeyboardPush(DIK_S)) {
			speed.z += -kMoveSpeed_;
		}
		if (input->KeyboardPush(DIK_A)) {
			speed.x += -kMoveSpeed_;
		}
		if (input->KeyboardPush(DIK_D)) {
			speed.x += kMoveSpeed_;
		}
	}
	//////////////////////////////////
	if (input->MouseButtonPush(RIGHT_MOUSE)) {
		_isSlow = true;
	}
	else {
		_isSlow = false;
	}
	if (input->MouseButtonRelease(RIGHT_MOUSE)) {
		nowSetPoint = false;
		pointDash_->MakeMoveVec(Affin::GetWorldTrans(object_->wtf.matWorld));
	}

	if (_isSlow == true) {
		velocity_ = speed * _SlowSpeed;
	}
	else {
		velocity_ = speed;
	}

	if (wallHit == true) {
		wallHit = false;
		velocity_ = -oldVelocity_;
	}

	object_->wtf.position += velocity_;
	oldVelocity_ = velocity_;

}

void Player::FaceAngleUpdate()
{
	Vector3 faceAngle;
	faceAngle.InIt();
	faceAngle_.y = (float)atan2(reticle->wtf.position.x - object_->wtf.position.x, reticle->wtf.position.z - object_->wtf.position.z);
	faceAngle = faceAngle_;

	object_->wtf.rotation = faceAngle;
}

void Player::HitMyColor()
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

void Player::ColisionUpdate() {
	// コライダーのアップデート
	object_->UpdateMatrix();

	for (uint32_t i = NONE; i < SPHERE_COLISSION_NUM; i++) {
		if (sphere[i]->GetIsHit() == true) {
			if (sphere[i]->GetCollisionInfo().collider_->GetAttribute() == COLLISION_ATTR_ENEMIEBULLETS) {
				OnColision(true);
			}
			if (sphere[i]->GetCollisionInfo().collider_->GetAttribute() == COLLISION_ATTR_ENEMIESFIRE) {
				if (coolTimeFB_ <= 0) {
					OnColision(false);
				}
			}
		}
	}
	if (coolTimeFB_ > 0) {
		coolTimeFB_--;
	}

	for (uint32_t i = NONE; i < SPHERE_COLISSION_NUM; i++) {
		spherePos[i] = object_->wtf.position;
		sphere[i]->Update();

		coliderPosTest_[i]->wtf.position = (sphere[i]->center);
		coliderPosTest_[i]->wtf.scale = Vector3(sphere[i]->GetRadius(), sphere[i]->GetRadius(), sphere[i]->GetRadius());
		coliderPosTest_[i]->wtf.rotation.InIt();
		coliderPosTest_[i]->Update();
	}
	// クエリーコールバッククラス
	{
		class PlayerQueryCallback :public QueryCallback
		{
		public:
			PlayerQueryCallback(Sphere* sphere) :sphereQ(sphere) {};
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
				const float threshold = cosf(Affin::radConvert(30.0f));
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
		for (uint32_t i = NONE; i < SPHERE_COLISSION_NUM; i++) {
			PlayerQueryCallback callback(sphere[i]);
			CollisionManager::GetInstance()->QuerySphere(*sphere[i], &callback, COLLISION_ATTR_BARRIEROBJECT);
			object_->wtf.position.x += callback.move.x;
			object_->wtf.position.y += callback.move.y;
			object_->wtf.position.z += callback.move.z;

			object_->UpdateMatrix();
			sphere[i]->Update();
		}
	}
}

void Player::OnColision(bool bullet)
{
	if (bullet) {
		hp_--;
		hit_++;
		isHitEffect = true;
	}
	if (bullet == false) {
		hp_ -= 2;
		coolTimeFB_ = 30;
		hit_++;
		isHitEffect = true;
	}
	if (hp_ <= NONE) {
		isDeath_ = true;
	}
}

void Player::PhantomUpdate()
{
	isPhantom_ = false;
	isPhantom_ = pointDash_->isActive;
	if (isPhantom_)
	{
		countPH_++;
		if (countPH_ == 1) {
			phantom_[0]->wtf = object_->wtf;
		}
		if (countPH_ == 3) {
			phantom_[1]->wtf = object_->wtf;
		}
		if (countPH_ == 6) {
			phantom_[2]->wtf = object_->wtf;
		}
		if (countPH_ == 9) {
			phantom_[3]->wtf = object_->wtf;
		}
		if (countPH_ > 10) {
			countPH_ = 0;
		}
	}
	else {
		for (uint32_t i = 0; i < 4; i++) {
			phantom_[i]->wtf = object_->wtf;
		}
	}

	for (uint32_t i = 0; i < 4; i++) {
		phantom_[i]->Update();
	}
}
