#pragma once
#include "pch.h"
#include "ResourceFactory.h"
#include "VertexBuffer.h"
#include "GeometryCollection.h"

#define kFrameCount 3  //��ʃo�b�t�@��
#define kWindowWidth 1280		//�E�B���h�E��
#define kWindowHeight 720		//�E�B���h�E����

class Renderer
{
public:
	Renderer (GeometryCollection geometries, HWND hWnd);
	Renderer ();

	void Render ();

private:
	// ******************************************
	// ���ʂ̃��\�b�h
	// ******************************************

	/// <summary>
	/// GPU�̏�������������܂ő҂�
	/// </summary>
	void WaitGpu ();

	// ******************************************
	// �������p���\�b�h
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
	// �����o�ϐ�
	// ******************************************

	//�R���X�^���g�o�b�t�@
	struct Cbuffer
	{
		XMMATRIX wvp;
		Cbuffer ()
		{
			ZeroMemory (this, sizeof (Cbuffer));
		}
	};

	/// <summary>
	/// �E�B���h�E�n���h��
	/// </summary>
	HWND m_hWnd;

	/// <summary>
	/// Direct3D�f�o�C�X
	/// </summary>
	com_ptr<ID3D12Device>				m_device;

	/// <summary>
	/// ���_�o�b�t�@
	/// </summary>
	com_ptr<VertexBuffer>               m_vertexBuffer;

	/// <summary>
	/// ���_�o�b�t�@�r���[
	/// </summary>
	D3D12_VERTEX_BUFFER_VIEW            m_vertexBufferView;

	/// <summary>
	/// �R���X�^���g�o�b�t�@
	/// </summary>
	com_ptr <ID3D12Resource> m_constantBuffer;
	com_ptr <ID3D12DescriptorHeap> m_descHeap;

	/// <summary>
	/// �R�}���h�A���P�[�^�[
	/// </summary>
	com_ptr<ID3D12CommandAllocator>		m_commandAllocator;

	/// <summary>
	/// �R�}���h���X�g
	/// </summary>
	com_ptr<ID3D12GraphicsCommandList>	m_commandList;

	/// <summary>
	/// �R�}���h�L���[
	/// </summary>
	com_ptr<ID3D12CommandQueue>			m_commandQueue;

	/// <summary>
	/// �X���b�v�`�F�C��
	/// </summary>
	com_ptr<IDXGISwapChain3>			m_swapChain;

	/// <summary>
	/// �����_�[�^�[�Q�b�g�r���[
	/// </summary>
	vector<com_ptr<ID3D12Resource>>	    m_renderTargets;
	com_ptr <ID3D12DescriptorHeap>		m_rtvHeap;

	/// <summary>
	/// �p�C�v���C���X�e�[�g�I�u�W�F�N�g
	/// </summary>
	com_ptr <ID3D12PipelineState>		m_pipelineState;

	/// <summary>
	/// ���[�g�V�O�l�`��
	/// </summary>
	com_ptr <ID3D12RootSignature>		m_rootSignature;

	/// <summary>
	/// �t�F���X
	/// </summary>
	com_ptr<ID3D12Fence>					m_fence;


	/// <summary>
	/// �t�F���X�l���i�[����ꏊ
	/// </summary>
	UINT64	m_fenceValue;
	
	/// <summary>
	/// �V�F�[�_�[
	/// </summary>
	ID3DBlob* vertexShader;
	ID3DBlob* pixelShader;

};

