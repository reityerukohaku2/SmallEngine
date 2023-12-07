#include "pch.h"
#include "Geometry.h"

/// <summary>
/// �R���X�g���N�^(���_�C���f�b�N�X����)
/// </summary>
/// <param name="triangles"></param>
Geometry::Geometry (VertexCollection vertices, VertexIndexCollection indices) {
	m_vertices = std::move (vertices);
	m_indices = std::move (indices);
}

/// <summary>
/// �R���X�g���N�^(���_�C���f�b�N�X�Ȃ�)
/// </summary>
/// <param name="triangles"></param>
Geometry::Geometry (VertexCollection vertices) {
	m_vertices = std::move (vertices);
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

Geometry Geometry::CreateGeometryFromPosAndIndex (vector<XMFLOAT3> vertexPositions, vector<DWORD> indicesData)
{
	auto vertices = Vertex::CreateVerticesFromXMFLOAT3Array (vertexPositions);
	auto indices = VertexIndex::CreateIndicesFromDWORDArray (indicesData);

	return Geometry (vertices, indices);
}


/// <summary>
/// ���_�����擾����
/// </summary>
/// <returns>�`��̒��_��</returns>
int Geometry::GetVertexNum () {
	return m_vertices.size();
}

/// <summary>
/// ���_�C���f�b�N�X�����擾����
/// </summary>
/// <returns>�`��̒��_�C���f�b�N�X��</returns>
int Geometry::GetIndexNum ()
{
	return m_indices.size();
}
