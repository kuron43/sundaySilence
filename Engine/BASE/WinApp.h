#pragma once
#pragma warning(push)
#pragma warning(disable: 4819)
#include <Windows.h>

#pragma warning(pop)

//WindowsAPI
class WinApp
{
public:
	static LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	//getter
	HWND GetHwnd() const { return hwnd; }

	HINSTANCE GetHInstance() const { return w.hInstance; }

	bool ProcessMessage();

	// ウィンドウ横幅
	static const int window_width = 1280;
	// ウィンドウ縦幅
	static const int window_height = 720;

	// シングルトンインスタンスの取得
	static WinApp* GetInstance();
	float aspectRatio;

public: //メンバ関数
	//初期化
	void Initialize();

	//更新
	void Update();

	//終了
	void Finalize();
private:
	//ウィンドウハンドル
	HWND hwnd = nullptr;

	//ウィンドウクラスの設定
	WNDCLASSEX w{};

	static WinApp* winApp_;

};