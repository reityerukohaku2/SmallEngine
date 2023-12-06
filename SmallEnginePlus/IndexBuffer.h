#pragma once
#include "pch.h"
#include <d3d12.h>
#include "d3dx12.h"

using winrt::com_ptr;

/// <summary>
/// �C���f�b�N�X�o�b�t�@
/// �V���O���g���p�^�[��
/// </summary>
class IndexBuffer : public winrt::implements<IndexBuffer, ID3D12Resource>
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// winrt::implements���p�����Ă�s����public�ɂ��Ă��邪�A�Ăяo���Ăق����Ȃ�
	/// </summary>
	/// <param name="device">D3D12�f�o�C�X</param>
	/// <param name="indexBufferSize">�C���f�b�N�X�o�b�t�@�̃o�C�g��</param>
	IndexBuffer (com_ptr<ID3D12Device> device, UINT indexBufferSize);

	/// <summary>
	/// �C���X�^���X�������s��
	/// </summary>
	/// <param name="device">D3D12�f�o�C�X</param>
	/// <param name="indexBufferSize">�C���f�b�N�X�o�b�t�@�̃o�C�g��</param>
	/// <returns>�C���f�b�N�X�o�b�t�@�C���X�^���X</returns>
	static com_ptr<IndexBuffer> GetInstance (com_ptr<ID3D12Device> device, UINT indexBufferSize);


	// ******************************************
	// ID3D12Resource�̏������z�֐�
	// ******************************************

	HRESULT __stdcall Map (UINT Subresource, const D3D12_RANGE* pReadRange, void** ppData) override;
	void __stdcall Unmap (UINT Subresource, const D3D12_RANGE* pWrittenRange) override;
	D3D12_GPU_VIRTUAL_ADDRESS __stdcall GetGPUVirtualAddress (void) override;
	ULONG __stdcall Release (void) throw() override;
	ULONG __stdcall AddRef (void) throw() override;

private:
	/// <summary>
	/// �C���f�b�N�X�o�b�t�@�̃C���X�^���X
	/// </summary>
	static inline com_ptr<IndexBuffer> s_instance;

	/// <summary>
	/// �C���f�b�N�X�o�b�t�@�{��
	/// </summary>
	com_ptr<ID3D12Resource> m_resource;

	/// <summary>
	/// �C���f�b�N�X�o�b�t�@�̃o�C�g��
	/// </summary>
	UINT m_indexBufferSize;

	friend class ResourceFactory;


	//// implements ����Čp������܂���
	HRESULT __stdcall QueryInterface (REFIID riid, void** ppvObject) throw() override;

	HRESULT __stdcall GetPrivateData (REFGUID guid, UINT* pDataSize, void* pData) override;

	HRESULT __stdcall SetPrivateData (REFGUID guid, UINT DataSize, const void* pData) override;

	HRESULT __stdcall SetPrivateDataInterface (REFGUID guid, const IUnknown* pData) override;

	HRESULT __stdcall SetName (LPCWSTR Name) override;

	HRESULT __stdcall GetDevice (REFIID riid, void** ppvDevice) override;

	D3D12_RESOURCE_DESC __stdcall GetDesc (void) override;

	HRESULT __stdcall WriteToSubresource (UINT DstSubresource, const D3D12_BOX* pDstBox, const void* pSrcData, UINT SrcRowPitch, UINT SrcDepthPitch) override;

	HRESULT __stdcall ReadFromSubresource (void* pDstData, UINT DstRowPitch, UINT DstDepthPitch, UINT SrcSubresource, const D3D12_BOX* pSrcBox) override;

	HRESULT __stdcall GetHeapProperties (D3D12_HEAP_PROPERTIES* pHeapProperties, D3D12_HEAP_FLAGS* pHeapFlags) override;

	void use_make_function_to_create_this_object () override;

};

