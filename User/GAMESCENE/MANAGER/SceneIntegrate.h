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
#include "GAME1Scene.h"
#include "GAME2Scene.h"

// チェンジシーン用のenum
enum _SCENE_ {
	SCE_TITLE = 1,
	SCE_CLEAR ,
	SCE_PAUSE ,
	SCE_SELECT,
	SCE_TRANS ,
	SCE_GAME1 ,
	SCE_GAME2 ,
	SCE_GAME3 
};

enum LEVELS
{
	TITLE,
	TUTRIAL,
	STAGE1,
	STAGE2,
};