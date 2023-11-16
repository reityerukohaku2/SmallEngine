#pragma once
#include <d3d12.h>
#include "d3dx12.h"
#include "Vertex.h"

using winrt::com_ptr;

/// <summary>
/// 頂点バッファ
/// </summary>
class VertexBuffer : public winrt::implements<VertexBuffer, ID3D12Resource>
{
public:
	VertexBuffer (com_ptr<ID3D12Device> device, UINT vertexBufferSize);

private:
	com_ptr<ID3D12Resource> m_resource;

	// implements を介して継承されました
	HRESULT __stdcall QueryInterface (REFIID riid, void** ppvObject) override;
	ULONG __stdcall AddRef (void) override;
	ULONG __stdcall Release (void) override;
	HRESULT __stdcall GetPrivateData (REFGUID guid, UINT* pDataSize, void* pData) override;
	HRESULT __stdcall SetPrivateData (REFGUID guid, UINT DataSize, const void* pData) override;
	HRESULT __stdcall SetPrivateDataInterface (REFGUID guid, const IUnknown* pData) override;
	HRESULT __stdcall SetName (LPCWSTR Name) override;
	HRESULT __stdcall GetDevice (REFIID riid, void** ppvDevice) override;
	HRESULT __stdcall Map (UINT Subresource, const D3D12_RANGE* pReadRange, void** ppData) override;
	void __stdcall Unmap (UINT Subresource, const D3D12_RANGE* pWrittenRange) override;
	D3D12_RESOURCE_DESC __stdcall GetDesc (void) override;
	D3D12_GPU_VIRTUAL_ADDRESS __stdcall GetGPUVirtualAddress (void) override;
	HRESULT __stdcall WriteToSubresource (UINT DstSubresource, const D3D12_BOX* pDstBox, const void* pSrcData, UINT SrcRowPitch, UINT SrcDepthPitch) override;
	HRESULT __stdcall ReadFromSubresource (void* pDstData, UINT DstRowPitch, UINT DstDepthPitch, UINT SrcSubresource, const D3D12_BOX* pSrcBox) override;
	HRESULT __stdcall GetHeapProperties (D3D12_HEAP_PROPERTIES* pHeapProperties, D3D12_HEAP_FLAGS* pHeapFlags) override;
	void use_make_function_to_create_this_object () override;
};

