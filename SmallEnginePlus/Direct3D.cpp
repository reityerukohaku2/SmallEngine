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
	
	winrt::check_hresult(D3D12GetDebugInterface(__uuidof( debugController), debugController.put_void()));
	debugController->EnableDebugLayer();

#endif

	//=====================================================
	//デバイス生成(主にリソース作成時に使用するオブジェクト)
	//=====================================================
	UINT creationFlags = 0;

	// デバイスを作成
	{
		D3D_FEATURE_LEVEL futureLevel = D3D_FEATURE_LEVEL_12_0;
		winrt::check_hresult (D3D12CreateDevice (nullptr, D3D_FEATURE_LEVEL_12_0, __uuidof(m_device), m_device.put_void ()));
	}

	// コマンドキューの作成
	{
		D3D12_COMMAND_QUEUE_DESC queueDesc = {};
		queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		winrt::check_hresult (m_device->CreateCommandQueue (&queueDesc, __uuidof(m_commandQueue), m_commandQueue.put_void ()));
	}

	// コマンドアロケータとコマンドリストの作成
	{
		winrt::check_hresult (m_device->CreateCommandAllocator (D3D12_COMMAND_LIST_TYPE_DIRECT, __uuidof(m_commandAllocator), m_commandAllocator.put_void()));
		winrt::check_hresult (m_device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_commandAllocator.get(), NULL, __uuidof(m_commandList), m_commandList.put_void()));
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
		com_ptr<IDXGIFactory4> factory;
		CreateDXGIFactory1(__uuidof(factory), factory.put_void());
		factory->CreateSwapChainForHwnd(m_commandQueue.get(), hWnd, &swapChainDesc, NULL, NULL, (IDXGISwapChain1**)m_swapChain.put());
	}

	//コンスタントバッファ作成
	{
		//コンスタントバッファ作成
		UINT CBSize = D3D12_CONSTANT_BUFFER_DATA_PLACEMENT_ALIGNMENT;
		CD3DX12_HEAP_PROPERTIES heap_properties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
		CD3DX12_RESOURCE_DESC desc = CD3DX12_RESOURCE_DESC::Buffer (CBSize);
		m_device->CreateCommittedResource(
			&heap_properties,
			D3D12_HEAP_FLAG_NONE,
			&desc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			__uuidof(m_constantBuffer), m_constantBuffer.put_void());

		//コンスタントバッファビューのヒープ作成
		D3D12_DESCRIPTOR_HEAP_DESC cbvHeapDesc = {};
		cbvHeapDesc.NumDescriptors = 1;
		cbvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
		cbvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
		m_device->CreateDescriptorHeap(&cbvHeapDesc, __uuidof(m_descHeap), m_descHeap.put_void());

		//コンスタントバッファビュー作成
		D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
		cbvDesc.BufferLocation = m_constantBuffer->GetGPUVirtualAddress();
		cbvDesc.SizeInBytes = CBSize;
		D3D12_CPU_DESCRIPTOR_HANDLE cHandle = m_descHeap->GetCPUDescriptorHandleForHeapStart();
		m_device->CreateConstantBufferView(&cbvDesc, cHandle);
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
			m_swapChain->GetBuffer(n, __uuidof(m_renderTargets[n]), m_renderTargets[n].put_void());
			m_device->CreateRenderTargetView(m_renderTargets[n].get(), NULL, rtvHandle);
			rtvHandle.Offset(1, m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
		}
	}
	
	// フェンスの作成
	{
		if (FAILED(m_device->CreateFence(0, D3D12_FENCE_FLAG_NONE, __uuidof(m_fence), m_fence.put_void()))) {
			return false;
		}
		m_fenceValue = 1;
	}

	//ルートシグネチャ作成
	{
		//コンスタントバッファビューのテーブルをルートに作成
		CD3DX12_DESCRIPTOR_RANGE1 ranges[1];
		CD3DX12_ROOT_PARAMETER1 rootParameters[1];
		ranges[0].Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 0, 0, D3D12_DESCRIPTOR_RANGE_FLAG_DATA_STATIC);
		rootParameters[0].InitAsDescriptorTable(1, &ranges[0], D3D12_SHADER_VISIBILITY_ALL);
		CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC rootSignatureDesc;
		rootSignatureDesc.Init_1_1(_countof(rootParameters), rootParameters,
			0, NULL,
			D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT
		);
		ID3DBlob* signature;
		ID3DBlob* error;
		D3DX12SerializeVersionedRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &error);
		m_device->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), __uuidof(m_rootSignature), m_rootSignature.put_void());
	}

	//シェーダー作成
	ID3DBlob* vertexShader;
	ID3DBlob* pixelShader;
	{
		D3DCompileFromFile (L"Simple.hlsl", NULL, NULL, "VS", "vs_5_1", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &vertexShader, nullptr);
		D3DCompileFromFile (L"Simple.hlsl", NULL, NULL, "PS", "ps_5_1", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &pixelShader, nullptr);
	}

	//頂点レイアウト作成
	D3D12_INPUT_ELEMENT_DESC inputElementDescs[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
	};

	//パイプラインステートオブジェクト作成
	{
		D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
		psoDesc.InputLayout = { inputElementDescs, _countof(inputElementDescs) };
		psoDesc.pRootSignature = m_rootSignature.get();
		psoDesc.VS = CD3DX12_SHADER_BYTECODE(vertexShader);
		psoDesc.PS = CD3DX12_SHADER_BYTECODE(pixelShader);
		psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
		psoDesc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;
		psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
		psoDesc.DepthStencilState.DepthEnable = false;
		psoDesc.DepthStencilState.StencilEnable = false;
		psoDesc.SampleMask = UINT_MAX;
		psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		psoDesc.NumRenderTargets = 1;
		psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
		psoDesc.SampleDesc.Count = 1;
		m_device->CreateGraphicsPipelineState(&psoDesc, __uuidof(m_pipelineState), m_pipelineState.put_void());
	}

	return true;
}

/// <summary>
/// モデルの初期化
/// </summary>
/// <returns>成功したらSUCCEEDED</returns>
HRESULT Direct3D::InitModels () {
	// 頂点の作成
	vector<XMFLOAT3> vertexPositions = 
	{
		{ -0.5f, 0.5f , 0.0f },
		{ -0.5f, -0.5f , 0.0f },
		{ 0.5f, -0.5f , 0.0f },
	};

	vector<com_ptr<Vertex>> vertices = Vertex::CreateVerticesFromXMFloat3Array (vertexPositions);
	IGeometry tryangle = winrt::make<Geometry>(vertices);

	// 頂点バッファ作成
	const UINT vertexBufferSize = sizeof(tryangle);

	// D3D12_HEAP_TYPE_UPLOAD: DEFAULTほど高速ではないがCPUから見える
	CD3DX12_HEAP_PROPERTIES heapProperties = CD3DX12_HEAP_PROPERTIES (D3D12_HEAP_TYPE_UPLOAD);
	CD3DX12_RESOURCE_DESC desc = CD3DX12_RESOURCE_DESC::Buffer (vertexBufferSize);

	m_device->CreateCommittedResource(
		&heapProperties,
		D3D12_HEAP_FLAG_NONE,
		&desc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		__uuidof(m_vertexBuffer), m_vertexBuffer.put_void());

	// 頂点バッファに頂点情報の書き込み
	UINT8* pVertexDataBegin;
	CD3DX12_RANGE readRange(0, 0);
	m_vertexBuffer->Map(0, &readRange, (void**)&pVertexDataBegin);
	memcpy(pVertexDataBegin, tryangle.GetVertexArray(), vertexBufferSize);
	m_vertexBuffer->Unmap(0, NULL);

	// バーテックスバッファビュー作成
	m_vertexBufferView.BufferLocation = m_vertexBuffer->GetGPUVirtualAddress();
	m_vertexBufferView.StrideInBytes = sizeof(XMFLOAT3);
	m_vertexBufferView.SizeInBytes = vertexBufferSize;

	return S_OK;
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
	m_commandList->Reset(m_commandAllocator.get(), m_pipelineState.get());


	// ================================================
	// ここからコマンドリストにコマンドを書き込んでいく
	// ================================================
	
	// バックバッファのトランジションをレンダーターゲットモードにする
	D3D12_RESOURCE_BARRIER render_target_mode_barrier = CD3DX12_RESOURCE_BARRIER::Transition(m_renderTargets[backBufferIndex].get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
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
	const float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	m_commandList->ClearRenderTargetView(rtvHandle, clearColor, 0, NULL);

	//ルートシグネチャをセット
	m_commandList->SetGraphicsRootSignature(m_rootSignature.get());

	// ディスクリプタヒープ（アプリにただ1つだけ）をセット
	ID3D12DescriptorHeap* ppHeaps[] = { m_descHeap.get()};
	m_commandList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);

	//World View Projection 変換
	XMMATRIX rotMat, worldMat;
	XMMATRIX viewMat;
	XMMATRIX projMat;
	// ビュートランスフォーム
	XMFLOAT3 eyeVec(0.0f, 0.0f, -3.0f);//カメラ 位置
	XMFLOAT3 dirVec(0.0f, 0.0f, 1.0f);//カメラ　方向
	XMFLOAT3 upVec(0.0f, 1.0f, 0.0f);//上方位置

	viewMat = XMMatrixLookToRH (XMLoadFloat3 (&eyeVec), XMLoadFloat3 (&dirVec), XMLoadFloat3 (&upVec));
	// プロジェクショントランスフォーム
	projMat = XMMatrixPerspectiveFovRH (3.14159f / 4.0f, (FLOAT)kWindowWidth / (FLOAT)kWindowHeight, 0.1f, 1000.0f);

	//ポリゴントポロジーの指定
	m_commandList->IASetPrimitiveTopology (D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//バーテックスバッファをセット
	m_commandList->IASetVertexBuffers (0, 1, &m_vertexBufferView);

	//描画
	static float r = 0;
	r += 0.05f;
	rotMat = XMMatrixRotationZ (r);//単純にyaw回転させる

	//コンスタントバッファの内容を更新
	CD3DX12_RANGE readRange (0, 0);
	readRange = CD3DX12_RANGE (0, 0);
	UINT8* pCbvDataBegin;
	m_constantBuffer->Map (0, &readRange, reinterpret_cast<void**>(&pCbvDataBegin));
	Cbuffer cb;
	//ワールドトランスフォーム
	worldMat = rotMat * XMMatrixTranslation (0, 0, 0);
	char* ptr = reinterpret_cast<char*>(pCbvDataBegin);
	cb.wvp = XMMatrixTranspose (worldMat * viewMat * projMat);
	memcpy (ptr, &cb, sizeof (Cbuffer));

	//テーブルセット
	D3D12_GPU_DESCRIPTOR_HANDLE cbvSrvUavDescHeap = m_descHeap->GetGPUDescriptorHandleForHeapStart ();
	m_commandList->SetGraphicsRootDescriptorTable (0, cbvSrvUavDescHeap);

	//描画
	m_commandList->DrawInstanced (3, 1, 0, 0);


	// バックバッファのトランジションをPresentモードにする
	D3D12_RESOURCE_BARRIER present_mode_barrier = CD3DX12_RESOURCE_BARRIER::Transition(m_renderTargets[backBufferIndex].get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
	m_commandList->ResourceBarrier(1, &present_mode_barrier);

	// コマンドの書き込みはここで終わり、Closeする
	m_commandList->Close();

	// コマンドリストの実行
	ID3D12CommandList* ppCommandLists[] = { m_commandList.get() };
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
	m_commandQueue->Signal(m_fence.get(), m_fenceValue);

	//上でセットしたシグナルがGPUから帰ってくるまでストール（この行で待機）
	do
	{
		//GPUの完了を待つ間、ここで何か有意義な事（CPU作業）をやるほど効率が上がる

	} while (m_fence->GetCompletedValue() < m_fenceValue);

	// フェンス値を更新
	// 前回より大きな値であればどんな値でもいい
	m_fenceValue++;
}
