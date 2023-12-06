#pragma once
#include "pch.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "GeometryCollection.h"

class ResourceFactory
{
public:
	/// <summary>
	/// �`��̔z������ɒ��_�o�b�t�@�𐶐�����
	/// </summary>
	/// <param name="geometries">�`��̔z��</param>
	/// <returns>���_�o�b�t�@</returns>
	static com_ptr<VertexBuffer> CreateVertexBufferByGeometries (com_ptr<ID3D12Device> device, GeometryCollection geometries);

	/// <summary>
	/// �`��̔z������ɃC���f�b�N�X�o�b�t�@�𐶐�����
	/// </summary>
	/// <param name="geometries">�`��̔z��</param>
	/// <returns>�C���f�b�N�X�o�b�t�@</returns>
	static com_ptr<IndexBuffer> CreateIndexBufferByGeometries (com_ptr<ID3D12Device> device, GeometryCollection geometries);
};

