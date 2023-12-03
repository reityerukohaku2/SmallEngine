#pragma once
#include "pch.h"
#include <d3d12.h>
#include "d3dx12.h"
#include "Vertex.h"

using winrt::com_ptr;

/// <summary>
/// 頂点バッファ
/// シングルトンパターン
/// </summary>
class VertexBuffer : public winrt::implements<VertexBuffer, ID3D12Resource>
{
public:

	/// <summary>
	/// コンストラクタ
	/// winrt::implementsを継承してる都合上publicにしているが、呼び出してほしくない
	/// </summary>
	/// <param name="device">D3D12デバイス</param>
	/// <param name="vertexBufferSize">頂点バッファのバイト数</param>
	VertexBuffer (com_ptr<ID3D12Device> device, UINT vertexBufferSize);

	/// <summary>
	/// インスタンス生成を行う
	/// </summary>
	/// <param name="device">D3D12デバイス</param>
	/// <param name="vertexBufferSize">頂点バッファのバイト数</param>
	/// <returns>頂点バッファインスタンス</returns>
	static com_ptr<VertexBuffer> GetInstance (com_ptr<ID3D12Device> device, UINT vertexBufferSize);

	/// <summary>
	/// 頂点バッファのバイト数を取得する
	/// </summary>
	/// <returns>頂点バッファのバイト数</returns>
	UINT GetVertexBufferSize ();


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
	/// 頂点バッファのインスタンス
	/// </summary>
	static inline com_ptr<VertexBuffer> s_instance;

	/// <summary>
	/// 頂点バッファ本体
	/// </summary>
	com_ptr<ID3D12Resource> m_resource;
	
	/// <summary>
	/// 頂点バッファのバイト数
	/// </summary>
	UINT m_vertexBufferSize;

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

