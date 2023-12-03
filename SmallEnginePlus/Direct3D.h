#pragma once
#include "pch.h"
// Direct3Dのライブラリを使用できるようにする
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"user32.lib") 
#pragma comment(lib,"Gdi32.lib") 
#pragma comment(lib,"Ole32.lib") 
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"winmm.lib") 

#include "d3dx12.h"
#include "GeometryCollection.h"
#include "Renderer.h"

using winrt::com_ptr;
using namespace std;
using namespace DirectX;

#define kWindowWidth 1280		//ウィンドウ幅
#define kWindowHeight 720		//ウィンドウ高さ
#define kAppName "初期化"
#define kFrameCount 3			//画面バッファ数
#define ARRAY_LENGTH(array) (sizeof(array) / sizeof(array[0]))

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

	/// <summary>
	/// モデルの初期化
	/// </summary>
	/// <returns>成功したらSUCCEEDED</returns>
	HRESULT InitModels ();

private:

	Renderer m_renderer;

	/// <summary>
	/// デバッグコントローラ
	/// </summary>
	com_ptr<ID3D12Debug>					debugController;

	/// <summary>
	/// コマンドアロケーター
	/// </summary>
	com_ptr<ID3D12CommandAllocator>		m_commandAllocator;



	/// <summary>
	/// コマンドキュー
	/// </summary>
	com_ptr<ID3D12CommandQueue>			m_commandQueue;

	/// <summary>
	/// スワップチェイン
	/// </summary>
	com_ptr<IDXGISwapChain3>				m_swapChain;

	/// <summary>
	/// レンダーターゲットビュー
	/// </summary>
	com_ptr <ID3D12Resource>				m_renderTargets[kFrameCount];
	com_ptr <ID3D12DescriptorHeap>		m_rtvHeap;



	/// <summary>
	/// 頂点バッファビュー
	/// </summary>
	D3D12_VERTEX_BUFFER_VIEW			m_vertexBufferView;

	/// <summary>
	/// インデックスバッファ
	/// </summary>
	com_ptr <ID3D12Resource>				m_indexBuffer;
	D3D12_INDEX_BUFFER_VIEW				m_indexBufferView;

		
	/// <summary>
	/// パイプラインステートオブジェクト
	/// </summary>
	com_ptr <ID3D12PipelineState>		m_pipelineState;

	GeometryCollection m_geometries;

	// 唯一のインスタンス用のポインタ
	static inline Direct3D* s_instance;

	Direct3D(){}

	/// <summary>
	/// メモリ領域の開放
	/// </summary>
	void DestroyD3D ();
};

// 
// の唯一のインスタンスを簡単に取得するためのマクロ
#define D3D Direct3D::GetInstance()