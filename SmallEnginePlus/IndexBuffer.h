#pragma once
#include "pch.h"
#include <d3d12.h>
#include "d3dx12.h"

using winrt::com_ptr;

/// <summary>
/// インデックスバッファ
/// シングルトンパターン
/// </summary>
class IndexBuffer : public winrt::implements<IndexBuffer, ID3D12Resource>
{
public:

	/// <summary>
	/// コンストラクタ
	/// winrt::implementsを継承してる都合上publicにしているが、呼び出してほしくない
	/// </summary>
	/// <param name="device">D3D12デバイス</param>
	/// <param name="indexBufferSize">インデックスバッファのバイト数</param>
	IndexBuffer (com_ptr<ID3D12Device> device, UINT indexBufferSize);

	/// <summary>
	/// インスタンス生成を行う
	/// </summary>
	/// <param name="device">D3D12デバイス</param>
	/// <param name="indexBufferSize">インデックスバッファのバイト数</param>
	/// <returns>インデックスバッファインスタンス</returns>
	static com_ptr<IndexBuffer> GetInstance (com_ptr<ID3D12Device> device, UINT indexBufferSize);


	// ******************************************
	// ID3D12Resourceの純粋仮想関数
	// ******************************************

	HRESULT __stdcall Map (UINT Subresource, const D3D12_RANGE* pReadRange, void** ppData) override;
	void __stdcall Unmap (UINT Subresource, const D3D12_RANGE* pWrittenRange) override;
	D3D12_GPU_VIRTUAL_ADDRESS __stdcall GetGPUVirtualAddress (void) override;
	ULONG __stdcall Release (void) throw() override;
	ULONG __stdcall AddRef (void) throw() override;

private:
	/// <summary>
	/// インデックスバッファのインスタンス
	/// </summary>
	static inline com_ptr<IndexBuffer> s_instance;

	/// <summary>
	/// インデックスバッファ本体
	/// </summary>
	com_ptr<ID3D12Resource> m_resource;

	/// <summary>
	/// インデックスバッファのバイト数
	/// </summary>
	UINT m_indexBufferSize;

	friend class ResourceFactory;


	//// implements を介して継承されました
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

