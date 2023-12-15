#include "pch.h"
#include "ResourceFactory.h"

/// <summary>
/// �`��������ɁA���_�o�b�t�@���쐬����
/// </summary>
/// <param name="device"></param>
/// <param name="geometries"></param>
/// <returns></returns>
com_ptr<VertexBuffer> ResourceFactory::CreateVertexBufferByGeometries (com_ptr<ID3D12Device> device, GeometryCollection geometries)
{
	UINT vertexBufferSize = geometries.GetGeometriesSize ();

	auto vertexBuffer = VertexBuffer::GetInstance (device, vertexBufferSize);

	// ���_�o�b�t�@�ɒ��_����Map����
	shared_ptr <UINT8> pVertexDataBegin;
	CD3DX12_RANGE readRange (0, 0);
	vertexBuffer->Map (0, &readRange, reinterpret_cast<void**>(&pVertexDataBegin));

	// ���_�z�񂩂�v���~�e�B�u�ȍ��W�̔z��𐶐�
	auto vertices = geometries.GetVertices ();

	memcpy (pVertexDataBegin.get(), vertices.data(), geometries.GetVerticesSize());
	vertexBuffer->Unmap (0, NULL);

	return vertexBuffer;
}

/// <summary>
/// �`��̔z������ɃC���f�b�N�X�o�b�t�@�𐶐�����
/// </summary>
/// <param name="device"></param>
/// <param name="geometries"></param>
/// <returns></returns>
com_ptr<IndexBuffer> ResourceFactory::CreateIndexBufferByGeometries (com_ptr<ID3D12Device> device, GeometryCollection geometries)
{
	UINT indexBufferSize = geometries.GetIndicesSize ();

	auto indexBuffer = IndexBuffer::GetInstance (device, indexBufferSize);

	// �C���f�b�N�X�o�b�t�@�ɒ��_����Map����
	shared_ptr <UINT8> pIndexDataBegin;
	CD3DX12_RANGE readRange (0, 0);
	indexBuffer->Map (0, &readRange, reinterpret_cast<void**>(&pIndexDataBegin));

	// ���_�z�񂩂�v���~�e�B�u�ȍ��W�̔z��𐶐�
	auto indices = geometries.GetIndices ();

	memcpy (pIndexDataBegin.get (), indices.data (), indices.GetIndicesSize ());
	indexBuffer->Unmap (0, NULL);

	return indexBuffer;
}

