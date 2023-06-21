#include "ImGuiManager.h"
#include <imgui_impl_win32.h>
#include <imgui_impl_dx12.h>

void ImGuiManager::Initialize(WinApp* winApp, DirectXCommon* dxCommon) {
	assert(winApp);
	assert(dxCommon);

	dxCommon_ = dxCommon;
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
	result = dxCommon_->GetDevice()->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&srvHeap_));
	assert(SUCCEEDED(result));

	// DirectX12用の初期関数呼び出し
	ImGui_ImplDX12_Init(
		dxCommon_->GetDevice(),
		static_cast<int>(dxCommon_->GetBackBufferCount()),
		DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, srvHeap_.Get(),
		srvHeap_->GetCPUDescriptorHandleForHeapStart(),
		srvHeap_->GetGPUDescriptorHandleForHeapStart()
	);

	// フォント追加
	ImGuiIO& io = ImGui::GetIO();
	// 標準フォントを追加
	io.Fonts->AddFontDefault();


}

void ImGuiManager::Finalize() {
	// 後始末
	ImGui_ImplDX12_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	// デスクリプターヒープを解放
	srvHeap_.Reset();

}

void ImGuiManager::Begin() {
	// ImGuiフレーム開始
	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void ImGuiManager::End() {
	// 描画前準備
	ImGui::Render();

}

void ImGuiManager::Draw() {
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList = dxCommon_->GetCommandList();

	// デスクリプターヒープの配列をセットするコマンド
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> ppHeaps[] = { srvHeap_.Get() };
	commandList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps->GetAddressOf());
	// 描画コマンドを発行
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), commandList.Get());
}
