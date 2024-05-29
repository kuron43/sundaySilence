//#pragma once
//// MotionBlur.cpp
//
//#include <d3d12.h>
//#include <dxgi1_4.h>
//#include <d3dcompiler.h>
//#include <DirectXMath.h>
//
//// 省略されたヘッダーと定義
//
//// シェーダーコードをバイナリデータとして定義
//extern const BYTE g_VSCode[];
//extern const BYTE g_PSCode[];
//
//// 定数バッファ構造体
//struct ConstantBufferData
//{
//	DirectX::XMFLOAT2 motionVector;
//};
//
//int main()
//{
//	// 省略された初期化コード
//
//	// シェーダーをコンパイルおよび作成
//	ID3DBlob* vsBlob = nullptr;
//	ID3DBlob* psBlob = nullptr;
//	CompileShader(L"MotionBlurVS.hlsl", "mainVS", "vs_5_0", &vsBlob);
//	CompileShader(L"MotionBlurPS.hlsl", "mainPS", "ps_5_0", &psBlob);
//
//	// 省略されたDirectX 12 セットアップコード
//
//	// 定数バッファを作成
//	ConstantBufferData constantBufferData;
//	constantBufferData.motionVector = DirectX::XMFLOAT2(0.02f, 0.0f); // モーションベクトルの設定
//
//	// 定数バッファをアップロードヒープに作成
//	ID3D12Resource* constantBuffer;
//	CreateBuffer(device, sizeof(ConstantBufferData), &constantBufferData, &constantBuffer);
//
//	// シェーダーリソースビューを作成
//	ID3D12DescriptorHeap* srvHeap;
//	CreateShaderResourceView(device, texture, &srvHeap);
//
//	// メインループ
//	while (!done)
//	{
//		// 省略されたレンダリングコード
//
//		// 定数バッファ更新
//		UpdateSubresources(commandList, constantBuffer, constantBufferUploadHeap, 0, 0, 1, &constantBufferData);
//
//		// シェーダーリソースビューのセット
//		commandList->SetGraphicsRootDescriptorTable(0, srvHeap->GetGPUDescriptorHandleForHeapStart());
//
//		// 定数バッファのセット
//		commandList->SetGraphicsRootConstantBufferView(1, constantBuffer->GetGPUVirtualAddress());
//
//		// 省略された描画コマンド
//
//		// フェンスで同期
//		ExecuteCommandList(commandList);
//		WaitForPreviousFrame();
//	}
//
//	// 省略された後始末コード
//
//	return 0;
//}