#pragma once
#include "pch.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "GeometryCollection.h"

class ResourceFactory
{
public:
	/// <summary>
	/// 形状の配列を元に頂点バッファを生成する
	/// </summary>
	/// <param name="geometries">形状の配列</param>
	/// <returns>頂点バッファ</returns>
	static com_ptr<VertexBuffer> CreateVertexBufferByGeometries (com_ptr<ID3D12Device> device, GeometryCollection geometries);

	/// <summary>
	/// 形状の配列を元にインデックスバッファを生成する
	/// </summary>
	/// <param name="geometries">形状の配列</param>
	/// <returns>インデックスバッファ</returns>
	static com_ptr<IndexBuffer> CreateIndexBufferByGeometries (com_ptr<ID3D12Device> device, GeometryCollection geometries);
};

