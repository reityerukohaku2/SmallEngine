#pragma once
#include "pch.h"
#include "VertexBuffer.h"
#include "GeometryCollection.h"

class ResourceFactory
{
public:
	/// <summary>
	/// 形状の配列を元に頂点バッファを生成する
	/// </summary>
	/// <param name="geometries"></param>
	/// <returns></returns>
	static com_ptr<VertexBuffer> CreateVertexBufferByGeometries (com_ptr<ID3D12Device> device, GeometryCollection geometries);
};

