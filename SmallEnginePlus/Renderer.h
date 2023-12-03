#pragma once
#include "pch.h"
#include "ResourceFactory.h"
#include "VertexBuffer.h"
#include "GeometryCollection.h"

#define kFrameCount 3  //画面バッファ数
#define kWindowWidth 1280		//ウィンドウ幅
#define kWindowHeight 720		//ウィンドウ高さ

class Renderer
{
public:
	Renderer (GeometryCollection geometries, HWND hWnd);
	Renderer ();

	void Render ();

private:
	// ******************************************
	// 普通のメソッド
	// ******************************************

	/// <summary>
	/// GPUの処理が完了するまで待つ
	/// </summary>
	void WaitGpu ();

	// ******************************************
	// 初期化用メソッド
	// ******************************************

	void CreateCommandQueue();
	void CreateCommandList ();
	void CreateSwapChain();
	void CreateRenderTarget ();
	void CreateFence ();
	void CreateConstantBuffer ();
	void CreateRootSignature();
	void CreatePilelineState ();

	// ******************************************
	// メンバ変数
	// ******************************************

	//コンスタントバッファ
	struct Cbuffer
	{
		XMMATRIX wvp;
		Cbuffer ()
		{
			ZeroMemory (this, sizeof (Cbuffer));
		}
	};

	/// <summary>
	/// ウィンドウハンドラ
	/// </summary>
	HWND m_hWnd;

	/// <summary>
	/// Direct3Dデバイス
	/// </summary>
	com_ptr<ID3D12Device>				m_device;

	/// <summary>
	/// 頂点バッファ
	/// </summary>
	com_ptr<VertexBuffer>               m_vertexBuffer;

	/// <summary>
	/// 頂点バッファビュー
	/// </summary>
	D3D12_VERTEX_BUFFER_VIEW            m_vertexBufferView;

	/// <summary>
	/// コンスタントバッファ
	/// </summary>
	com_ptr <ID3D12Resource> m_constantBuffer;
	com_ptr <ID3D12DescriptorHeap> m_descHeap;

	/// <summary>
	/// コマンドアロケーター
	/// </summary>
	com_ptr<ID3D12CommandAllocator>		m_commandAllocator;

	/// <summary>
	/// コマンドリスト
	/// </summary>
	com_ptr<ID3D12GraphicsCommandList>	m_commandList;

	/// <summary>
	/// コマンドキュー
	/// </summary>
	com_ptr<ID3D12CommandQueue>			m_commandQueue;

	/// <summary>
	/// スワップチェイン
	/// </summary>
	com_ptr<IDXGISwapChain3>			m_swapChain;

	/// <summary>
	/// レンダーターゲットビュー
	/// </summary>
	vector<com_ptr<ID3D12Resource>>	    m_renderTargets;
	com_ptr <ID3D12DescriptorHeap>		m_rtvHeap;

	/// <summary>
	/// パイプラインステートオブジェクト
	/// </summary>
	com_ptr <ID3D12PipelineState>		m_pipelineState;

	/// <summary>
	/// ルートシグネチャ
	/// </summary>
	com_ptr <ID3D12RootSignature>		m_rootSignature;

	/// <summary>
	/// フェンス
	/// </summary>
	com_ptr<ID3D12Fence>					m_fence;


	/// <summary>
	/// フェンス値を格納する場所
	/// </summary>
	UINT64	m_fenceValue;
	
	/// <summary>
	/// シェーダー
	/// </summary>
	ID3DBlob* vertexShader;
	ID3DBlob* pixelShader;

};

