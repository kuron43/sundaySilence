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
	void Initialize(WinApp* winApp, DirectXCommon* dxCommon);

	/// <summary>
	/// 終了
	/// </summary>
	void Finalize();

	/// <summary>
	/// Imgui受付開始
	/// </summary>
	void Begin();
	
	/// <summary>
	/// Imgui受付終了
	/// </summary>
	void End();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();


private:
	DirectXCommon* dxCommon_;

	// SRV用デスクリプターヒープ
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvHeap_;

public:



};

