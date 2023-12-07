#include "pch.h"
#include "Renderer.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="geometries">�`��̔z��</param>
Renderer::Renderer (GeometryCollection geometries, HWND hWnd)
{
	//�f�o�b�O���C���[
	UINT dxgiFactoryFlags = 0;
#if defined(_DEBUG)	
	ID3D12Debug* debugController;
	if (SUCCEEDED (D3D12GetDebugInterface (IID_PPV_ARGS (&debugController))))
	{
		debugController->EnableDebugLayer ();
	}
#endif

	m_hWnd = hWnd;

	m_geometries = geometries;

	//DX12�f�o�C�X�쐬
	D3D12CreateDevice (0, D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS (&m_device));

	//�R�}���h�L���[�쐬
	CreateCommandQueue ();

	//�R�}���h���X�g�쐬
	CreateCommandList ();
	
	//�X���b�v�`�F�[���쐬
	CreateSwapChain ();

	//�����_�[�^�[�Q�b�g�쐬
	CreateRenderTarget ();

	//�t�F���X�쐬
	CreateFence();

	//�V�F�[�_�[�֘A

	//�R���X�^���g�o�b�t�@�쐬
	CreateConstantBuffer ();

	//�V�F�[�_�[�쐬
	{
		D3DCompileFromFile (L"Simple.hlsl", NULL, NULL, "VS", "vs_5_1", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &vertexShader, nullptr);
		D3DCompileFromFile (L"Simple.hlsl", NULL, NULL, "PS", "ps_5_1", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &pixelShader, nullptr);
	}

	//���[�g�V�O�l�`���쐬
	CreateRootSignature ();

	//�p�C�v���C���X�e�[�g�I�u�W�F�N�g�쐬
	CreatePilelineState ();

	// ���_�o�b�t�@�̍쐬
	m_vertexBuffer = ResourceFactory::CreateVertexBufferByGeometries (m_device, m_geometries);

	// ���_�o�b�t�@�r���[�̍쐬
	m_vertexBufferView.BufferLocation = m_vertexBuffer->GetGPUVirtualAddress();
	m_vertexBufferView.SizeInBytes = m_geometries.GetGeometriesSize ();
	m_vertexBufferView.StrideInBytes = sizeof(Vertex);

	// �C���f�b�N�X�o�b�t�@�̍쐬
	m_indexBuffer = ResourceFactory::CreateIndexBufferByGeometries (m_device, m_geometries);

	// �C���f�b�N�X�o�b�t�@�r���[�̍쐬
	m_indexBufferView.BufferLocation = m_indexBuffer->GetGPUVirtualAddress ();
	m_indexBufferView.Format = DXGI_FORMAT_R32_UINT;
	m_indexBufferView.SizeInBytes = m_geometries.GetIndicesSize();
}

Renderer::Renderer(){}

/// <summary>
/// �`��
/// </summary>
void Renderer::Render ()
{
	//�o�b�N�o�b�t�@�����݉����ڂ����擾
	UINT backBufferIndex = m_swapChain->GetCurrentBackBufferIndex ();

	//�R�}���h���X�g�ɏ������ޑO�ɂ̓R�}���h�A���P�[�^�[�����Z�b�g����
	m_commandAllocator->Reset ();

	//�R�}���h���X�g�����Z�b�g����
	m_commandList->Reset (m_commandAllocator.get(), m_pipelineState.get());


	///////////////////////////////////////////////////
	// ��������R�}���h���X�g�ɃR�}���h����������ł���
	///////////////////////////////////////////////////


	//�o�b�N�o�b�t�@�̃g�����W�V�����������_�[�^�[�Q�b�g���[�h�ɂ���
	auto resource_barrier = CD3DX12_RESOURCE_BARRIER::Transition (m_renderTargets[backBufferIndex].get (), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
	m_commandList->ResourceBarrier (1, &resource_barrier);

	//�o�b�N�o�b�t�@�������_�[�^�[�Q�b�g�ɃZ�b�g
	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle (m_rtvHeap->GetCPUDescriptorHandleForHeapStart (), backBufferIndex, m_device->GetDescriptorHandleIncrementSize (D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
	m_commandList->OMSetRenderTargets (1, &rtvHandle, false, NULL);

	//�r���[�|�[�g���Z�b�g
	CD3DX12_VIEWPORT  viewport = CD3DX12_VIEWPORT (0.0f, 0.0f, (float)kWindowWidth, (float)kWindowHeight);
	CD3DX12_RECT  scissorRect = CD3DX12_RECT (0, 0, kWindowWidth, kWindowHeight);
	m_commandList->RSSetViewports (1, &viewport);
	m_commandList->RSSetScissorRects (1, &scissorRect);

	//��ʃN���A
	const float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	m_commandList->ClearRenderTargetView (rtvHandle, clearColor, 0, NULL);

	//���[�g�V�O�l�`�����Z�b�g
	m_commandList->SetGraphicsRootSignature (m_rootSignature.get());

	//�q�[�v�i�A�v���ɂ���1�����j���Z�b�g
	ID3D12DescriptorHeap* ppHeaps[] = { m_descHeap.get()};
	m_commandList->SetDescriptorHeaps (_countof (ppHeaps), ppHeaps);

	//World View Projection �ϊ�
	XMMATRIX rotMat, worldMat;
	XMMATRIX viewMat;
	XMMATRIX projMat;

	// �r���[�g�����X�t�H�[��
	XMFLOAT3 eyeVec (0.0f, 0.0f, -3.0f);//�J���� �ʒu
	XMFLOAT3 dirVec (0.0f, 0.0f, 1.0f);//�J�����@����
	XMFLOAT3 upVec (0.0f, 1.0f, 0.0f);//����ʒu
	viewMat = XMMatrixLookToRH (XMLoadFloat3 (&eyeVec), XMLoadFloat3 (&dirVec), XMLoadFloat3 (&upVec));
	// �v���W�F�N�V�����g�����X�t�H�[��
	projMat = XMMatrixPerspectiveFovRH (3.14159 / 4, (FLOAT)kWindowWidth / (FLOAT)kWindowHeight, 0.1f, 1000.0f);

	//�|���S���g�|���W�[�̎w��
	m_commandList->IASetPrimitiveTopology (D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//�o�[�e�b�N�X�o�b�t�@���Z�b�g
	m_commandList->IASetVertexBuffers (0, 1, &m_vertexBufferView);
	//�C���f�b�N�X�o�b�t�@���Z�b�g
	m_commandList->IASetIndexBuffer (&m_indexBufferView);

	// ��]
	static float r = 0;
	r += 0.05f;
	rotMat = XMMatrixRotationZ (r);//�P����yaw��]������

	//�R���X�^���g�o�b�t�@�̓��e���X�V
	CD3DX12_RANGE readRange (0, 0);
	readRange = CD3DX12_RANGE (0, 0);
	UINT8* pCbvDataBegin;
	m_constantBuffer->Map (0, &readRange, reinterpret_cast<void**>(&pCbvDataBegin));
	Cbuffer cb;

	//���[���h�g�����X�t�H�[��
	worldMat = rotMat * XMMatrixTranslation (0, 0, 0);
	char* ptr = reinterpret_cast<char*>(pCbvDataBegin);
	cb.wvp = XMMatrixTranspose (worldMat * viewMat * projMat);
	memcpy (ptr, &cb, sizeof (Cbuffer));

	//�e�[�u���Z�b�g
	D3D12_GPU_DESCRIPTOR_HANDLE cbvSrvUavDescHeap = m_descHeap->GetGPUDescriptorHandleForHeapStart ();
	m_commandList->SetGraphicsRootDescriptorTable (0, cbvSrvUavDescHeap);

	//�`��
	auto instanceCount = m_geometries.GetVertexNum () / 3;
	m_commandList->DrawIndexedInstanced (6, instanceCount, 0, 0, 0);

	//�o�b�N�o�b�t�@�̃g�����W�V������Present���[�h�ɂ���
	resource_barrier = CD3DX12_RESOURCE_BARRIER::Transition (m_renderTargets[backBufferIndex].get (), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
	m_commandList->ResourceBarrier (1, &resource_barrier);

	//�R�}���h�̏������݂͂����ŏI���AClose����
	m_commandList->Close ();

	//�R�}���h���X�g�̎��s
	ID3D12CommandList* ppCommandLists[] = { m_commandList.get()};
	m_commandQueue->ExecuteCommandLists (_countof (ppCommandLists), ppCommandLists);

	//�o�b�N�o�b�t�@���t�����g�o�b�t�@�ɐ؂�ւ��ăV�[�������j�^�[�ɕ\��
	m_swapChain->Present (1, 0);

	//GPU�̏�������������܂ő҂�
	WaitGpu ();

	//60fps�Œ�
	static unsigned int time60 = 0;
	while (timeGetTime () - time60 < 16);
	time60 = timeGetTime ();
}

/// <summary>
/// GPU�̏�������������܂ő҂�
/// </summary>
void Renderer::WaitGpu () {
	//GPU�T�C�h���S�Ċ��������Ƃ���GPU�T�C�h����Ԃ��Ă���l�i�t�F���X�l�j���Z�b�g
	m_commandQueue->Signal (m_fence.get (), m_fenceValue);

	//��ŃZ�b�g�����V�O�i����GPU����A���Ă���܂ŃX�g�[���i���̍s�őҋ@�j
	do
	{
		//GPU�̊�����҂ԁA�����ŉ����L�Ӌ`�Ȏ��iCPU��Ɓj�����قǌ������オ��

	} while (m_fence->GetCompletedValue () < m_fenceValue);

	// �t�F���X�l���X�V
	// �O����傫�Ȓl�ł���΂ǂ�Ȓl�ł�����
	m_fenceValue++;
}

void Renderer::CreateCommandQueue () {
	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	m_device->CreateCommandQueue (&queueDesc, IID_PPV_ARGS (&m_commandQueue));
}

void Renderer::CreateCommandList () {
	m_device->CreateCommandAllocator (D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS (&m_commandAllocator));
	m_device->CreateCommandList (0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_commandAllocator.get(), NULL, IID_PPV_ARGS (&m_commandList));
	m_commandList->Close ();
}

void Renderer::CreateSwapChain()
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
	CreateDXGIFactory1 (IID_PPV_ARGS (&factory));
	factory->CreateSwapChainForHwnd (m_commandQueue.get(), m_hWnd, &swapChainDesc, NULL, NULL, (IDXGISwapChain1**)&m_swapChain);
}

void Renderer::CreateRenderTarget()
{
	//�����_�[�^�[�Q�b�g�r���[�̃q�[�v�쐬
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
	rtvHeapDesc.NumDescriptors = kFrameCount;
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	m_device->CreateDescriptorHeap (&rtvHeapDesc, IID_PPV_ARGS (&m_rtvHeap));

	// �����_�[�^�[�Q�b�g�̗̈�m��
	m_renderTargets.reserve (kFrameCount);
	m_renderTargets.resize (kFrameCount);

	// �����_�[�^�[�Q�b�g�r���[�쐬
	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle (m_rtvHeap->GetCPUDescriptorHandleForHeapStart ());
	for (UINT n = 0; n < kFrameCount; n++)
	{
		m_swapChain->GetBuffer (n, IID_PPV_ARGS (&m_renderTargets[n]));
		m_device->CreateRenderTargetView (m_renderTargets[n].get(), NULL, rtvHandle);
		rtvHandle.Offset (1, m_device->GetDescriptorHandleIncrementSize (D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
	}
}

void Renderer::CreateFence()
{
	m_device->CreateFence (0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS (&m_fence));
	m_fenceValue = 1;
}

void Renderer::CreateConstantBuffer()
{
	//�R���X�^���g�o�b�t�@�쐬
	UINT CBSize = D3D12_CONSTANT_BUFFER_DATA_PLACEMENT_ALIGNMENT;
	auto heapProperties = CD3DX12_HEAP_PROPERTIES (D3D12_HEAP_TYPE_UPLOAD);
	auto resourceDesc = CD3DX12_RESOURCE_DESC::Buffer (CBSize);

	m_device->CreateCommittedResource (
		&heapProperties,
		D3D12_HEAP_FLAG_NONE,
		&resourceDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS (&m_constantBuffer));

	//�R���X�^���g�o�b�t�@�r���[�̃q�[�v�쐬
	D3D12_DESCRIPTOR_HEAP_DESC cbvHeapDesc = {};
	cbvHeapDesc.NumDescriptors = 1;
	cbvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	cbvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	m_device->CreateDescriptorHeap (&cbvHeapDesc, IID_PPV_ARGS (&m_descHeap));

	//�R���X�^���g�o�b�t�@�r���[�쐬
	D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
	cbvDesc.BufferLocation = m_constantBuffer->GetGPUVirtualAddress ();
	cbvDesc.SizeInBytes = CBSize;
	D3D12_CPU_DESCRIPTOR_HANDLE cHandle = m_descHeap->GetCPUDescriptorHandleForHeapStart ();
	m_device->CreateConstantBufferView (&cbvDesc, cHandle);
}

void Renderer::CreateRootSignature () {
	
	//�R���X�^���g�o�b�t�@�r���[�̃e�[�u�������[�g�ɍ쐬
	CD3DX12_DESCRIPTOR_RANGE1 ranges[1];
	CD3DX12_ROOT_PARAMETER1 rootParameters[1];
	ranges[0].Init (D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 0, 0, D3D12_DESCRIPTOR_RANGE_FLAG_DATA_STATIC);
	rootParameters[0].InitAsDescriptorTable (1, &ranges[0], D3D12_SHADER_VISIBILITY_ALL);
	CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC rootSignatureDesc;
	rootSignatureDesc.Init_1_1 (_countof (rootParameters), rootParameters,
		0, NULL,
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT
	);
	ID3DBlob* signature;
	ID3DBlob* error;
	D3DX12SerializeVersionedRootSignature (&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &error);
	m_device->CreateRootSignature (0, signature->GetBufferPointer (), signature->GetBufferSize (), IID_PPV_ARGS (&m_rootSignature));
	
}

void Renderer::CreatePilelineState () {
	//���_���C�A�E�g�쐬
	D3D12_INPUT_ELEMENT_DESC inputElementDescs[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
	};

	D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
	psoDesc.InputLayout = { inputElementDescs, _countof (inputElementDescs) };
	psoDesc.pRootSignature = m_rootSignature.get();
	psoDesc.VS = CD3DX12_SHADER_BYTECODE (vertexShader);
	psoDesc.PS = CD3DX12_SHADER_BYTECODE (pixelShader);
	psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC (D3D12_DEFAULT);
	psoDesc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;
	psoDesc.BlendState = CD3DX12_BLEND_DESC (D3D12_DEFAULT);
	psoDesc.DepthStencilState.DepthEnable = false;
	psoDesc.DepthStencilState.StencilEnable = false;
	psoDesc.SampleMask = UINT_MAX;
	psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	psoDesc.NumRenderTargets = 1;
	psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
	psoDesc.SampleDesc.Count = 1;
	m_device->CreateGraphicsPipelineState (&psoDesc, IID_PPV_ARGS (&m_pipelineState));
}