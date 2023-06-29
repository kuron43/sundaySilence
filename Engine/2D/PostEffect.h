#pragma once
#include"DirectXCommon.h"
#include "WinApp.h"
#include <DirectXTex.h>
#include <array>
#include <string>

#include "Affin.h"

class PostEffect
{
protected: // エイリアス
    // Microsoft::WRL::を省略
    template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
    // DirectX::を省略

public:
    /// <summary>
    /// 頂点データ構造体
    /// </summary>
    struct VertexPosUv {
        Vector3 pos; // xyz座標
        Vector2 uv;  // uv座標
    };

    /// <summary>
    /// 定数バッファ用データ構造体
    /// </summary>
    struct ConstBufferData {
        Vector4 color; // 色 (RGBA)
        Matrix4 mat;   // ３Ｄ変換行列
    };

    //GPU
    struct SendDataGPU {
        int shadeNumber;	//SHADER番号
        int kernelSize;		// ぼかし度
		Vector2 center;		// 中心
        float intensity;	// ブラーの広がりの強さ
        int samples;		// サンプル回数
    };

    //デフォルトテクスチャ格納ディレクトリ
    std::string kDefaultTextureDirectoryPath = "Resources/";
    HRESULT result;
public:

    static void Initialize(DirectXCommon* dxCommon);

    static void Finalize();

    /// <summary>
    /// パイプライン生成
    /// </summary>
    static void CreatGraphicsPipeline();

    /// <summary>
    /// シーン描画前処理
    /// </summary>
    /// <param name="cmdList">コマンドリスト</param>
    static void PreDrawScene(ID3D12GraphicsCommandList* cmdList);

    /// <summary>
    /// シーン描画処理
    /// </summary>
    static void Draw(ID3D12GraphicsCommandList* cmdList);

    /// <summary>
    /// シーン描画後処理
    /// </summary>
    /// <param name="cmdList">コマンド処理</param>
    static void PostDrawScene();

    static void SetShadeNumber(int SetShadeNumber);

    static void SetKernelSize(int range);

    static void SetRadialBlur(Vector2 senter, float intensity, int sample);

private://静的メンバ変数
    static const float clearColor[4];

    static ID3D12Device* device_;

    static ID3D12GraphicsCommandList* commandList;

    static VertexPosUv vertices[4];

    static VertexPosUv* vertMap;

    static ComPtr<ID3D12Resource> vertBuff;	//頂点バッファ

    //頂点バッファビューの作成
    static D3D12_VERTEX_BUFFER_VIEW vbView;
    static ComPtr<ID3D12Resource> texBuff[2];

    static ComPtr<ID3D12DescriptorHeap> descHeapSRV;
    //深度バッファ
    static ComPtr<ID3D12Resource> depthBuff;
    //RTV用のデスクリプタヒープ
    static ComPtr<ID3D12DescriptorHeap> descHeapRTV;
    //DSV用のデスクリプタヒープ
    static ComPtr<ID3D12DescriptorHeap> descHeapDSV;

    static ComPtr<ID3D12PipelineState> pipelineState;
    static ComPtr<ID3D12RootSignature> rootSignature;
private:
    // 定数バッファ
    static ComPtr<ID3D12Resource> constDataBuff_;
    // マッピング済みアドレス
    static SendDataGPU* dataMap;
};

