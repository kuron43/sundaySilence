#include "ImGuiManager.h"
#include <imgui_impl_win32.h>
#include <imgui_impl_dx12.h>

void ImGuiManager::Initialize(WinApp* winApp, DirectXCommon* dxCommon) {
	assert(winApp);
	assert(dxCommon);
	HRESULT result;

	// ImGuiのコンテキスト生成
	ImGui::CreateContext();
	// imguiのスタイルを設定
	ImGui::StyleColorsDark();

	// win32用の初期関数呼び出し
	ImGui_ImplWin32_Init(winApp->GetHwnd());

	// デスクリプターヒープ設定
	D3D12_DESCRIPTOR_HEAP_DESC desc = {};
	desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	desc.NumDescriptors = 1;
	desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	// デスクリプターヒープ生成	
	result = dxCommon->GetDevice()->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&srvHeap_));
	assert(SUCCEEDED(result));

	// DirectX12用の初期関数呼び出し
	ImGui_ImplDX12_Init(
		dxCommon->GetDevice(),
		static_cast<int>(dxCommon->GetBackBufferCount()),
		DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, srvHeap_.Get(),
		srvHeap_->GetCPUDescriptorHandleForHeapStart(),
		srvHeap_->GetGPUDescriptorHandleForHeapStart()
	);

	// フォント追加
	ImGuiIO& io = ImGui::GetIO();
	// 標準フォントを追加
	io.Fonts->AddFontDefault();


}
