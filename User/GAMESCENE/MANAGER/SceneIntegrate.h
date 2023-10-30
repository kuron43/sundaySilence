#pragma once
/**
 * @file SceneIntegrate
 * @brief シーンを選択しやすいようにシーンの一括インクルード
 */

// 要らないなら消しておk

#include "TitleScene.h"
#include "EndScene.h"
#include "PauseScene.h"
#include "SelectScene.h"
#include "GameOver.h"

#include "TransitionsScene.h"
#include "GAME1Scene.h"
#include "GAME2Scene.h"

// チェンジシーン用のenum
enum _SCENE_ {
	SCE_TITLE = 1,
	SCE_OVER = 2,
	SCE_CLEAR = 3,
	SCE_PAUSE = 4,
	SCE_SELECT = 5,
	SCE_TRANS = 6,
	SCE_GAMEOVER = 7,
	SCE_GAME1 = 8,
	SCE_GAME2 = 9
};