#include "pch.h"
#include "ResourceFactory.h"

/// <summary>
/// 形状情報を元に、頂点バッファを作成する
/// </summary>
/// <param name="device"></param>
/// <param name="geometries"></param>
/// <returns></returns>
com_ptr<VertexBuffer> ResourceFactory::CreateVertexBufferByGeometries (com_ptr<ID3D12Device> device, GeometryCollection geometries)
{
	UINT vertexBufferSize = geometries.GetGeometriesSize ();

	auto vertexBuffer = VertexBuffer::GetInstance (device, vertexBufferSize);

	// 頂点バッファに頂点情報をMapする
	unique_ptr<UINT8> pVertexDataBegin;
	CD3DX12_RANGE readRange (0, 0);
	vertexBuffer->Map (0, &readRange, reinterpret_cast<void**>(&pVertexDataBegin));
	memcpy (pVertexDataBegin.get(), geometries.GetVertices().data(), sizeof (vertexBufferSize));
	vertexBuffer->Unmap (0, NULL);

	return vertexBuffer;
}