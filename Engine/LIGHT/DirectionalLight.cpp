#include "DirectionalLight.h"

using namespace DirectX;

/// <summary>
/// 静的メンバ変数の実体
/// </summary>
ID3D12Device* DirectionalLight::device = nullptr;

void DirectionalLight::StaticInitialize(ID3D12Device* device)
{
	//再初期化チェック
	assert(!DirectionalLight::device);
	//静的メンバ変数のセット
	DirectionalLight::device = device;
}

bool DirectionalLight::Initialize()
{
	// ヒープ設定
	D3D12_HEAP_PROPERTIES cbHeapProp{};
	cbHeapProp.Type = D3D12_HEAP_TYPE_UPLOAD;                   // GPUへの転送用
	// リソース設定
	D3D12_RESOURCE_DESC cbResourceDesc{};
	cbResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	cbResourceDesc.Width = (sizeof(ConstBufferData) + 0xff) & ~0xff;   // 256バイトアラインメント
	cbResourceDesc.Height = 1;
	cbResourceDesc.DepthOrArraySize = 1;
	cbResourceDesc.MipLevels = 1;
	cbResourceDesc.SampleDesc.Count = 1;
	cbResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	/*ID3D12Resource* constBuff = nullptr;*/
	// 定数バッファの生成
	result = device->CreateCommittedResource(
		&cbHeapProp, // ヒープ設定
		D3D12_HEAP_FLAG_NONE,
		&cbResourceDesc, // リソース設定
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuff));
	assert(SUCCEEDED(result));

	//定数バッファへデータ転送
	TransferConstBuffer();

	return true;
}

void DirectionalLight::TransferConstBuffer()
{
	//定数バッファへデータ転送
	ConstBufferData* constMap = nullptr;
	result = constBuff->Map(0, nullptr, (void**)&constMap);
	if (SUCCEEDED(result)) {
		constMap->lightv = -lightdir;
		constMap->lightcolor = lightcolor;
		constBuff->Unmap(0, nullptr);
	}
}

void DirectionalLight::SetLightDir(const Vector4& lightdir)
{
	//正規化してセット
	this->lightdir = lightdir.Normalization();
	dirty = true;
}

void DirectionalLight::SetLightColor(const Vector3& lightcolor)
{
	this->lightcolor = lightcolor;
	dirty = true;
}

void DirectionalLight::Update()
{
	//値の更新があった時だけ定数バッファに転送する
	if (dirty) {
		TransferConstBuffer();
		dirty = false;
	}
}

void DirectionalLight::Draw(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndex)
{
	//定数バッファビューをセット
	cmdList->SetGraphicsRootConstantBufferView(rootParameterIndex,
		constBuff->GetGPUVirtualAddress());
}

DirectionalLight* DirectionalLight::Create()
{
	//3Dオブジェクトのインスタンスを生成
	DirectionalLight* instance = new DirectionalLight();
	if (instance == nullptr) {
		return nullptr;
	}

	// 初期化
	if (!instance->Initialize()) {
		delete instance;
		assert(0);
		return nullptr;
	}

	return instance;
}

