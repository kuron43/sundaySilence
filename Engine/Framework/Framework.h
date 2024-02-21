#pragma once

#include "WinApp.h"
#include "Input.h"
#include "DirectXCommon.h"
#include "FPS.h"
#include "ImGuiManager.h"
#pragma warning(push)
#pragma warning(disable: 4514)
#include <cassert>
#include <imgui.h>
#pragma warning(pop)

class Framework
{
public: // メンバ関数

	virtual ~Framework() = default;

	virtual void Initialize();

	virtual void Finalize();

	virtual void Update();

	virtual void Draw() = 0;

	virtual bool IsEndRequest() { return endRequest_; }

	void Run();

protected:
	bool endRequest_;

	//ポインタ
	WinApp* winApp = nullptr;
	DirectXCommon* dxCommon = nullptr;
	FPS* fps = nullptr;
	Input* input = nullptr;
	ImGuiManager* imgui = nullptr;

};

