/**
 * @file Cursor.cpp
 * @brief
 */
#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
#pragma warning(disable: 4514)
#include <imgui.h>
#pragma warning(pop)
#include "Affin.h"
#include "Cursor.h"

Cursor::Cursor() {
}
Cursor::~Cursor() {
}

///
void Cursor::Initialize(SpriteCommon* spriteCommon) {

	cursorPic_ = std::make_unique<Sprite>();
	cursorPic_->Initialize(spriteCommon, 7);
	cursorPic_->SetSize({ 24,24 });
	//cursorPic_->SetAnchorPoint({ 1,1 });
}

///
void Cursor::Update(Input* input) {
	CusUpdate(input);
	cursorPic_->Update();
}

///
void Cursor::Draw() {

	cursorPic_->Draw();
}

void Cursor::CusUpdate(Input* input) {
	if (input) {

	}
	cursorPic_->SetTextureIndex(7);
	mousepos_ = input->GetMousePosition();
	//mousepos_.y *= -1;
	if ((mousepos_.x + WinApp::window_width / 2) >= WinApp::window_width) {
		mousepos_.x = (WinApp::window_width/2) - 1;
	}
	else if ((mousepos_.x - WinApp::window_width / 2) <= -WinApp::window_width) {
		mousepos_.x = (-WinApp::window_width / 2);
	}
	if (mousepos_.y+(WinApp::window_height / 2) >= WinApp::window_height) {
		mousepos_.y = (WinApp::window_height/2) - 1;
	}
	else if (mousepos_.y - (WinApp::window_height / 2) <= -WinApp::window_height) {
		mousepos_.y = (-WinApp::window_height / 2)+1;
	}
	cursorPicPos = { mousepos_.x + WinApp::window_width / 2,-mousepos_.y + WinApp::window_height / 2 };
	cursorPic_->SetPozition(cursorPicPos);
	spritePos_ = cursorPic_->GetPosition();


	ImGui::Begin("cursorPos");
	ImGui::InputFloat2("spritePos", &spritePos_.x);
	ImGui::InputFloat2("spritePos", &cursorPicPos.x);
	ImGui::InputFloat2("mousePos", &mousepos_.x);
	ImGui::End();
}

// スプライトとの当たりはんちぇい
bool Cursor::Cursor2Sprite(Sprite* sprite)
{

	Vector2 spPosLU = sprite->GetPosition();
	Vector2 spSize = sprite->GetSize();
	if (spPosLU.x<spritePos_.x && spPosLU.x + spSize.x>spritePos_.x &&
		spPosLU.y<spritePos_.y && spPosLU.y + spSize.y>spritePos_.y) {
		cursorPic_->SetTextureIndex(18);
		return true;
	}
	else {
		return false;
	}
}
