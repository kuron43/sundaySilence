#include "PostEffect.h"
#include<d3dx12.h>
#include"WinApp.h"
#include <cassert>
#include <d3dcompiler.h>

#pragma comment(lib, "d3dcompiler.lib")

ID3D12Device* PostEffect::device_;

ID3D12GraphicsCommandList* PostEffect::commandList;

PostEffect::VertexPosUv PostEffect::vertices[4];

PostEffect::VertexPosUv* PostEffect::vertMap;

Microsoft::WRL::ComPtr<ID3D12Resource> PostEffect::vertBuff;	//頂点バッファ

//頂点バッファビューの作成
D3D12_VERTEX_BUFFER_VIEW PostEffect::vbView{};
Microsoft::WRL::ComPtr<ID3D12Resource> PostEffect::texBuff[2];

Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> PostEffect::descHeapSRV;
//深度バッファ
Microsoft::WRL::ComPtr<ID3D12Resource> PostEffect::depthBuff;
//RTV用のデスクリプタヒープ
Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> PostEffect::descHeapRTV;
//DSV用のデスクリプタヒープ
Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> PostEffect::descHeapDSV;

Microsoft::WRL::ComPtr<ID3D12PipelineState> PostEffect::pipelineState;
Microsoft::WRL::ComPtr<ID3D12RootSignature> PostEffect::rootSignature;

// 定数バッファ
Microsoft::WRL::ComPtr<ID3D12Resource> PostEffect::constDataBuff_;
// マッピング済みアドレス
PostEffect::SendDataGPU* PostEffect::dataMap = nullptr;

const float PostEffect::clearColor[4] = { 0.0f,0.0f,0.0f,0 };

void PostEffect::Initialize(DirectXCommon* dxCommon)
{
	HRESULT result;

	device_ = dxCommon->GetDevice();

	D3D12_RESOURCE_DESC texresDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,
		WinApp::window_width,
		(UINT)WinApp::window_height,
		1, 0, 1, 0, D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET);
	{

		//テクスチャバッファの生成
		//ヒープ設定
		CD3DX12_HEAP_PROPERTIES heapProp(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK,
			D3D12_MEMORY_POOL_L0);

		CD3DX12_CLEAR_VALUE clearValue(DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, clearColor);

		for (int i = 0; i < 2; i++) {

			result = device_->CreateCommittedResource(
				&heapProp,
				D3D12_HEAP_FLAG_NONE,
				&texresDesc,
				D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
				&clearValue,
				IID_PPV_ARGS(&texBuff[i]));
			assert(SUCCEEDED(result));

			{//テクスチャを赤クリア
			//画素数(1280*720=921600ピクセル)
				const UINT pixelCount = WinApp::window_width * WinApp::window_height;
				//画像1行分のデータサイズ
				const UINT rowPitch = sizeof(UINT) * WinApp::window_width;
				//画像全体のデータサイズ
				const UINT depthPitch = rowPitch * WinApp::window_height;
				//画像イメージ
				UINT* img = new UINT[pixelCount];
				for (int j = 0; j < pixelCount; j++) { img[j] = 0xffffffff; }


				result = texBuff[i]->WriteToSubresource(0, nullptr,
					img, rowPitch, depthPitch);
				assert(SUCCEEDED(result));
				delete[] img;
			}

		}

	}
	//SRV用のデスクリプタヒープ設定
	D3D12_DESCRIPTOR_HEAP_DESC srvDescHeapDesc = {};
	srvDescHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvDescHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	srvDescHeapDesc.NumDescriptors = 2;
	//SRVデスクリプタヒープ設定
	result = device_->CreateDescriptorHeap(&srvDescHeapDesc, IID_PPV_ARGS(&descHeapSRV));
	assert(SUCCEEDED(result));
	//SRV設定
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;

	for (int i = 0; i < 2; i++) {
		//デスクリプタヒープにSRVを作成
		device_->CreateShaderResourceView(texBuff[i].Get(),
			&srvDesc,
			CD3DX12_CPU_DESCRIPTOR_HANDLE(descHeapSRV->GetCPUDescriptorHandleForHeapStart(), i,
				device_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV))
		);
	}

	//RTV用のデスクリプタヒープ設定
	D3D12_DESCRIPTOR_HEAP_DESC rtvDescHeapDesc{};

	rtvDescHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvDescHeapDesc.NumDescriptors = 2;

	result = device_->CreateDescriptorHeap(&rtvDescHeapDesc, IID_PPV_ARGS(&descHeapRTV));
	assert(SUCCEEDED(result));
	//RTV用のデスクリプタヒープを生成
	for (int i = 0; i < 2; i++) {
		//デスクリプタヒープにRTVを作成
		device_->CreateRenderTargetView(texBuff[i].Get(), nullptr, CD3DX12_CPU_DESCRIPTOR_HANDLE(
			descHeapRTV->GetCPUDescriptorHandleForHeapStart(), i, device_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV)));
	}


	descHeapDSV = dxCommon->GetdsvHeap();

	depthBuff = dxCommon->GetbackBuffers();

	VertexPosUv vertices_[4] = {
		{{-1.0f,-1.0f,0.0f},{0.0f,1.0f}},
		{{-1.0f,+1.0f,0.0f},{0.0f,0.0f}},
		{{+1.0f,-1.0f,0.0f},{1.0f,1.0f}},
		{{+1.0f,+1.0f,0.0f},{1.0f,0.0f}},
	};
	for (int i = 0; i < 4; i++)
	{
		vertices[i] = vertices_[i];
	}

	//頂点データ全体のサイズ=頂点データ一つ分のサイズ*頂点データの要素数
	UINT sizeVB = static_cast<UINT>(sizeof(vertices[0]) * _countof(vertices));
	//頂点バッファの設定
	D3D12_HEAP_PROPERTIES heapProp{};  //ヒープ設定
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD; //GPUへの転送用
	//リソース設定
	D3D12_RESOURCE_DESC resDesc{};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = sizeVB; //頂点データ全体のサイズ
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	//頂点バッファの生成
	result = device_->CreateCommittedResource(
		&heapProp, //ヒープ設定
		D3D12_HEAP_FLAG_NONE,
		&resDesc, //リソース設定
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vertBuff));
	assert(SUCCEEDED(result));

	//GPU上のバッファに対応した仮想メモリ（メインメモリ上）を取得
	result = vertBuff->Map(0, nullptr, (void**)&vertMap);
	assert(SUCCEEDED(result));
	//前頂点に対して
	for (int i = 0; i < _countof(vertices); i++) {
		vertMap[i] = vertices[i]; //座標コピー
	}

	//GPU仮想アドレス
	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
	//頂点バッファのサイズ
	vbView.SizeInBytes = sizeVB;
	//頂点一つ分のデータサイズ
	vbView.StrideInBytes = sizeof(vertices[0]);

	CreatGraphicsPipeline();


	// ヒーププロパティ
	CD3DX12_HEAP_PROPERTIES heapProps = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	// リソース設定
	CD3DX12_RESOURCE_DESC resourceDesc =
		CD3DX12_RESOURCE_DESC::Buffer((sizeof(SendDataGPU) + 0xff) & ~0xff);

	// 定数バッファの生成
	result = dxCommon->GetDevice()->CreateCommittedResource(
		&heapProps, // アップロード可能
		D3D12_HEAP_FLAG_NONE, &resourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
		IID_PPV_ARGS(&constDataBuff_));
	assert(SUCCEEDED(result));

	//定数バッファのマッピング
	result = constDataBuff_->Map(0, nullptr, (void**)&dataMap);
	assert(SUCCEEDED(result));

	//定数として10を入れておく(ぼかし度)
	dataMap->shadeNumber = 1;
	dataMap->kernelSize = 10;
	dataMap->center = { 0.5f,0.5f };
	dataMap->intensity = 0.1f;
	dataMap->samples = 1;

	constDataBuff_->Unmap(0, nullptr);
}

void PostEffect::Finalize()
{

	vertBuff.Reset();
	for (int i = 0; i < 2; i++) {
		texBuff[i].Reset();
	}
	descHeapSRV.Reset();
	depthBuff.Reset();
	descHeapRTV.Reset();
	descHeapDSV.Reset();
	pipelineState.Reset();
	rootSignature.Reset();

}

void PostEffect::CreatGraphicsPipeline()
{
	HRESULT result;

	Microsoft::WRL::ComPtr<ID3DBlob> vsBlob = nullptr;//頂点シェーダーオブジェクト
	Microsoft::WRL::ComPtr<ID3DBlob> psBlob = nullptr;//ピクセルシェーダーオブジェクト

	ID3DBlob* errorBlob = nullptr;//エラーオブジェクト

	//頂点シェーダーの読み込みとコンパイル
	result = D3DCompileFromFile(
		L"Resources/SHADER/PostEffectVS.hlsl", //シェーダーファイル名
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,//インクルード可能にする
		"main", "vs_5_0",//エントリーポイント名、シェーダーモデル指定
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, //デバッグ用設定
		0,
		&vsBlob, &errorBlob);

	//エラーなら
	if (FAILED(result)) {
		//errorBlobからエラー内容をstring型にコピー
		std::string error;
		error.resize(errorBlob->GetBufferSize());

		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			error.begin());
		error += "\n";
		//エラー内容を出力ウインドウに表示
		OutputDebugStringA(error.c_str());
		assert(0);
	}
	//ピクセルシェーダーの読み込みとコンパイル
	result = D3DCompileFromFile(
		L"Resources/SHADER/PostEffectPS.hlsl",
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"main", "ps_5_0",
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
		0,
		&psBlob, &errorBlob);
	//エラーなら
	if (FAILED(result)) {
		//errorBlobから内容をstring型にコピー
		std::string error;
		error.resize(errorBlob->GetBufferSize());

		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			error.begin());
		error += "\n";
		//エラー内容を出力ウインドウに表示
		OutputDebugStringA(error.c_str());
		assert(0);
	}
	//頂点レイアウト
	D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
		{
		"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,
		D3D12_APPEND_ALIGNED_ELEMENT,
		D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0,
		},//vyz座標(一行で書いたほうが見やすい)
		{
		"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,
		D3D12_APPEND_ALIGNED_ELEMENT,
		D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0,
		},//uv座標(一行で書いたほうが見やすい)
	};

	//グラフィックスパイプライン設定
	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc{};
	//シェーダーの設定
	pipelineDesc.VS.pShaderBytecode = vsBlob->GetBufferPointer();
	pipelineDesc.VS.BytecodeLength = vsBlob->GetBufferSize();
	pipelineDesc.PS.pShaderBytecode = psBlob->GetBufferPointer();
	pipelineDesc.PS.BytecodeLength = psBlob->GetBufferSize();
	//サンプルマスクの設定
	pipelineDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;
	//ラスタライザの設定
	pipelineDesc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;//カリングしない
	pipelineDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;//ポリゴン内塗りつぶし
	pipelineDesc.RasterizerState.DepthClipEnable = true;//深度グリッピングを有効に

	// デスクリプタレンジ
	CD3DX12_DESCRIPTOR_RANGE descRangeSRV0;
	descRangeSRV0.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0); // t0 レジスタ

	CD3DX12_DESCRIPTOR_RANGE descRangeSRV1;
	descRangeSRV1.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 1); // t1 レジスタ
	// ルートパラメータ
	CD3DX12_ROOT_PARAMETER rootparams[3] = {};
	rootparams[0].InitAsConstantBufferView(0, 0, D3D12_SHADER_VISIBILITY_ALL);
	rootparams[1].InitAsDescriptorTable(1, &descRangeSRV0, D3D12_SHADER_VISIBILITY_ALL);
	rootparams[2].InitAsDescriptorTable(1, &descRangeSRV1, D3D12_SHADER_VISIBILITY_ALL);

	// スタティックサンプラー
	CD3DX12_STATIC_SAMPLER_DESC samplerDesc =
		CD3DX12_STATIC_SAMPLER_DESC(0, D3D12_FILTER_MIN_MAG_MIP_LINEAR); // s0 レジスタ
	samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
	samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
	samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;

	// ルートシグネチャの設定
	CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC rootSignatureDesc;
	rootSignatureDesc.Init_1_0(
		_countof(rootparams), rootparams, 1, &samplerDesc,
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	Microsoft::WRL::ComPtr<ID3DBlob> rootSigBlob;
	// バージョン自動判定のシリアライズ
	result = D3DX12SerializeVersionedRootSignature(
		&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &rootSigBlob, &errorBlob);
	assert(SUCCEEDED(result));
	// ルートシグネチャの生成
	result = device_->CreateRootSignature(
		0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(),
		IID_PPV_ARGS(&rootSignature));
	assert(SUCCEEDED(result));


	//レンダーターゲットのブレンド設定
	D3D12_RENDER_TARGET_BLEND_DESC& blenddesc = pipelineDesc.BlendState.RenderTarget[0];
	blenddesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;//RGBA全てのチャンネルを描画
	blenddesc.BlendEnable = true;//ブレンドを有効にする
	blenddesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;//加算
	blenddesc.SrcBlendAlpha = D3D12_BLEND_ONE;//ソースの値を100%使う
	blenddesc.DestBlendAlpha = D3D12_BLEND_ZERO;//デストの値を0%使う
	////加算合成
	//blenddesc.BlendOp = D3D12_BLEND_OP_ADD;//加算
	//blenddesc.SrcBlend = D3D12_BLEND_ONE;//ソースの値を100%使う
	//blenddesc.DestBlend = D3D12_BLEND_ONE;//デストの値を100%使う
	////減算合成
	//blenddesc.BlendOp = D3D12_BLEND_OP_REV_SUBTRACT;//デストからソースを減算
	//blenddesc.SrcBlend = D3D12_BLEND_ONE;//ソースの値を100%使う
	//blenddesc.DestBlend = D3D12_BLEND_ONE;//デストの値を100%使う
	////色反転
	//blenddesc.BlendOp = D3D12_BLEND_OP_ADD;//加算
	//blenddesc.SrcBlend = D3D12_BLEND_INV_DEST_COLOR;//1.0f-デストカラーの値
	//blenddesc.DestBlend = D3D12_BLEND_ZERO;//使わない
	//半透明合成
	blenddesc.BlendOp = D3D12_BLEND_OP_ADD;//加算
	blenddesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;//ソースのアルファ値
	blenddesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;//1.0f-ソースのアルファ値
	////ブレンドステート
	//pipelineDesc.BlendState.RenderTarget[0].RenderTargetWriteMask
	//	= D3D12_COLOR_WRITE_ENABLE_ALL;//RBGAすべてのチャンネルを描画
	//頂点レイアウトの設定
	pipelineDesc.InputLayout.pInputElementDescs = inputLayout;
	pipelineDesc.InputLayout.NumElements = _countof(inputLayout);
	//図形の形状設定
	pipelineDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	//その他の設定
	pipelineDesc.NumRenderTargets = 1;//描画対象は一つ
	pipelineDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;//0～255指定のRGBA
	pipelineDesc.SampleDesc.Count = 1; //1ピクセルにつき一回サンプリング


	// グラフィックスパイプラインの生成
	pipelineDesc.pRootSignature = rootSignature.Get();
	result = device_->CreateGraphicsPipelineState(&pipelineDesc, IID_PPV_ARGS(&pipelineState));
	assert(SUCCEEDED(result));
}

void PostEffect::PreDrawScene(ID3D12GraphicsCommandList* cmdList)
{
	commandList = cmdList;

	for (int i = 0; i < 2; i++) {
		CD3DX12_RESOURCE_BARRIER resouceBar = CD3DX12_RESOURCE_BARRIER::Transition(texBuff[i].Get(),
			D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
			D3D12_RESOURCE_STATE_RENDER_TARGET);

		//リソースバリアを変更(シェーダーリソース→描画可能)
		commandList->ResourceBarrier(1,
			&resouceBar);
	}

	//レンダーターゲットビュー用のディスクリプタヒープのハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHs[2];
	for (int i = 0; i < 2; i++) {
		rtvHs[i] = CD3DX12_CPU_DESCRIPTOR_HANDLE(descHeapRTV->GetCPUDescriptorHandleForHeapStart(), i,
			device_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
	}

	//深度ステンシルビュー用デスクリプタヒープのハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE dsvH = descHeapDSV->GetCPUDescriptorHandleForHeapStart();
	//レンダーターゲットをセット
	commandList->OMSetRenderTargets(2, rtvHs, false, &dsvH);

	CD3DX12_VIEWPORT viewPorts[2];
	CD3DX12_RECT scissorRects[2];

	for (int i = 0; i < 2; i++) {
		viewPorts[i] = CD3DX12_VIEWPORT(0.0f, 0.0f, WinApp::window_width, WinApp::window_height);
		scissorRects[i] = CD3DX12_RECT(0, 0, WinApp::window_width, WinApp::window_height);
	}

	//ビューポートの設定
	commandList->RSSetViewports(2, viewPorts);
	//シザリング矩形の設定
	commandList->RSSetScissorRects(2, scissorRects);
	for (int i = 0; i < 2; i++) {
		//全画面のクリア
		commandList->ClearRenderTargetView(rtvHs[i], clearColor, 0, nullptr);
	}
	//深度バッファのクリア
	commandList->ClearDepthStencilView(dsvH, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
}

void PostEffect::Draw(ID3D12GraphicsCommandList* cmdList)
{
	commandList = cmdList;

	//パイプラインステートとルートシグネチャの設定コマンド
	commandList->SetPipelineState(pipelineState.Get());
	commandList->SetGraphicsRootSignature(rootSignature.Get());

	//SRVヒープの設定コマンド
	ID3D12DescriptorHeap* ppHeaps[] = { descHeapSRV.Get() };
	commandList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
	//プリミティブ形状の設定コマンド
	commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	//頂点バッファビューの設定コマンド
	commandList->IASetVertexBuffers(0, 1, &vbView);

	//画像描画
	//SRVヒープの先頭ハンドルを取得（SRVを指しているはず）
	commandList->SetGraphicsRootDescriptorTable(1, CD3DX12_GPU_DESCRIPTOR_HANDLE(descHeapSRV->GetGPUDescriptorHandleForHeapStart(), 0,
		device_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV)));

	commandList->SetGraphicsRootDescriptorTable(2, CD3DX12_GPU_DESCRIPTOR_HANDLE(descHeapSRV->GetGPUDescriptorHandleForHeapStart(), 1,
		device_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV)));

	commandList->SetGraphicsRootConstantBufferView(0, constDataBuff_->GetGPUVirtualAddress());

	//描画コマンド
	commandList->DrawInstanced(_countof(vertices), 1, 0, 0);//すべての頂点を使って描画
}

void PostEffect::PostDrawScene()
{
	for (int i = 0; i < 2; i++) {
		CD3DX12_RESOURCE_BARRIER RESOURCE_BARRIER = CD3DX12_RESOURCE_BARRIER::Transition(texBuff[i].Get(),
			D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);

		commandList->ResourceBarrier(1, &RESOURCE_BARRIER);
	}
}

void PostEffect::SetShadeNumber(int SetShadeNumber)
{
	dataMap->shadeNumber = SetShadeNumber;
}

void PostEffect::SetKernelSize(int range) {

	dataMap->kernelSize = range;

}

void PostEffect::SetRadialBlur(Vector2 center, float intensity, int sample)
{
	dataMap->center = center;
	dataMap->intensity = intensity;
	dataMap->samples = sample;
}