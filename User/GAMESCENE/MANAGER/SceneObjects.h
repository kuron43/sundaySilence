#pragma once
/**
 * @file SceneObject.h
 * @brief シーンオブジェクト所持クラス
 */
#include <map>
#include <string>

#include "LightGroup.h"
#include "FBXObject3d.h"
 //#include "fbx/FBXLoader.h"
 //#include "FBXModel.h"
#include "Audio.h"
#include "SpriteCommon.h"
#include "Model.h"
#include "Object3d.h"
#include "ParticleManager.h"
#include "JsonLoader.h"

#include "Human.h"
#include "Player.h"
#include "Enemy.h"
#include "Boss.h"

#include "Wall.h"
#include "Floor.h"

#include "Cursor.h"

typedef struct Shake {
	uint32_t isShake;
	uint32_t count;
	uint32_t maxSwing;
	uint32_t quantity;
	uint32_t randX;
	uint32_t randZ;
}Shake;

// ゲーム使用のオブジェクト一括宣言クラス
class SceneObjects
{
private:
	DirectXCommon* _dxcommon;
public:
	SceneObjects(DirectXCommon* dxcommon);
	~SceneObjects();


	void Initialize();
	void Reset();
	void UpdateImGui();

public: // 演出用

	void BannerDraw();
	bool Banner(uint32_t isStart = 0);
	void ShakeRand(Shake& w);

	void SlowEffect(bool isSlow);
	void SlowReset();
	void SlowEffectDraw();

private: // 演出用
	// バナー用
	std::unique_ptr <Sprite> bannerBuckSP_;
	Vector2 bannerBuckSPpos_;
	Vector3 bannerBuckSPscale_;
	std::unique_ptr <Sprite> bannerBuck2SP_;
	Vector2 bannerBuck2SPpos_;
	Vector3 bannerBuck2SPscale_;
	std::unique_ptr <Sprite> bannerWordSP_;
	Vector2 bannerWordSPpos_;
	Vector3 bannerWordSPscale_;
	uint32_t bannerTimer = 0;
	// バナーイージング用
	float bannerEasetime = 0.0f;
	uint32_t bannerTime = 0;
	uint32_t bannerEaseMaxTime = 50;
	bool isBannerEaseOut = true;

	// スロー用
	std::unique_ptr <Sprite> slowSP_;
	Vector3 slowSPsize_;
	const float slowSP_ALPHA_MIN = 0.0f;
	const float slowSP_ALPHA_MAX = 0.4f;
	float slowSPAlpha_ = 0.0f;
	bool slowSPTime_MAX = false;
	bool slowPlayEase_ = false;
	bool nowSlowEffect = false;
	bool changeIsSlow = false;
	// スローイージング用
	float slowEasetime = 0.0f;
	uint32_t slowTime = 0;
	uint32_t slowEaseMaxTime = 30;
	bool isSlowEaseOut = false;



	Shake backWall;
public: // UI用
	void UIUpdate();
	void UIDraw();

	void ONIsUIDraw() { isUIDraw_ = true; };
	void OFFIsUIDraw() { isUIDraw_ = false; };
	bool GetIsUIDraw() { return isUIDraw_; };

public:
	void LoadLevels();
	void SetingLevel(LevelData* data);

private: // UI用
	bool isUIDraw_ = false;

	// ベース
	std::unique_ptr <Sprite> UIBuckSP_;
	Vector2 UIBuckSPpos_;
	Vector2 UIBuckSPsize_;

	// 武器
	std::unique_ptr <Sprite> UIBarrierGaugeSP_;
	Vector2 UIWeaponSPpos_;
	Vector2 UIWeaponSPsize_;
	uint32_t UISP_Wep_size;
	bool isFire_;
	// スロー
	std::unique_ptr <Sprite> UISlowSP_;
	Vector2 UISlowSPpos_;
	Vector2 UISlowSPsize_;
	// ポイント
	std::unique_ptr <Sprite> UIPointSP_;
	Vector2 UIPointSPpos_;
	Vector2 UIPointSPsize_;

	// ポーズ案内
	std::unique_ptr <Sprite> UIPauseSP_;
	Vector2 UIPauseSPpos_;
	Vector2 UIPauseSPsize_;

	// PlayerHP 仮
	std::unique_ptr <Sprite> UIHPSP_;
	Vector2 UIHPSPpos_;
	Vector2 UIHPSPsize_;
	std::unique_ptr <Sprite> UIHPBaseSP_;
	Vector2 UIHPBaseSPpos_;
	Vector2 UIHPBaseSPsize_;
	std::array<std::unique_ptr <Sprite>, NUMBER::NUM_FIVE> UIDushSP_;
	Vector2 UIDushPos_;
	Vector2 UIDushSize_;

public: // オブジェクトの管理
	std::unique_ptr <LightGroup> lightGroup;
	std::unique_ptr <Audio> audio;
	std::unique_ptr <SpriteCommon> spriteCommon_;
	std::unique_ptr<Cursor> mouseCursor_;

	std::unique_ptr <Object3d> skydome_O;
	Model* skydome_M;
	Model* box;

	//FBXモデル
	std::unique_ptr<FBXModel> bossFbxM_;
	std::unique_ptr<FBXObject3d> bossFbxO_;

	// ポリモーフィズムとは...
	std::unique_ptr<Player> player;
	std::unique_ptr <Sprite> plDamageRed_;
	float damageRedAlpha_ = 0.0f;
	Vector2 plDamageRedPos = { 0.0f,0.0f };
	std::unique_ptr<Model> enemyMD;
	std::unique_ptr<Model> maruMD;
	std::list<std::unique_ptr<Enemy>> enemys;
	uint32_t eneCount;
	std::list<std::unique_ptr<Boss>> boss;
	uint32_t bossCount;

	std::unique_ptr<Model> wallMD;
	std::list< std::unique_ptr <Wall>> walls;

	std::unique_ptr<Floor> floorGround;
	Model* floorGroundMD;

	// レベルデータ管理
	std::vector<std::string> levelName_;
	std::map<std::string, std::unique_ptr<LevelData>>levels;

private: // ライト用
	Vector3 rotateLight{ 10.0f,1,0 };
	Vector3 lightDir = { 0,1,0 };
	float ambientColor0[3] = { 1,1,1 };

	//光線方向初期値
	float lightDir0[3] = { 0,0,1 };
	float lightColor0[3] = { 1,1,1 };
	float lightDir1[3] = { 0,1,0 };
	float lightColor1[3] = { 1,1,1 };
	float lightDir2[3] = { 1,0,0 };
	float lightColor2[3] = { 1,1,1 };

	Vector3 pointLightPos = { 10.0f,4.0f,0 };
	float pointLightColor[3] = { 1,1,1 };
	float pointLightAtten[3] = { 0.3f,0.1f,0.1f };

	float spotLightDir[3] = { 0,-1,0 };
	float spotLightPos[3] = { 0,5,0 };
	float spotLightColor[3] = { 1,1,1 };
	float spotLightAtten[3] = { 0.0f,0.0f,0.0f };
	float spotLightFactorAngle[2] = { 20.0f,30.0f };

	float circleShadowDir[3] = { 0,-1,0 };
	float circleShadowAtten[3] = { 0.5f,0.6f,0.0f };
	float circleShadowFactorAngle[2] = { 0.0f,0.5f };
};

