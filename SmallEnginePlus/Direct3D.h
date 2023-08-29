#pragma once

// Direct3Dのライブラリを使用できるようにする
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

#include <d3d12.h>
#include "d3dx12.h"
#include <dxgi1_4.h>
#include <DirectXMath.h>

// ComPtrを使用できるようにする
#include <wrl/client.h>
using Microsoft::WRL::ComPtr;

#define kWindowWidth 1280		//ウィンドウ幅
#define kWindowHeight 720		//ウィンドウ高さ
#define kAppName "初期化"
#define kFrameCount 3			//画面バッファ数

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
	bool Initialize(HWND hWnd);

	/// <summary>
	/// レンダリングを行う
	/// </summary>
	void Render();

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

private:
	/// <summary>
	/// デバッグコントローラ
	/// </summary>
	ComPtr<ID3D12Debug>					debugController;

	/// <summary>
	/// Direct3Dデバイス
	/// </summary>
	ComPtr<ID3D12Device>				m_device;

	/// <summary>
	/// コマンドアロケーター
	/// </summary>
	ComPtr<ID3D12CommandAllocator>		m_commandAllocator;

	/// <summary>
	/// コマンドリスト
	/// </summary>
	ComPtr<ID3D12GraphicsCommandList>	m_commandList;

	/// <summary>
	/// コマンドキュー
	/// </summary>
	ComPtr<ID3D12CommandQueue>			m_commandQueue;

	/// <summary>
	/// スワップチェイン
	/// </summary>
	ComPtr<IDXGISwapChain3>				m_swapChain;

	/// <summary>
	/// レンダーターゲットビューのヒープ
	/// </summary>
	ComPtr<ID3D12DescriptorHeap>		m_rtvHeap;

	/// <summary>
	/// レンダーターゲットビュー
	/// </summary>
	ComPtr <ID3D12Resource>				m_renderTargets[kFrameCount];

	/// <summary>
	/// フェンス
	/// </summary>
	ComPtr<ID3D12Fence>					m_fence;

	/// <summary>
	/// フェンス値を格納する場所
	/// </summary>
	UINT64	m_fenceValue;

	// 唯一のインスタンス用のポインタ
	static inline Direct3D* s_instance;

	Direct3D() {}

	/// <summary>
	/// GPUの処理が完了するまで待つ
	/// </summary>
	void WaitGpu();
};

// Direct3Dの唯一のインスタンスを簡単に取得するためのマクロ
#define D3D Direct3D::GetInstance()