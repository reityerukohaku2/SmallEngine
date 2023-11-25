#include "pch.h"
#include "VertexBuffer.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="device">D3D12デバイス</param>
/// <param name="vertexBufferSize">頂点バッファのバイト数</param>
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
		__uuidof(m_resource), m_resource.put_void());

	m_vertexBufferSize = vertexBufferSize;
}

/// <summary>
/// インスタンス生成を行う
/// </summary>
/// <param name="device">D3D12デバイス</param>
/// <param name="vertexBufferSize">頂点バッファのバイト数</param>
/// <returns>頂点バッファインスタンス</returns>
com_ptr<VertexBuffer> VertexBuffer::GetInstance (com_ptr<ID3D12Device> device, UINT vertexBufferSize)
{
	if (s_instance == nullptr) {
		s_instance = winrt::make_self<VertexBuffer> (device, vertexBufferSize);
	}
	return s_instance;
}

HRESULT __stdcall VertexBuffer::Map (UINT Subresource, const D3D12_RANGE* pReadRange, void** ppData)
{
	return m_resource->Map (Subresource, pReadRange, ppData);
}

void __stdcall VertexBuffer::Unmap (UINT Subresource, const D3D12_RANGE* pWrittenRange)
{
	return m_resource->Unmap (Subresource, pWrittenRange);
}

D3D12_GPU_VIRTUAL_ADDRESS __stdcall VertexBuffer::GetGPUVirtualAddress (void)
{
	return m_resource->GetGPUVirtualAddress();
}


HRESULT __stdcall VertexBuffer::QueryInterface (REFIID riid, void** ppvObject)
{
	return m_resource->QueryInterface(riid, ppvObject);
}

ULONG __stdcall VertexBuffer::AddRef (void)
{
	return m_resource->AddRef();
}

ULONG __stdcall VertexBuffer::Release (void)
{
	return m_resource->Release();
}

HRESULT __stdcall VertexBuffer::GetPrivateData (REFGUID guid, UINT* pDataSize, void* pData)
{
	return m_resource->GetPrivateData(guid, pDataSize, pData);
}

HRESULT __stdcall VertexBuffer::SetPrivateData (REFGUID guid, UINT DataSize, const void* pData)
{
	return m_resource->SetPrivateData(guid, DataSize, pData);
}

HRESULT __stdcall VertexBuffer::SetPrivateDataInterface (REFGUID guid, const IUnknown* pData)
{
	return m_resource->SetPrivateDataInterface(guid, pData);
}

HRESULT __stdcall VertexBuffer::SetName (LPCWSTR Name)
{
	return m_resource->SetName(Name);
}

HRESULT __stdcall VertexBuffer::GetDevice (REFIID riid, void** ppvDevice)
{
	return m_resource->GetDevice(riid, ppvDevice);
}

D3D12_RESOURCE_DESC __stdcall VertexBuffer::GetDesc (void)
{
	return m_resource->GetDesc();
}

HRESULT __stdcall VertexBuffer::WriteToSubresource (UINT DstSubresource, const D3D12_BOX* pDstBox, const void* pSrcData, UINT SrcRowPitch, UINT SrcDepthPitch)
{
	return m_resource->WriteToSubresource(DstSubresource, pDstBox, pSrcData, SrcRowPitch, SrcDepthPitch);
}

HRESULT __stdcall VertexBuffer::ReadFromSubresource (void* pDstData, UINT DstRowPitch, UINT DstDepthPitch, UINT SrcSubresource, const D3D12_BOX* pSrcBox)
{
	return m_resource->ReadFromSubresource(pDstData, DstRowPitch, DstDepthPitch, SrcSubresource, pSrcBox);
}

HRESULT __stdcall VertexBuffer::GetHeapProperties (D3D12_HEAP_PROPERTIES* pHeapProperties, D3D12_HEAP_FLAGS* pHeapFlags)
{
	return m_resource->GetHeapProperties(pHeapProperties, pHeapFlags);
}

void VertexBuffer::use_make_function_to_create_this_object ()
{
}


/// <summary>
/// 頂点バッファの大きさを返す
/// </summary>
/// <returns></returns>
UINT VertexBuffer::GetVertexBufferSize () {
	return m_vertexBufferSize;
}