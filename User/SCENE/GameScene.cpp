#include "GameScene.h"

/// <summary>
	/// コンストクラタ
	/// </summary>
GameScene::GameScene() {

}

/// <summary>
/// デストラクタ
/// </summary>
GameScene::~GameScene() {


	//オーディオ解放
	//audio->Finalize();
	//delete audio;
	delete spriteCommon;
	delete sprite;
	delete camera;

	delete skydome, skydomeMD;

	delete particleManager;
}

/// <summary>
/// 初期化
/// </summary>
void GameScene::Initialize(DirectXCommon* dxCommon, Input* input){
	// nullチェック
	assert(dxCommon);
	assert(input);

	this->dxCommon = dxCommon;
	this->input = input;

	//スプライト共通部分の初期化
	spriteCommon = new SpriteCommon;
	spriteCommon->Initialize(dxCommon);

	// カメラ生成
	camera = new Camera(WinApp::window_width, WinApp::window_height);
	//FBXObject3d::SetCamera(camera);
	ParticleManager::SetCamera(camera);
	Object3d::SetCamera(camera);


	skydomeMD = Model::LoadFromOBJ("skydome");

	skydome = Object3d::Create();

	skydome->SetModel(skydomeMD);
	skydome->wtf.scale = (Vector3{ 1000, 1000, 1000 });
	skydome->Update();
	

	sprite = new Sprite();

	Vector2 spritePOS = sprite->GetPosition();
	sprite->Initialize(spriteCommon);
	sprite->SetPozition(spritePOS);
	sprite->SetSize(Vector2{ WinApp::window_width/3,WinApp::window_height/3 });

	spriteCommon->LoadTexture(0, "inu.png");
	sprite->SetTextureIndex(0);

	// パーティクル生成
	particleManager = ParticleManager::Create();
	particleManager->LoadTexture("1.png");
	particleManager->Update();
}

/// <summary>
/// 毎フレーム処理
/// </summary>
void GameScene::Update() {
	camera->Update();
	particleManager->Update();

	skydome->Update();



	// パーティクル起動(長押し)
	{
		if (input->TriggerKey(DIK_P)) {

			//パーティクル範囲
			for (int j = 0; j < 50; j++) {
				//X,Y,Z全て[-5.0f,+5.0f]でランダムに分布
				const float rnd_pos = 0.03f;
				//const float rnd_posX = 1.0f;
				Vector3 pos{};
				pos.x += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
				pos.y += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
				pos.z +=( (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f)+10;

				//速度
				//X,Y,Z全て[-0.05f,+0.05f]でランダムに分布
				const float rnd_vel = 0.5f;
				Vector3 vel{};
				vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
				vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
				vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
				//重力に見立ててYのみ[-0.001f,0]でランダムに分布
				const float rnd_acc = -0.01f;
				const float rnd_acc_v = -0.01f;
				Vector3 acc{};
				acc.x = ((float)rand() / RAND_MAX * rnd_acc) * ((float)rand() / RAND_MAX * rnd_acc_v);
				acc.y = ((float)rand() / RAND_MAX * rnd_acc) * ((float)rand() / RAND_MAX * rnd_acc_v);
				//acc.z = (float)rand() / RAND_MAX * rnd_acc;

				//追加
				particleManager->Add(50, pos, vel, acc, 1.0f, 0.0f);
			}
		}
	}
}

/// <summary>
/// 描画
/// </summary>
void GameScene::Draw() {

	//3Dオブジェクト描画前処理
	Object3d::PreDraw(dxCommon->GetCommandList());
	/// <summary>
	/// 3Dオブジェクトの描画
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// <summary>
	
	skydome->Draw();
	
	//3Dオブジェクト描画後処理
	Object3d::PostDraw();

	// 3Dオブジェクト描画前処理
	ParticleManager::PreDraw(dxCommon->GetCommandList());


	//// 3Dオブクジェクトの描画
	particleManager->Draw();

	// 3Dオブジェクト描画後処理
	ParticleManager::PostDraw();

	sprite->Draw();
}