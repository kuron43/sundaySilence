#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include "WinApp.h"
//#include <DirectXTex.h>
#include <vector>

//DirectX基盤
class DirectXCommon
{
public://メンバ関数
	//初期化
	void Initialize(WinApp* winApp);

	void InitializeDevice();

	void InitializeCommand();

	void InitializeSwapchain();

	void InitializeRenderTargetView();

	void InitializeDepthBuffer();

	void InitializeFence();

	//描画前処理
	void PreDraw();
	//描画後処理
	void PostDraw();

	//デバイス取得
	ID3D12Device* GetDevice() const { return device.Get(); }

	//コマンドリスト取得
	ID3D12GraphicsCommandList* GetCommandList()const { return commandList.Get(); }

	//バックバッファの数を取得
	size_t GetBackBufferCount() const { return backBuffers.size(); }

private:
	//DirectX12デバイス
	Microsoft::WRL::ComPtr<ID3D12Device> device;
	//DXGIファクトリ
	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory;
	//バックバッファ
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> backBuffers;

	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};

	D3D12_RESOURCE_DESC depthResourceDesc{};

	//WindowsAPI
	WinApp* winApp_ = nullptr;

	HRESULT result;
	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> cmdAllocator;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList;
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvHeap;
	Microsoft::WRL::ComPtr<ID3D12Fence> fence;
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvHeap;
	D3D12_RESOURCE_BARRIER barrierDesc{};
	UINT64 fenceVal = 0;
	Microsoft::WRL::ComPtr<ID3D12Resource> depthBuff;
};