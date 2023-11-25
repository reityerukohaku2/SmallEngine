#pragma once
#include "pch.h"
// Direct3D�̃��C�u�������g�p�ł���悤�ɂ���
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

#define kWindowWidth 1280		//�E�B���h�E��
#define kWindowHeight 720		//�E�B���h�E����
#define kAppName "������"
#define kFrameCount 3			//��ʃo�b�t�@��
#define ARRAY_LENGTH(array) (sizeof(array) / sizeof(array[0]))

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

	/// <summary>
	/// ���f���̏�����
	/// </summary>
	/// <returns>����������SUCCEEDED</returns>
	HRESULT InitModels ();

private:

	Renderer m_renderer;

	/// <summary>
	/// �f�o�b�O�R���g���[��
	/// </summary>
	com_ptr<ID3D12Debug>					debugController;

	/// <summary>
	/// �R�}���h�A���P�[�^�[
	/// </summary>
	com_ptr<ID3D12CommandAllocator>		m_commandAllocator;



	/// <summary>
	/// �R�}���h�L���[
	/// </summary>
	com_ptr<ID3D12CommandQueue>			m_commandQueue;

	/// <summary>
	/// �X���b�v�`�F�C��
	/// </summary>
	com_ptr<IDXGISwapChain3>				m_swapChain;

	/// <summary>
	/// �����_�[�^�[�Q�b�g�r���[
	/// </summary>
	com_ptr <ID3D12Resource>				m_renderTargets[kFrameCount];
	com_ptr <ID3D12DescriptorHeap>		m_rtvHeap;



	/// <summary>
	/// ���_�o�b�t�@�r���[
	/// </summary>
	D3D12_VERTEX_BUFFER_VIEW			m_vertexBufferView;

	/// <summary>
	/// �C���f�b�N�X�o�b�t�@
	/// </summary>
	com_ptr <ID3D12Resource>				m_indexBuffer;
	D3D12_INDEX_BUFFER_VIEW				m_indexBufferView;

		
	/// <summary>
	/// �p�C�v���C���X�e�[�g�I�u�W�F�N�g
	/// </summary>
	com_ptr <ID3D12PipelineState>		m_pipelineState;

	GeometryCollection m_geometries;

	// �B��̃C���X�^���X�p�̃|�C���^
	static inline Direct3D* s_instance;

	Direct3D(){}

	/// <summary>
	/// �������̈�̊J��
	/// </summary>
	void DestroyD3D ();
};

// 
// �̗B��̃C���X�^���X���ȒP�Ɏ擾���邽�߂̃}�N��
#define D3D Direct3D::GetInstance()