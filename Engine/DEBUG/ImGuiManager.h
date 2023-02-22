#pragma once
#include "WinApp.h"
#include "DirectXCommon.h"

// Imgui の管理
class ImGuiManager
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(WinApp* winApp,DirectXCommon* dxCommon);

private:

	// SRV用デスクリプターヒープ
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvHeap_;

public:



};

