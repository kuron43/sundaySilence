#pragma once
// シーンを選択しやすいようにシーンの一括インクルード
// 要らないなら消しておk

#include "TitleScene.h"
#include "GAME1Scene.h"
#include "EndScene.h"
#include "PauseScene.h"

enum _SCENE_{
	SC_TITLE = 1,
	SC_OVER = 2,
	SC_CLEAR = 3,
	SC_PAUSE = 4,
	SC_GAME1 = 5,
};