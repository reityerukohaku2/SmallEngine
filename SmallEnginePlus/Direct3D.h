#pragma once

// Direct3Dのライブラリを使用できるようにする
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#include <d3d11.h>
#include <DirectXMath.h>

// ComPtrを使用できるようにする
#include <wrl/client.h>
using Microsoft::WRL::ComPtr;

//=========================================
// Direct3Dクラス
//=========================================
class Direct3D
{
public:
	/// <summary>
	/// Direct3Dを初期化し、使用できるようにする
	/// </summary>
	/// <param name="hWnd">ウィンドウハンドル</param>
	/// <param name="width">画面の幅</param>
	/// <param name="height">画面の高さ</param>
	/// <returns>成功時にtrue、失敗時にfalseを返す</returns>
	bool Initialize(HWND hWnd, int width, int height);

	// シングルトン実装用
	/// <summary>
	/// インスタンス生成
	/// </summary>
	static void CreateInstance();

	/// <summary>
	/// インスタンス削除
	/// </summary>
	static void DeleteInstance();

	/// <summary>
	/// インスタンス取得
	/// </summary>
	/// <returns></returns>
	static Direct3D& GetInstance();

	/// <summary>
	/// デバイスコンテキストの取得
	/// </summary>
	/// <returns>デバイスコンテキスト</returns>
	ComPtr<ID3D11DeviceContext> GetDeviceContext();

	/// <summary>
	/// バックバッファービューの取得
	/// </summary>
	/// <returns>バックバッファービュー</returns>
	ComPtr<ID3D11RenderTargetView> GetBackBufferView();

	/// <summary>
	/// スワップチェインの取得
	/// </summary>
	/// <returns>スワップチェイン</returns>
	ComPtr<IDXGISwapChain> GetSwapChain();

private:
	// Direct3Dデバイス
	ComPtr<ID3D11Device>		m_device;
	// Direct3Dデバイスコンテキスト
	ComPtr<ID3D11DeviceContext>	m_deviceContext;
	// スワップチェイン
	ComPtr<IDXGISwapChain>		m_swapChain;
	// バックバッファーのRTビュー
	ComPtr<ID3D11RenderTargetView> m_backBufferView;

	// 唯一のインスタンス用のポインタ
	static inline Direct3D* s_instance;

	Direct3D() {}

};

// Direct3Dの唯一のインスタンスを簡単に取得するためのマクロ
#define D3D Direct3D::GetInstance()