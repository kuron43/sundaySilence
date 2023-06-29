#include "Player.h"
#include "Assault.h"

Player::Player() {

}
Player::~Player() {
	delete model_;
}

///
void Player::Initialize() {
	model_ = Model::LoadFromOBJ("cube");

	object_ = Object3d::Create();
	object_->SetModel(model_);
	object_->Initialize();

	reticle = Object3d::Create();
	reticle->SetModel(model_);
	reticle->Initialize();
	weapon_[0] = new Assault();
	weapon_[0]->Initialize();

}

///
void Player::Update(Input* input, bool isTitle) {
	nowTitle = isTitle;
	Move(input);
	object_->Update();
	Vector2 mousepos = input->GetMousePosition();
	reticle->wtf.position = { mousepos.x * mouseSensitivity_,0,mousepos.y * mouseSensitivity_ };
	reticle->Update();
	if (input->MouseButtonPush(0)) {
		weapon_[0]->Shot(object_->wtf, reticle->wtf);
	}
	weapon_[0]->Update(input, isSlow);
}

///
void Player::Draw(DirectXCommon* dxCommon) {
	Object3d::PreDraw(dxCommon->GetCommandList());
	object_->Draw();
	if (!nowTitle) {
		reticle->Draw();
	}
	Object3d::PostDraw();
	if (!nowTitle) {
		weapon_[0]->Draw(dxCommon);
	}
}

/// リセットを行う
void Player::Reset() {

}

void Player::Move(Input* input) {

	//-----行動処理-----//
	//速度を0にする
	velocity_ = { 0 , 0 , 0 };

	//キー入力があったら
	if (input->KeyboardPush(DIK_W) ||
		input->KeyboardPush(DIK_A) ||
		input->KeyboardPush(DIK_S) ||
		input->KeyboardPush(DIK_D))
	{
		if (isRun_ == false) {
			isRun_ = true;
		}

		//Z軸方向にの速度を入れる
		velocity_ = { 0 , 0 , kMoveSpeed_ };

		//W,Dを押していたら
		if (input->KeyboardPush(DIK_W) && input->KeyboardPush(DIK_D))
		{

			//45度方向に向くように回転させる
			if (faceAngle_.y != Affin::radConvert(45))
			{
				if (faceAngle_.y >= Affin::radConvert(45) &&
					faceAngle_.y <= Affin::radConvert(225))
				{

					faceAngle_.y -= kTurnSpeed_;

					if (faceAngle_.y <= Affin::radConvert(45) ||
						faceAngle_.y >= Affin::radConvert(225))
					{
						faceAngle_.y = Affin::radConvert(45);
					}
				}
				else
				{

					faceAngle_.y += kTurnSpeed_;

					if (faceAngle_.y >= Affin::radConvert(45) &&
						faceAngle_.y <= Affin::radConvert(225))
					{
						faceAngle_.y = Affin::radConvert(45);
					}
				}
			}

		}

		//W,Aを押していたら
		else if (input->KeyboardPush(DIK_W) && input->KeyboardPush(DIK_A))
		{

			//135度方向に向くように回転させる
			if (faceAngle_.y != Affin::radConvert(315))
			{
				if (faceAngle_.y >= Affin::radConvert(125) &&
					faceAngle_.y <= Affin::radConvert(315))
				{

					faceAngle_.y += kTurnSpeed_;

					if (faceAngle_.y <= Affin::radConvert(125) ||
						faceAngle_.y >= Affin::radConvert(315))
					{
						faceAngle_.y = Affin::radConvert(315);
					}
				}
				else
				{

					faceAngle_.y -= kTurnSpeed_;

					if (faceAngle_.y >= Affin::radConvert(125) &&
						faceAngle_.y <= Affin::radConvert(315))
					{
						faceAngle_.y = Affin::radConvert(315);
					}
				}
			}

		}

		//S,Dを押していたら
		else if (input->KeyboardPush(DIK_S) && input->KeyboardPush(DIK_D))
		{

			//315度方向に向くように回転させる
			if (faceAngle_.y != Affin::radConvert(135))
			{
				if (faceAngle_.y <= Affin::radConvert(315) &&
					faceAngle_.y >= Affin::radConvert(135))
				{

					faceAngle_.y -= kTurnSpeed_;

					if (Affin::radConvert(135) >= faceAngle_.y)
					{
						faceAngle_.y = Affin::radConvert(135);
					}
				}
				else
				{

					faceAngle_.y += kTurnSpeed_;

					if (Affin::radConvert(135) <= faceAngle_.y)
					{
						faceAngle_.y = Affin::radConvert(135);
					}
				}
			}

		}

		//S,Aを押していたら
		else if (input->KeyboardPush(DIK_S) && input->KeyboardPush(DIK_A))
		{

			//225度方向に向くように回転させる
			if (faceAngle_.y != Affin::radConvert(225))
			{
				if (faceAngle_.y >= Affin::radConvert(45) &&
					faceAngle_.y <= Affin::radConvert(225))
				{

					faceAngle_.y += kTurnSpeed_;

					if (Affin::radConvert(225) <= faceAngle_.y)
					{
						faceAngle_.y = Affin::radConvert(225);
					}
				}
				else
				{

					faceAngle_.y -= kTurnSpeed_;

					if (Affin::radConvert(225) >= faceAngle_.y &&
						faceAngle_.y >= Affin::radConvert(45))
					{
						faceAngle_.y = Affin::radConvert(225);
					}

				}
			}

		}

		//Wを押していたら
		else if (input->KeyboardPush(DIK_W))
		{

			//0度方向に向くように回転させる
			if (faceAngle_.y != Affin::radConvert(0))
			{
				if (faceAngle_.y <= Affin::radConvert(180))
				{

					faceAngle_.y -= kTurnSpeed_;

					if (Affin::radConvert(0) >= faceAngle_.y)
					{
						faceAngle_.y = Affin::radConvert(0);
					}
				}
				else
				{

					faceAngle_.y += kTurnSpeed_;

					if (Affin::radConvert(360) <= faceAngle_.y)
					{
						faceAngle_.y = Affin::radConvert(0);
					}
				}
			}
		}

		//Sを押していたら
		else if (input->KeyboardPush(DIK_S))
		{

			//180度方向に向くように回転させる
			if (faceAngle_.y != Affin::radConvert(180))
			{
				if (faceAngle_.y <= Affin::radConvert(180))
				{

					faceAngle_.y += kTurnSpeed_;

					if (Affin::radConvert(180) <= faceAngle_.y)
					{
						faceAngle_.y = Affin::radConvert(180);
					}
				}
				else
				{

					faceAngle_.y -= kTurnSpeed_;

					if (Affin::radConvert(180) >= faceAngle_.y)
					{
						faceAngle_.y = Affin::radConvert(180);
					}
				}
			}
		}

		//Dを押していたら
		else if (input->KeyboardPush(DIK_D))
		{

			//90度方向に向くように回転させる
			if (faceAngle_.y != Affin::radConvert(90))
			{
				if (faceAngle_.y != Affin::radConvert(90))
				{
					if (faceAngle_.y >= Affin::radConvert(90) &&
						faceAngle_.y <= Affin::radConvert(270))
					{
						faceAngle_.y -= kTurnSpeed_;

						if (faceAngle_.y <= Affin::radConvert(90) ||
							Affin::radConvert(270) <= faceAngle_.y)
						{
							faceAngle_.y = Affin::radConvert(90);
						}

					}
					else
					{
						faceAngle_.y += kTurnSpeed_;

						if (faceAngle_.y >= Affin::radConvert(90) &&
							faceAngle_.y <= Affin::radConvert(270))
						{
							faceAngle_.y = Affin::radConvert(90);
						}
					}
				}
			}
		}

		//Aを押していたら
		else if (input->KeyboardPush(DIK_A))
		{
			//270度方向に向くように回転させる
			if (faceAngle_.y != Affin::radConvert(270))
			{
				if (faceAngle_.y >= Affin::radConvert(90) &&
					faceAngle_.y <= Affin::radConvert(270))
				{
					faceAngle_.y += kTurnSpeed_;

					if (faceAngle_.y <= Affin::radConvert(90) ||
						Affin::radConvert(270) <= faceAngle_.y)
					{
						faceAngle_.y = Affin::radConvert(270);
					}

				}
				else
				{
					faceAngle_.y -= kTurnSpeed_;

					if (faceAngle_.y >= Affin::radConvert(90) &&
						Affin::radConvert(270) >= faceAngle_.y)
					{
						faceAngle_.y = Affin::radConvert(270);
					}
				}
			}
		}

		if (Affin::radConvert(360) < faceAngle_.y)
		{
			faceAngle_.y += -Affin::radConvert(360);
		}
		if (faceAngle_.y < 0)
		{
			faceAngle_.y += Affin::radConvert(360);
		}
		object_->wtf.rotation = faceAngle_;

	}
	else
	{
		if (isRun_ == true) {
			isRun_ = false;
		}
	}


	//////////////////////////////////
	float speed = kMoveSpeed_;
	if (input->KeyboardPush(DIK_R)) {
		isSlow = true;
	}
	if (input->KeyboardPush(DIK_T)) {
		isSlow = false;
	}

	if (isSlow == true) {
		speed = speed * 0.25f;
	}
	else {
		speed = kMoveSpeed_;
	}

	velocity_ = Affin::VecMat(velocity_, object_->wtf.matWorld);
	object_->wtf.position += velocity_;

}