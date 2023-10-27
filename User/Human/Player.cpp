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
	delete pointDash_;
	delete weapon_[0];
	for (uint32_t i = 0; i < SPHERE_COLISSION_NUM; i++) {
		CollisionManager::GetInstance()->RemoveCollider(sphere[i]);
		delete sphere[i];		
	}
}

///
void Player::Initialize() {
	model_ = Model::LoadFromOBJ("prayer");
	reticleMD_ = Model::LoadFromOBJ("cursor");

	object_ = Object3d::Create();
	object_->SetModel(model_);
	object_->Initialize();

	reticle = Object3d::Create();
	reticle->SetModel(reticleMD_);
	reticle->Initialize();
	reticle->wtf.scale = Vector3(0.5f, 0.5f, 0.5f);
	weapon_[0] = new Assault();
	weapon_[0]->Initialize();

	pointDash_ = new PointDash();
	pointDash_->Initialize();
	pointDash_->points.resize(pointDash_->MAX_POINTNUM);

	//当たり判定用
	SPHERE_COLISSION_NUM = 1;
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
	if (pointDash_->isActive == false) {
		Move(input);
	}
	Vector2 mousepos = input->GetMousePosition();
	reticle->wtf.position = { mousepos.x * mouseSensitivity_,0,mousepos.y * mouseSensitivity_ };
	reticle->Update();
	if (input->MouseButtonPush(0) && !isTitle && isSlow == false) {
		weapon_[0]->Shot(object_->wtf, reticle->wtf, PLAYER);
	}
	weapon_[0]->Update(input, isSlow);

	if (pointDash_->PointRayUpdate(Affin::GetWorldTrans(object_->wtf.matWorld), Affin::GetWorldTrans(reticle->wtf.matWorld))) {
		if (input->MouseButtonTrigger(0) && !isTitle && isSlow == true) {
			pointDash_->SetPoint(reticle->wtf.position, input);
		nowSetPoint = true;
		}
	}

	if (!isTitle && pointDash_->isActive == true) {
		pointDash_->GoToPoint();
		object_->wtf.position = pointDash_->resultVec;
	}

	ColisionUpdate();

	object_->Update();

	ImGui::Begin("pointRes");
	ImGui::InputFloat3("Vec", &pointDash_->resultVec.x);
	ImGui::Text("spe :%f", pointDash_->easeSpeed);
	ImGui::End();
}

///
void Player::Draw(DirectXCommon* dxCommon) {
	Object3d::PreDraw(dxCommon->GetCommandList());
	pointDash_->Draw();
	object_->Draw();
	if (!nowTitle) {
		reticle->Draw();
	}
	for (uint32_t i = 0; i < SPHERE_COLISSION_NUM; i++) {

		//coliderPosTest_[i]->Draw();
	}
	Object3d::PostDraw();
	if (!nowTitle) {
		weapon_[0]->Draw(dxCommon);
	}
}

/// リセットを行う
void Player::Reset() {

	for (uint32_t i = 0; i < SPHERE_COLISSION_NUM; i++) {
		CollisionManager::GetInstance()->RemoveCollider(sphere[i]);
	}

}

void Player::Move(Input* input) {

	//-----行動処理-----//
	//速度を0にする
	velocity_ = { 0 , 0 , 0 };
	Vector2 vec2Velocity = { 0,0 };
	Vector3 faceAngle = { 0,0,0 };
	Vector3 speed = { 0 , 0 , 0 };

	//キー入力があったら
	if (input->KeyboardPush(DIK_W) ||
		input->KeyboardPush(DIK_A) ||
		input->KeyboardPush(DIK_S) ||
		input->KeyboardPush(DIK_D)) {

		if (input->KeyboardPush(DIK_W)) {
			speed += Vector3(0, 0, kMoveSpeed_);
		}
		if (input->KeyboardPush(DIK_S)) {
			speed += Vector3(0, 0, -kMoveSpeed_);
		}
		if (input->KeyboardPush(DIK_A)) {
			speed += Vector3(-kMoveSpeed_, 0, 0);
		}
		if (input->KeyboardPush(DIK_D)) {
			speed += Vector3(kMoveSpeed_, 0, 0);
		}

	}

	vec2Velocity = input->Pad_X_GetLeftStickVec(Vector2(1.0f, 1.0f));
	speed += { vec2Velocity.x, 0, -vec2Velocity.y };


	//////////////////////////////////
	if (input->MouseButtonTrigger(1)) {
		isSlow = true;
	}
	if (input->MouseButtonRelease(1)) {
		isSlow = false;
		nowSetPoint = false;
		pointDash_->MakeMoveVec(Affin::GetWorldTrans(object_->wtf.matWorld));
	}

	if (isSlow == true) {
		velocity_ = speed * 0.25f;
	}
	else {
		velocity_ = speed;
	}

	if (wallHit == true) {
		wallHit = false;
		velocity_ = -oldVelocity_;
	}

	{
		faceAngle_.y = (float)atan2(object_->wtf.position.x - reticle->wtf.position.x, object_->wtf.position.z - reticle->wtf.position.z);
		faceAngle = faceAngle_;
	}

	object_->wtf.rotation = faceAngle;
	object_->wtf.position += velocity_;
	oldVelocity_ = velocity_;

}

void Player::ColisionUpdate() {
	// コライダーのアップデート
	object_->UpdateMatrix();

	for (uint32_t i = 0; i < SPHERE_COLISSION_NUM; i++) {
		if (sphere[i]->GetIsHit() == true) {
			if (sphere[i]->GetCollisionInfo().collider_->GetAttribute() == COLLISION_ATTR_BARRIEROBJECT) {
				wallHit = true;
			}
		}
	}

	for (uint32_t i = 0; i < SPHERE_COLISSION_NUM; i++) {
		spherePos[i] = object_->wtf.position;
		sphere[i]->Update();

		coliderPosTest_[i]->wtf.position = (sphere[i]->center);
		coliderPosTest_[i]->wtf.scale = Vector3(sphere[i]->GetRadius(), sphere[i]->GetRadius(), sphere[i]->GetRadius());
		coliderPosTest_[i]->wtf.rotation = (Vector3{ 0,0,0 });
		coliderPosTest_[i]->Update();
	}
	{
		// クエリーコールバッククラス
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
		for (uint32_t i = 0; i < SPHERE_COLISSION_NUM; i++) {
			PlayerQueryCallback callback(sphere[i]);
			CollisionManager::GetInstance()->QuerySphere(*sphere[i], &callback);
			object_->wtf.position.x += callback.move.x;
			object_->wtf.position.y += callback.move.y;
			object_->wtf.position.z += callback.move.z;

			object_->UpdateMatrix();
			sphere[i]->Update();
		}
	}
}

void Player::OnColision()
{

}
