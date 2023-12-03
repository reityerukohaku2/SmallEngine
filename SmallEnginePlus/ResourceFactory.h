#pragma once
#include "pch.h"
#include "VertexBuffer.h"
#include "GeometryCollection.h"

class ResourceFactory
{
public:
	/// <summary>
	/// �`��̔z������ɒ��_�o�b�t�@�𐶐�����
	/// </summary>
	/// <param name="geometries"></param>
	/// <returns></returns>
	static com_ptr<VertexBuffer> CreateVertexBufferByGeometries (com_ptr<ID3D12Device> device, GeometryCollection geometries);
};

