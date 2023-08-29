#include "Direct3D.h"

#include <windows.h>

void Direct3D::CreateInstance() 
{
	// �C���X�^���X���폜���Ă��琶��
	DeleteInstance();

	s_instance = new Direct3D();

}

void Direct3D::DeleteInstance() 
{
	// �C���X�^���X�����݂���ꍇ�A�폜
	if (s_instance != nullptr)
	{
		delete s_instance;
		s_instance = nullptr;
	}
}

Direct3D& Direct3D::GetInstance() {
	// �C���X�^���X�����݂��Ȃ��ꍇ�A����
	if (s_instance == nullptr) {
		CreateInstance();
	}
	return *s_instance;
}

/// <summary>
/// ���������\�b�h
/// </summary>
/// <param name="hWnd">�E�B���h�E�n���h��</param>
/// <returns>��������������true�A���s����false</returns>
bool Direct3D::Initialize(HWND hWnd)
{
	//�f�o�b�O���C���[�쐬
	UINT dxgiFactoryFlags = 0;
#if defined(_DEBUG)	
	
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(debugController.GetAddressOf()))))
	{
		debugController->EnableDebugLayer();
	}
#endif

	//=====================================================
	//�f�o�C�X����(��Ƀ��\�[�X�쐬���Ɏg�p����I�u�W�F�N�g)
	//=====================================================
	UINT creationFlags = 0;

	// �f�o�C�X���쐬
	{
		D3D_FEATURE_LEVEL futureLevel = D3D_FEATURE_LEVEL_12_0;
		if (FAILED(D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(m_device.GetAddressOf())))) {
			return false;
		}
	}

	// �R�}���h�L���[�̍쐬
	{
		D3D12_COMMAND_QUEUE_DESC queueDesc = {};
		queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		if (FAILED(m_device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(m_commandQueue.GetAddressOf())))) {
			return false;
		}
	}

	// �R�}���h�A���P�[�^�ƃR�}���h���X�g�̍쐬
	{
		if (FAILED(m_device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(m_commandAllocator.GetAddressOf())))) {
			return false;
		}
		if (FAILED(m_device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_commandAllocator.Get(), NULL, IID_PPV_ARGS(m_commandList.GetAddressOf())))) {
			return false;
		}
	}

	// �X���b�v�`�F�C���̍쐬
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

	// �����_�[�^�[�Q�b�g�̍쐬
	{
		//�����_�[�^�[�Q�b�g�r���[�̃q�[�v�쐬
		D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
		rtvHeapDesc.NumDescriptors = kFrameCount;
		rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		m_device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&m_rtvHeap));

		// �����_�[�^�[�Q�b�g�r���[�쐬
		CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(m_rtvHeap->GetCPUDescriptorHandleForHeapStart());
		// �S�t���[�����쐬����
		for (UINT n = 0; n < kFrameCount; n++)
		{
			m_swapChain->GetBuffer(n, IID_PPV_ARGS(m_renderTargets[n].GetAddressOf()));
			m_device->CreateRenderTargetView(m_renderTargets[n].Get(), NULL, rtvHandle);
			rtvHandle.Offset(1, m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
		}
	}
	
	// �t�F���X�̍쐬
	{
		m_fenceValue = 0;
		if (FAILED(m_device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(m_fence.GetAddressOf())))) {
			return false;
		}
	}

	return true;
}

/// <summary>
/// �����_�����O���s��
/// </summary>
void Direct3D::Render() {
	// �o�b�N�o�b�t�@�����݉����ڂ����擾
	UINT backBufferIndex = m_swapChain->GetCurrentBackBufferIndex();

	// �R�}���h���X�g�ɏ������ޑO�ɃR�}���h�A���P�[�^�[�����Z�b�g����
	m_commandAllocator->Reset();

	// �R�}���h���X�g�����Z�b�g����
	m_commandList->Reset(m_commandAllocator.Get(), 0);


	// ================================================
	// ��������R�}���h���X�g�ɃR�}���h����������ł���
	// ================================================
	
	// �o�b�N�o�b�t�@�̃g�����W�V�����������_�[�^�[�Q�b�g���[�h�ɂ���
	D3D12_RESOURCE_BARRIER render_target_mode_barrier = CD3DX12_RESOURCE_BARRIER::Transition(m_renderTargets[backBufferIndex].Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
	m_commandList->ResourceBarrier(1, &render_target_mode_barrier);

	// �o�b�N�o�b�t�@�������_�[�^�[�Q�b�g�ɃZ�b�g
	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(m_rtvHeap->GetCPUDescriptorHandleForHeapStart(), backBufferIndex, m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
	m_commandList->OMSetRenderTargets(1, &rtvHandle, false, NULL);

	// �r���[�|�[�g���Z�b�g
	CD3DX12_VIEWPORT viewport = CD3DX12_VIEWPORT(0.0f, 0.0f, (float)kWindowWidth, (float)kWindowHeight);
	CD3DX12_RECT scissorRect = CD3DX12_RECT(0, 0, kWindowWidth, kWindowHeight);
	m_commandList->RSSetViewports(1, &viewport);
	m_commandList->RSSetScissorRects(1, &scissorRect);

	// ��ʃN���A
	const float clearColor[] = { 0.0f, 0.0f, 1.0f, 1.0f };
	m_commandList->ClearRenderTargetView(rtvHandle, clearColor, 0, NULL);

	// �o�b�N�o�b�t�@�̃g�����W�V������Present���[�h�ɂ���
	D3D12_RESOURCE_BARRIER present_mode_barrier = CD3DX12_RESOURCE_BARRIER::Transition(m_renderTargets[backBufferIndex].Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
	m_commandList->ResourceBarrier(1, &present_mode_barrier);

	// �R�}���h�̏������݂͂����ŏI���AClose����
	m_commandList->Close();

	// �R�}���h���X�g�̎��s
	ID3D12CommandList* ppCommandLists[] = { m_commandList.Get() };
	m_commandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

	//�o�b�N�o�b�t�@���t�����g�o�b�t�@�ɐ؂�ւ��ăV�[�������j�^�[�ɕ\��
	m_swapChain->Present(1, 0);

	//GPU�̏�������������܂ő҂�
	WaitGpu();
}

/// <summary>
/// GPU�̏�������������܂ő҂�
/// </summary>
void Direct3D::WaitGpu() {
	//GPU�T�C�h���S�Ċ��������Ƃ���GPU�T�C�h����Ԃ��Ă���l�i�t�F���X�l�j���Z�b�g
	m_commandQueue->Signal(m_fence.Get(), m_fenceValue);

	//��ŃZ�b�g�����V�O�i����GPU����A���Ă���܂ŃX�g�[���i���̍s�őҋ@�j
	do
	{
		//GPU�̊�����҂ԁA�����ŉ����L�Ӌ`�Ȏ��iCPU��Ɓj�����قǌ������オ��

	} while (m_fence->GetCompletedValue() < m_fenceValue);

	// �t�F���X�l���X�V
	// �O����傫�Ȓl�ł���΂ǂ�Ȓl�ł�����
	m_fenceValue++;
}