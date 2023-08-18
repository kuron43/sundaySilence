#pragma once
// シーンを選択しやすいようにシーンの一括インクルード
// 要らないなら消しておk

#include "TitleScene.h"
#include "EndScene.h"
#include "PauseScene.h"

#include "GAME1Scene.h"
#include "GAME2Scene.h"

enum _SCENE_ {
	SCE_TITLE = 1,
	SCE_OVER = 2,
	SCE_CLEAR = 3,
	SCE_PAUSE = 4,
	SCE_GAME1 = 5,
	SCE_GAME2 = 6
};