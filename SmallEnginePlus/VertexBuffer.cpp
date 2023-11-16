#include "pch.h"
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer (com_ptr<ID3D12Device> device, UINT vertexBufferSize)
{
	// 頂点バッファ作成
	// D3D12_HEAP_TYPE_UPLOAD: DEFAULTほど高速ではないがCPUから見える
	CD3DX12_HEAP_PROPERTIES heapProperties = CD3DX12_HEAP_PROPERTIES (D3D12_HEAP_TYPE_UPLOAD);
	CD3DX12_RESOURCE_DESC desc = CD3DX12_RESOURCE_DESC::Buffer (vertexBufferSize);

	device->CreateCommittedResource (
		&heapProperties,
		D3D12_HEAP_FLAG_NONE,
		&desc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		__uuidof(m_resource), m_resource.put_void ());
}

HRESULT __stdcall VertexBuffer::QueryInterface (REFIID riid, void** ppvObject)
{
	return E_NOTIMPL;
}

ULONG __stdcall VertexBuffer::AddRef (void)
{
	return 0;
}

ULONG __stdcall VertexBuffer::Release (void)
{
	return 0;
}

HRESULT __stdcall VertexBuffer::GetPrivateData (REFGUID guid, UINT* pDataSize, void* pData)
{
	return E_NOTIMPL;
}

HRESULT __stdcall VertexBuffer::SetPrivateData (REFGUID guid, UINT DataSize, const void* pData)
{
	return E_NOTIMPL;
}

HRESULT __stdcall VertexBuffer::SetPrivateDataInterface (REFGUID guid, const IUnknown* pData)
{
	return E_NOTIMPL;
}

HRESULT __stdcall VertexBuffer::SetName (LPCWSTR Name)
{
	return E_NOTIMPL;
}

HRESULT __stdcall VertexBuffer::GetDevice (REFIID riid, void** ppvDevice)
{
	return E_NOTIMPL;
}

HRESULT __stdcall VertexBuffer::Map (UINT Subresource, const D3D12_RANGE* pReadRange, void** ppData)
{
	return E_NOTIMPL;
}

void __stdcall VertexBuffer::Unmap (UINT Subresource, const D3D12_RANGE* pWrittenRange)
{
}

D3D12_RESOURCE_DESC __stdcall VertexBuffer::GetDesc (void)
{
	return D3D12_RESOURCE_DESC ();
}

D3D12_GPU_VIRTUAL_ADDRESS __stdcall VertexBuffer::GetGPUVirtualAddress (void)
{
	return D3D12_GPU_VIRTUAL_ADDRESS ();
}

HRESULT __stdcall VertexBuffer::WriteToSubresource (UINT DstSubresource, const D3D12_BOX* pDstBox, const void* pSrcData, UINT SrcRowPitch, UINT SrcDepthPitch)
{
	return E_NOTIMPL;
}

HRESULT __stdcall VertexBuffer::ReadFromSubresource (void* pDstData, UINT DstRowPitch, UINT DstDepthPitch, UINT SrcSubresource, const D3D12_BOX* pSrcBox)
{
	return E_NOTIMPL;
}

HRESULT __stdcall VertexBuffer::GetHeapProperties (D3D12_HEAP_PROPERTIES* pHeapProperties, D3D12_HEAP_FLAGS* pHeapFlags)
{
	return E_NOTIMPL;
}

void VertexBuffer::use_make_function_to_create_this_object ()
{
}
