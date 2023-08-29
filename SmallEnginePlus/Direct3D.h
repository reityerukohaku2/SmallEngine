#pragma once

// Direct3D�̃��C�u�������g�p�ł���悤�ɂ���
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

#include <d3d12.h>
#include "d3dx12.h"
#include <dxgi1_4.h>
#include <DirectXMath.h>

// ComPtr���g�p�ł���悤�ɂ���
#include <wrl/client.h>
using Microsoft::WRL::ComPtr;

#define kWindowWidth 1280		//�E�B���h�E��
#define kWindowHeight 720		//�E�B���h�E����
#define kAppName "������"
#define kFrameCount 3			//��ʃo�b�t�@��

//=========================================
// Direct3D�N���X
//=========================================
class Direct3D
{
public:
	/// <summary>
	/// Direct3D�����������A�g�p�ł���悤�ɂ���
	/// </summary>
	/// <param name="hWnd">�E�B���h�E�n���h��</param>
	/// <param name="width">��ʂ̕�</param>
	/// <param name="height">��ʂ̍���</param>
	/// <returns>��������true�A���s����false��Ԃ�</returns>
	bool Initialize(HWND hWnd);

	/// <summary>
	/// �����_�����O���s��
	/// </summary>
	void Render();

	// �V���O���g�������p
	/// <summary>
	/// �C���X�^���X����
	/// </summary>
	static void CreateInstance();

	/// <summary>
	/// �C���X�^���X�폜
	/// </summary>
	static void DeleteInstance();

	/// <summary>
	/// �C���X�^���X�擾
	/// </summary>
	/// <returns></returns>
	static Direct3D& GetInstance();

private:
	/// <summary>
	/// �f�o�b�O�R���g���[��
	/// </summary>
	ComPtr<ID3D12Debug>					debugController;

	/// <summary>
	/// Direct3D�f�o�C�X
	/// </summary>
	ComPtr<ID3D12Device>				m_device;

	/// <summary>
	/// �R�}���h�A���P�[�^�[
	/// </summary>
	ComPtr<ID3D12CommandAllocator>		m_commandAllocator;

	/// <summary>
	/// �R�}���h���X�g
	/// </summary>
	ComPtr<ID3D12GraphicsCommandList>	m_commandList;

	/// <summary>
	/// �R�}���h�L���[
	/// </summary>
	ComPtr<ID3D12CommandQueue>			m_commandQueue;

	/// <summary>
	/// �X���b�v�`�F�C��
	/// </summary>
	ComPtr<IDXGISwapChain3>				m_swapChain;

	/// <summary>
	/// �����_�[�^�[�Q�b�g�r���[�̃q�[�v
	/// </summary>
	ComPtr<ID3D12DescriptorHeap>		m_rtvHeap;

	/// <summary>
	/// �����_�[�^�[�Q�b�g�r���[
	/// </summary>
	ComPtr <ID3D12Resource>				m_renderTargets[kFrameCount];

	/// <summary>
	/// �t�F���X
	/// </summary>
	ComPtr<ID3D12Fence>					m_fence;

	/// <summary>
	/// �t�F���X�l���i�[����ꏊ
	/// </summary>
	UINT64	m_fenceValue;

	// �B��̃C���X�^���X�p�̃|�C���^
	static inline Direct3D* s_instance;

	Direct3D() {}

	/// <summary>
	/// GPU�̏�������������܂ő҂�
	/// </summary>
	void WaitGpu();
};

// Direct3D�̗B��̃C���X�^���X���ȒP�Ɏ擾���邽�߂̃}�N��
#define D3D Direct3D::GetInstance()