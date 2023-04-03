#pragma once

// Direct3D�̃��C�u�������g�p�ł���悤�ɂ���
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#include <d3d11.h>
#include <DirectXMath.h>

// ComPtr���g�p�ł���悤�ɂ���
#include <wrl/client.h>
using Microsoft::WRL::ComPtr;

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
	bool Initialize(HWND hWnd, int width, int height);

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
	/// �f�o�C�X�R���e�L�X�g�̎擾
	/// </summary>
	/// <returns>�f�o�C�X�R���e�L�X�g</returns>
	ComPtr<ID3D11DeviceContext> GetDeviceContext();

	/// <summary>
	/// �o�b�N�o�b�t�@�[�r���[�̎擾
	/// </summary>
	/// <returns>�o�b�N�o�b�t�@�[�r���[</returns>
	ComPtr<ID3D11RenderTargetView> GetBackBufferView();

	/// <summary>
	/// �X���b�v�`�F�C���̎擾
	/// </summary>
	/// <returns>�X���b�v�`�F�C��</returns>
	ComPtr<IDXGISwapChain> GetSwapChain();

private:
	// Direct3D�f�o�C�X
	ComPtr<ID3D11Device>		m_device;
	// Direct3D�f�o�C�X�R���e�L�X�g
	ComPtr<ID3D11DeviceContext>	m_deviceContext;
	// �X���b�v�`�F�C��
	ComPtr<IDXGISwapChain>		m_swapChain;
	// �o�b�N�o�b�t�@�[��RT�r���[
	ComPtr<ID3D11RenderTargetView> m_backBufferView;

	// �B��̃C���X�^���X�p�̃|�C���^
	static inline Direct3D* s_instance;

	Direct3D() {}

};

// Direct3D�̗B��̃C���X�^���X���ȒP�Ɏ擾���邽�߂̃}�N��
#define D3D Direct3D::GetInstance()