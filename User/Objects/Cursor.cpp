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
}

///
void Cursor::Update(Input* input) {
	CusUpdate(input);

	cursorPic_->Update();
	object_->Update();

}

///
void Cursor::Draw(DirectXCommon* dxCommon) {
	Object3d::PreDraw(dxCommon->GetCommandList());
	//object_->Draw();
	Object3d::PostDraw();

	cursorPic_->Draw();
}

void Cursor::CusUpdate(Input* input) {
	if (input) {

	}
	mousepos_ = input->GetMousePosition();
	mousepos_.y *= -1;

	object_->wtf.position = { mousepos_.x * mouseSensitivity_,mousepos_.y * mouseSensitivity_ ,0 };
	cursorPic_->SetPozition({ mousepos_.x + WinApp::window_width / 2,mousepos_.y + WinApp::window_height / 2 });
	spritePos_ = cursorPic_->GetPosition();

	ImGui::Begin("cursorPos");
	ImGui::InputFloat2("mousePos", &mousepos_.x);
	ImGui::InputFloat2("spritePos", &spritePos_.x);
	ImGui::InputFloat3("objectPos", &object_->wtf.position.x);
	ImGui::End();
}

bool Cursor::Cursor2Sprite(Sprite sprite)
{
	{
		Vector2 spPosLU = sprite.GetPosition();
		Vector2 spSize = sprite.GetSize();
		if (spPosLU.x<spritePos_.x && spPosLU.x + spSize.x>spritePos_.x &&
			spPosLU.y<spritePos_.y && spPosLU.y + spSize.y>spritePos_.y) {
			return true;
		}
		return false;
	}
}
