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
	cursorPic_->SetSize({ 160,160 });
	cameraWTF_.Initialize();
	cameraWTF_.position = object_->camera_->GetEye();
	cameraWTF_.UpdateMat();
}

///
void Cursor::Update(Input* input) {

	Vector2 mousepos = input->GetMousePosition();
	object_->wtf.position = { mousepos.x * mouseSensitivity_,mousepos.y * mouseSensitivity_ ,0 };
	//object_->wtf.position = { mousepos.x,mousepos.y ,0 };


	cursorPic_->SetPozition({ mousepos.x + WinApp::window_width / 2,-mousepos.y + WinApp::window_height / 2 });
	cursorPic_->Update();
	object_->Update();
	CusUpdate();


	ImGui::Begin("cursorPos");
	ImGui::InputFloat2("mousePos", &mousepos.x);
	//ImGui::InputFloat3("cameraWTF_", &cameraWTF_.position.x);
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
		//Vector3 positionReticle = { cursorPic_->GetPosition().x,cursorPic_->GetPosition().y,0 };

		////ビューポート行列
		//Matrix4 matViewport = {
		//   WinApp::window_width / 2, 0, 0, 0,
		//  0, -WinApp::window_height / 2, 0, 0,
		//  0, 0, 1, 0,
		//   WinApp::window_width / 2,  WinApp::window_height / 2, 0, 1,
		//};

		////ビューポート行列
		//Matrix4 matViewProjectionViewport = Affin::matUnit();
		//matViewProjectionViewport *= object_->camera_->GetViewMatrix();
		//matViewProjectionViewport *= object_->camera_->GetProjectionMatrix();
		//matViewProjectionViewport *= matViewport;

		////ワールド→スクリーン座標変換(ここで3Dから2Dになる)
		////positionReticle = Affin::wDivision(positionReticle, matViewProjectionViewport);
		//Vector2 cursorPosImgui = cursorPic_.get()->GetPosition();

		//
		////合成行列の逆行列を計算する
		//Matrix4 matInverseVPV = matViewProjectionViewport;
		//Matrix4 resultInverse;
		//resultInverse = matInverseVPV.MakeInverse(&matViewProjectionViewport);

		////スクリーン座標
		//Vector3 posNear = Vector3(positionReticle.x, positionReticle.y, 0);
		//Vector3 posFar = Vector3(positionReticle.x, positionReticle.y, 1);

		////スクリーン座標系からワールド座標系へ
		//posNear = Affin::wDivision(posNear, matViewProjectionViewport);
		//posFar = Affin::wDivision(posFar, matViewProjectionViewport);

		////マウスレイの方向
		//Vector3 mouseDirection = posFar;
		//mouseDirection += posNear;
		//mouseDirection.nomalize();
		////カメラから照準オブジェクトの距離
		//const float kDistanceTestObject = 10.0f;
		//Vector3 A = posNear;
		//A = Vector3(mouseDirection.x * kDistanceTestObject, mouseDirection.y * kDistanceTestObject,
		//	mouseDirection.z * kDistanceTestObject);
		//object_->wtf.position = A;
		////worldTransform3DReticle_.matWorld = Affin::matUnit();
		////object_->wtf.matWorld = Affin::matTrans(object_->wtf.position);
		////object_->wtf.UpdateMat();

		//ImGui::Begin("cursorPos");
		//ImGui::InputFloat2("cursorPicPOS", &cursorPosImgui.x);
		//ImGui::InputFloat3("positionReticle", &positionReticle.x);/////////////////////////////////////////////////////////////////////////////////////////
		//ImGui::InputFloat3("objectPos", &object_->wtf.position.x);

		//ImGui::End();
	}
}