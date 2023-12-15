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
	shared_ptr <UINT8> pVertexDataBegin;
	CD3DX12_RANGE readRange (0, 0);
	vertexBuffer->Map (0, &readRange, reinterpret_cast<void**>(&pVertexDataBegin));

	// 頂点配列からプリミティブな座標の配列を生成
	auto vertices = geometries.GetVertices ();

	memcpy (pVertexDataBegin.get(), vertices.data(), geometries.GetVerticesSize());
	vertexBuffer->Unmap (0, NULL);

	return vertexBuffer;
}

/// <summary>
/// 形状の配列を元にインデックスバッファを生成する
/// </summary>
/// <param name="device"></param>
/// <param name="geometries"></param>
/// <returns></returns>
com_ptr<IndexBuffer> ResourceFactory::CreateIndexBufferByGeometries (com_ptr<ID3D12Device> device, GeometryCollection geometries)
{
	UINT indexBufferSize = geometries.GetIndicesSize ();

	auto indexBuffer = IndexBuffer::GetInstance (device, indexBufferSize);

	// インデックスバッファに頂点情報をMapする
	shared_ptr <UINT8> pIndexDataBegin;
	CD3DX12_RANGE readRange (0, 0);
	indexBuffer->Map (0, &readRange, reinterpret_cast<void**>(&pIndexDataBegin));

	// 頂点配列からプリミティブな座標の配列を生成
	auto indices = geometries.GetIndices ();

	memcpy (pIndexDataBegin.get (), indices.data (), indices.GetIndicesSize ());
	indexBuffer->Unmap (0, NULL);

	return indexBuffer;
}

