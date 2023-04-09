#include "TitleScene.h"
#include "SceneManager.h"

#include "EndScene.h"



TitleScene::TitleScene(SceneManager* controller) {
	_controller = controller;
}
TitleScene::~TitleScene() {
	delete spriteCommon;
	delete sprite;
	delete sprite2;

	delete particleManager;
	delete particleManager2;

	delete obj2, obj2MD;
	delete obj, model;
}

void TitleScene::Initialize(DirectXCommon* dxCommon) {

	// パーティクル生成
	particleManager = ParticleManager::Create();
	particleManager->LoadTexture("1.png");
	particleManager->Update();
	particleManager2 = ParticleManager_2::Create();
	particleManager2->LoadTexture("1_2.png");
	particleManager2->Update();

	//スプライト共通部分の初期化
	spriteCommon = new SpriteCommon;
	spriteCommon->Initialize(dxCommon);

	sprite = new Sprite();
	Vector2 spritePOS = sprite->GetPosition();
	sprite->Initialize(spriteCommon);
	sprite->SetPozition({0,0});
	sprite->SetSize(Vector2{ WinApp::window_width / 3,WinApp::window_height / 3 });


	sprite2 = new Sprite();
	Vector2 spritePOS2 = Vector2{ WinApp::window_width / 2,WinApp::window_height / 2 };
	sprite2->Initialize(spriteCommon);
	sprite2->SetPozition(spritePOS2);
	sprite2->SetSize(Vector2{ WinApp::window_width / 3,WinApp::window_height / 3 });

	spriteCommon->LoadTexture(0, "title.png");
	sprite->SetTextureIndex(0);
	spriteCommon->LoadTexture(1, "title.png");
	sprite2->SetTextureIndex(1);
	

	
	obj2MD = Model::LoadFromOBJ("ene");
	model = Model::LoadFromOBJ("REX");

	obj2 = Object3d::Create();
	obj2->SetModel(obj2MD);
	obj2->wtf.scale = (Vector3{ 0.8, 0.8, 0.8 });
	obj2->Update();

	obj = Object3d::Create();
	obj->SetModel(model);
	obj->wtf.position = (Vector3{ 5, 1, 5 });
	obj->wtf.scale = (Vector3{ 0.1, 0.1, 0.1 });
	obj->Update();

}

void TitleScene::Update(Input* input) {

	obj->Update();
	obj2->Update();

	particleManager->Update();
	particleManager2->Update();

	// パーティクル起動( P 押し)
	{

		if (input->KeyboardTrigger(DIK_E)) {
			particleManager2->LoadTexture("1_2.png");
			//パーティクル範囲
			for (int j = 0; j < 50; j++) {
				//X,Y,Z全て[-5.0f,+5.0f]でランダムに分布
				const float rnd_pos = 0.03f;
				//const float rnd_posX = 1.0f;
				Vector3 pos{};
				pos.x += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
				pos.y += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
				pos.z += ((float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f) + 10;

				//速度
				//X,Y,Z全て[-0.05f,+0.05f]でランダムに分布
				const float rnd_vel = 0.5f;
				Vector3 vel{};
				vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
				vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
				//vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
				//重力に見立ててYのみ[-0.001f,0]でランダムに分布
				const float rnd_acc = -0.01f;
				const float rnd_acc_v = -0.01f;
				Vector3 acc{};
				acc.x = ((float)rand() / RAND_MAX * rnd_acc) * ((float)rand() / RAND_MAX * rnd_acc_v);
				acc.y = ((float)rand() / RAND_MAX * rnd_acc) * ((float)rand() / RAND_MAX * rnd_acc_v);
				//acc.z = (float)rand() / RAND_MAX * rnd_acc;

				//追加
				particleManager->Add(100, pos+acc, vel + vel, acc, 1.0f, 0.0f);
				particleManager2->Add(100, pos, vel, acc, 1.0f, 0.0f);
			}
		}
	}

	if (input->KeyboardTrigger(DIK_SPACE) || input->Pad_X_ButtonTrigger(LB)) {
		//_controller->ChangeScene(new EndScene(_controller));
		
	}
}

void TitleScene::Draw(DirectXCommon* dxCommon) {

	
	sprite->Draw();
	sprite2->Draw();
	


	//3Dオブジェクト描画前処理
	Object3d::PreDraw(dxCommon->GetCommandList());

	obj2->Draw();
	obj->Draw();

	//3Dオブジェクト描画後処理
	Object3d::PostDraw();
	
	particleManager->Draw(dxCommon->GetCommandList());
	particleManager2->Draw(dxCommon->GetCommandList());
}