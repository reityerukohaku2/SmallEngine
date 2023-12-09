#include "pch.h"
#include "IndexBuffer.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="device">D3D12デバイス</param>
/// <param name="indexBufferSize">インデックスバッファのバイト数</param>
IndexBuffer::IndexBuffer (com_ptr<ID3D12Device> device, UINT indexBufferSize)
{
	// インデックスバッファ作成
	// D3D12_HEAP_TYPE_UPLOAD: DEFAULTほど高速ではないがCPUから見える
	CD3DX12_HEAP_PROPERTIES heapProperties = CD3DX12_HEAP_PROPERTIES (D3D12_HEAP_TYPE_UPLOAD);
	CD3DX12_RESOURCE_DESC desc = CD3DX12_RESOURCE_DESC::Buffer (indexBufferSize);

	device->CreateCommittedResource (
		&heapProperties,
		D3D12_HEAP_FLAG_NONE,
		&desc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		__uuidof(m_resource), m_resource.put_void ());

	m_indexBufferSize = indexBufferSize;
}

/// <summary>
/// インスタンス生成を行う
/// </summary>
/// <param name="device">D3D12デバイス</param>
/// <param name="indexBufferSize">インデックスバッファのバイト数</param>
/// <returns>インデックスバッファインスタンス</returns>
com_ptr<IndexBuffer> IndexBuffer::GetInstance (com_ptr<ID3D12Device> device, UINT indexBufferSize)
{
	if (s_instance == nullptr) {
		s_instance = winrt::make_self<IndexBuffer> (device, indexBufferSize);
	}
	return s_instance;
}

HRESULT __stdcall IndexBuffer::Map (UINT Subresource, const D3D12_RANGE* pReadRange, void** ppData)
{
	return m_resource->Map (Subresource, pReadRange, ppData);
}

void __stdcall IndexBuffer::Unmap (UINT Subresource, const D3D12_RANGE* pWrittenRange)
{
	return m_resource->Unmap (Subresource, pWrittenRange);
}

D3D12_GPU_VIRTUAL_ADDRESS __stdcall IndexBuffer::GetGPUVirtualAddress (void)
{
	return m_resource->GetGPUVirtualAddress ();
}


HRESULT __stdcall IndexBuffer::QueryInterface (REFIID riid, void** ppvObject)
{
	return m_resource->QueryInterface (riid, ppvObject);
}

ULONG __stdcall IndexBuffer::AddRef (void)
{
	return m_resource->AddRef ();
}

ULONG __stdcall IndexBuffer::Release (void)
{
	return m_resource->Release ();
}

HRESULT __stdcall IndexBuffer::GetPrivateData (REFGUID guid, UINT* pDataSize, void* pData)
{
	return m_resource->GetPrivateData (guid, pDataSize, pData);
}

HRESULT __stdcall IndexBuffer::SetPrivateData (REFGUID guid, UINT DataSize, const void* pData)
{
	return m_resource->SetPrivateData (guid, DataSize, pData);
}

HRESULT __stdcall IndexBuffer::SetPrivateDataInterface (REFGUID guid, const IUnknown* pData)
{
	return m_resource->SetPrivateDataInterface (guid, pData);
}

HRESULT __stdcall IndexBuffer::SetName (LPCWSTR Name)
{
	return m_resource->SetName (Name);
}

HRESULT __stdcall IndexBuffer::GetDevice (REFIID riid, void** ppvDevice)
{
	return m_resource->GetDevice (riid, ppvDevice);
}

D3D12_RESOURCE_DESC __stdcall IndexBuffer::GetDesc (void)
{
	return m_resource->GetDesc ();
}

HRESULT __stdcall IndexBuffer::WriteToSubresource (UINT DstSubresource, const D3D12_BOX* pDstBox, const void* pSrcData, UINT SrcRowPitch, UINT SrcDepthPitch)
{
	return m_resource->WriteToSubresource (DstSubresource, pDstBox, pSrcData, SrcRowPitch, SrcDepthPitch);
}

HRESULT __stdcall IndexBuffer::ReadFromSubresource (void* pDstData, UINT DstRowPitch, UINT DstDepthPitch, UINT SrcSubresource, const D3D12_BOX* pSrcBox)
{
	return m_resource->ReadFromSubresource (pDstData, DstRowPitch, DstDepthPitch, SrcSubresource, pSrcBox);
}

HRESULT __stdcall IndexBuffer::GetHeapProperties (D3D12_HEAP_PROPERTIES* pHeapProperties, D3D12_HEAP_FLAGS* pHeapFlags)
{
	return m_resource->GetHeapProperties (pHeapProperties, pHeapFlags);
}

void IndexBuffer::use_make_function_to_create_this_object ()
{
}

/// <summary>
/// インデックスバッファの大きさを返す
/// </summary>
/// <returns></returns>
UINT IndexBuffer::GetIndexBufferSize () {
	return m_indexBufferSize;
}