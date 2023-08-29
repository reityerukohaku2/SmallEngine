#include "Direct3D.h"

#include <windows.h>

void Direct3D::CreateInstance() 
{
	// インスタンスを削除してから生成
	DeleteInstance();

	s_instance = new Direct3D();

}

void Direct3D::DeleteInstance() 
{
	// インスタンスが存在する場合、削除
	if (s_instance != nullptr)
	{
		delete s_instance;
		s_instance = nullptr;
	}
}

Direct3D& Direct3D::GetInstance() {
	// インスタンスが存在しない場合、生成
	if (s_instance == nullptr) {
		CreateInstance();
	}
	return *s_instance;
}

/// <summary>
/// 初期化メソッド
/// </summary>
/// <param name="hWnd">ウィンドウハンドラ</param>
/// <returns>初期化成功時にtrue、失敗時にfalse</returns>
bool Direct3D::Initialize(HWND hWnd)
{
	//デバッグレイヤー作成
	UINT dxgiFactoryFlags = 0;
#if defined(_DEBUG)	
	
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(debugController.GetAddressOf()))))
	{
		debugController->EnableDebugLayer();
	}
#endif

	//=====================================================
	//デバイス生成(主にリソース作成時に使用するオブジェクト)
	//=====================================================
	UINT creationFlags = 0;

	// デバイスを作成
	{
		D3D_FEATURE_LEVEL futureLevel = D3D_FEATURE_LEVEL_12_0;
		if (FAILED(D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(m_device.GetAddressOf())))) {
			return false;
		}
	}

	// コマンドキューの作成
	{
		D3D12_COMMAND_QUEUE_DESC queueDesc = {};
		queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		if (FAILED(m_device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(m_commandQueue.GetAddressOf())))) {
			return false;
		}
	}

	// コマンドアロケータとコマンドリストの作成
	{
		if (FAILED(m_device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(m_commandAllocator.GetAddressOf())))) {
			return false;
		}
		if (FAILED(m_device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_commandAllocator.Get(), NULL, IID_PPV_ARGS(m_commandList.GetAddressOf())))) {
			return false;
		}
	}

	// スワップチェインの作成
	{
		DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
		swapChainDesc.BufferCount = kFrameCount;
		swapChainDesc.Width = kWindowWidth;
		swapChainDesc.Height = kWindowHeight;
		swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		swapChainDesc.SampleDesc.Count = 1;
		IDXGIFactory4* factory;
		CreateDXGIFactory1(IID_PPV_ARGS(&factory));
		factory->CreateSwapChainForHwnd(m_commandQueue.Get(), hWnd, &swapChainDesc, NULL, NULL, (IDXGISwapChain1**)m_swapChain.GetAddressOf());
	}

	// レンダーターゲットの作成
	{
		//レンダーターゲットビューのヒープ作成
		D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
		rtvHeapDesc.NumDescriptors = kFrameCount;
		rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		m_device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&m_rtvHeap));

		// レンダーターゲットビュー作成
		CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(m_rtvHeap->GetCPUDescriptorHandleForHeapStart());
		// 全フレーム分作成する
		for (UINT n = 0; n < kFrameCount; n++)
		{
			m_swapChain->GetBuffer(n, IID_PPV_ARGS(m_renderTargets[n].GetAddressOf()));
			m_device->CreateRenderTargetView(m_renderTargets[n].Get(), NULL, rtvHandle);
			rtvHandle.Offset(1, m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
		}
	}
	
	// フェンスの作成
	{
		m_fenceValue = 0;
		if (FAILED(m_device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(m_fence.GetAddressOf())))) {
			return false;
		}
	}

	return true;
}

/// <summary>
/// レンダリングを行う
/// </summary>
void Direct3D::Render() {
	// バックバッファが現在何枚目かを取得
	UINT backBufferIndex = m_swapChain->GetCurrentBackBufferIndex();

	// コマンドリストに書き込む前にコマンドアロケーターをリセットする
	m_commandAllocator->Reset();

	// コマンドリストをリセットする
	m_commandList->Reset(m_commandAllocator.Get(), 0);


	// ================================================
	// ここからコマンドリストにコマンドを書き込んでいく
	// ================================================
	
	// バックバッファのトランジションをレンダーターゲットモードにする
	D3D12_RESOURCE_BARRIER render_target_mode_barrier = CD3DX12_RESOURCE_BARRIER::Transition(m_renderTargets[backBufferIndex].Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
	m_commandList->ResourceBarrier(1, &render_target_mode_barrier);

	// バックバッファをレンダーターゲットにセット
	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(m_rtvHeap->GetCPUDescriptorHandleForHeapStart(), backBufferIndex, m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
	m_commandList->OMSetRenderTargets(1, &rtvHandle, false, NULL);

	// ビューポートをセット
	CD3DX12_VIEWPORT viewport = CD3DX12_VIEWPORT(0.0f, 0.0f, (float)kWindowWidth, (float)kWindowHeight);
	CD3DX12_RECT scissorRect = CD3DX12_RECT(0, 0, kWindowWidth, kWindowHeight);
	m_commandList->RSSetViewports(1, &viewport);
	m_commandList->RSSetScissorRects(1, &scissorRect);

	// 画面クリア
	const float clearColor[] = { 0.0f, 0.0f, 1.0f, 1.0f };
	m_commandList->ClearRenderTargetView(rtvHandle, clearColor, 0, NULL);

	// バックバッファのトランジションをPresentモードにする
	D3D12_RESOURCE_BARRIER present_mode_barrier = CD3DX12_RESOURCE_BARRIER::Transition(m_renderTargets[backBufferIndex].Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
	m_commandList->ResourceBarrier(1, &present_mode_barrier);

	// コマンドの書き込みはここで終わり、Closeする
	m_commandList->Close();

	// コマンドリストの実行
	ID3D12CommandList* ppCommandLists[] = { m_commandList.Get() };
	m_commandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

	//バックバッファをフロントバッファに切り替えてシーンをモニターに表示
	m_swapChain->Present(1, 0);

	//GPUの処理が完了するまで待つ
	WaitGpu();
}

/// <summary>
/// GPUの処理が完了するまで待つ
/// </summary>
void Direct3D::WaitGpu() {
	//GPUサイドが全て完了したときにGPUサイドから返ってくる値（フェンス値）をセット
	m_commandQueue->Signal(m_fence.Get(), m_fenceValue);

	//上でセットしたシグナルがGPUから帰ってくるまでストール（この行で待機）
	do
	{
		//GPUの完了を待つ間、ここで何か有意義な事（CPU作業）をやるほど効率が上がる

	} while (m_fence->GetCompletedValue() < m_fenceValue);

	// フェンス値を更新
	// 前回より大きな値であればどんな値でもいい
	m_fenceValue++;
}