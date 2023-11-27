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
	auto p_positions = geometries.GetVertices ().GetArrayOfXMFLOAT3Position().data();

	memcpy (pVertexDataBegin.get(), p_positions, sizeof (vertexBufferSize));
	vertexBuffer->Unmap (0, NULL);

	return vertexBuffer;
}