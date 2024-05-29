#pragma once
/**
 * @file SceneIntegrate
 * @brief シーンを選択しやすいようにシーンの一括インクルード
 */

// 要らないなら消しておk

#include "TitleScene.h"
#include "PauseScene.h"
#include "SelectScene.h"
#include "Clear.h"

#include "TransitionsScene.h"
#include "Tutorial.h"
#include "GAME1Scene.h"
#include "GAME2Scene.h"

// チェンジシーン用のenum
enum _SCENE_ {
	SCE_TITLE = 1,
	SCE_CLEAR ,
	SCE_PAUSE ,
	SCE_SELECT,
	SCE_TRANS ,
	SCE_TUTO  ,
	SCE_GAME1 ,
	SCE_GAME2 ,
	SCE_GAME3 ,
};
enum _TUTOSCENE_ {
	TUTO_PAUSE,
	TUTO_1 ,
	TUTO_2 ,
	TUTO_3 ,
	TUTO_4 ,
	TUTO_5 ,
	TUTO_6 ,
	TUTO_7 ,
	TUTO_8 ,
};

enum LEVELS
{
	TITLE,
	TUTRIAL,
	STAGE1,
	STAGE2,
	TUTRIAL_1,
	TUTRIAL_2,
	TUTRIAL_3,
	TUTRIAL_4,
};