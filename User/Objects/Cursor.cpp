#include "Cursor.h"
#include "imgui.h"
#include "Affin.h"

Cursor::Cursor() {

}
Cursor::~Cursor() {
	delete model_;
}

///
void Cursor::Initialize(SpriteCommon* spriteCommon) {
	model_ = Model::LoadFromOBJ("ball");

	object_ = Object3d::Create();
	object_->SetModel(model_);
	object_->Initialize();

	cursorPic_ = std::make_unique<Sprite>();
	cursorPic_->Initialize(spriteCommon, 7);
	cursorPic_->SetSize({ 16,16 });
	cameraWTF_.Initialize();
	cameraWTF_.position = object_->camera_->GetEye();
	cameraWTF_.UpdateMat();
}

///
void Cursor::Update(Input* input) {

	Vector2 mousepos = input->GetMousePosition();
	object_->wtf.position = { mousepos.x * mouseSensitivity_,mousepos.y * mouseSensitivity_ ,0 };
	//object_->wtf.position = { mousepos.x,mousepos.y ,0 };
	object_->Update();

	cameraWTF_.position = { mousepos.x,mousepos.y ,0 };
	cameraWTF_.UpdateMat();
	CusUpdate();
	/*cursorPic_->SetPozition({ mousepos.x + WinApp::window_width / 2,-mousepos.y + WinApp::window_height / 2 });*/
	cursorPic_->Update();


	ImGui::Begin("cursorPos");
	ImGui::InputFloat2("mousePos", &mousepos.x);
	ImGui::InputFloat3("cursorPos", &object_->wtf.position.x);
	ImGui::End();
}

///
void Cursor::Draw(DirectXCommon* dxCommon) {
	Object3d::PreDraw(dxCommon->GetCommandList());
	object_->Draw();
	Object3d::PostDraw();
	cursorPic_->Draw();
}

void Cursor::CusUpdate() {
	{
		{
			//自機のワールド座標から3Dレティクルのワールド座標を計算
			//自機から3Dレティクルへの距離
			const float kDistancePlayerTo3DReticle = 0.0f;
			//自機から3Dレティクルへのオフセット(Z+向き)
			Vector3 offset = { 0, 0, 1.0f };
			//自機のワールド行列の回転を反映
			offset = Affin::VecMat(offset, cameraWTF_.matWorld);
			//ベクトルの長さを整える
			float len = sqrt(offset.x * offset.x + offset.y * offset.y + offset.z * offset.z);
			if (len != 0) {
				offset /= len;
			}
			offset *= kDistancePlayerTo3DReticle;
			object_->wtf.position = offset;
			object_->wtf.matWorld = Affin::matTrans(cameraWTF_.position);
			object_->UpdateMatrix();


			Vector3 positionReticle = Affin::GetWorldTrans(object_->wtf.matWorld);

			//ビューポート行列
			Matrix4 matViewport = {
			   WinApp::window_width / 2, 0, 0, 0,
			  0, -WinApp::window_height / 2, 0, 0,
			  0, 0, 1, 0,
			   WinApp::window_width / 2,  WinApp::window_height / 2, 0, 1,
			};

			//ビューポート行列
			Matrix4 matViewProjectionViewport;
			matViewProjectionViewport *= object_->camera_->GetViewMatrix();
			matViewProjectionViewport *= object_->camera_->GetProjectionMatrix();
			matViewProjectionViewport *= matViewport;

			//ワールド→スクリーン座標変換(ここで3Dから2Dになる)
			positionReticle = Affin::wDivision(positionReticle, matViewProjectionViewport);
			ImGui::Begin("cursorPos");
			ImGui::InputFloat2("mousePos", &positionReticle.x);
			ImGui::InputFloat3("cursorPos", &object_->wtf.position.x);
			ImGui::End();
			//スプライトのレティクルに座標設定
			cursorPic_->SetPozition(Vector2(positionReticle.x, positionReticle.y));
		}
	}
}