#include "pch.h"
#include "Geometry.h"

/// <summary>
/// �R���X�g���N�^(���_�C���f�b�N�X����)
/// </summary>
/// <param name="triangles"></param>
Geometry::Geometry (VertexCollection vertices, vector<VertexIndex> indices) {
	m_vertices = std::move (vertices);
	m_indices = std::move (indices);
}

/// <summary>
/// �R���X�g���N�^(���_�C���f�b�N�X�Ȃ�)
/// </summary>
/// <param name="triangles"></param>
Geometry::Geometry (VertexCollection vertices) {
	this->m_vertices = std::move (vertices);

	void* data;
	CD3DX12_RANGE readRange (0, 0);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Geometry::~Geometry () {
	for (const auto vertex : m_vertices) {
		vertex.~Vertex ();
	}

	for (const auto index : m_indices) {
		index.~VertexIndex ();
	}

	m_vertices.clear();
}

/// <summary>
/// ���_�����擾����
/// </summary>
/// <returns>���_���</returns>
VertexCollection Geometry::GetVertices () {
	return m_vertices;
}

/// <summary>
/// ���_���W�Q����`��𐶐�����
/// </summary>
/// <param name="vertexPositions">���_���W�Q</param>
/// <returns>�`��</returns>
Geometry Geometry::CreateGeometryFromXMFloat3Array (vector<XMFLOAT3> vertexPositions)
{
	auto vertices = Vertex::CreateVerticesFromXMFLOAT3Array (vertexPositions);
	return Geometry (vertices);
}


/// <summary>
/// ���_�����擾����
/// </summary>
/// <returns>�`��̒��_��</returns>
int Geometry::GetVertexNum () {
	return this->m_vertices.size();
}