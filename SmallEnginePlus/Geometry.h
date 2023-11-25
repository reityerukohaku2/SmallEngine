#pragma once
#include "pch.h"
#include "Vertex.h"
#include "VertexIndex.h"
#include "VertexBuffer.h"

using namespace std;
using winrt::com_ptr;

/// <summary>
/// ���_��g�ݍ��킹���`��
/// </summary>
class Geometry
{
public:
	/// <summary>
	/// �R���X�g���N�^(���_�C���f�b�N�X����)
	/// </summary>
	/// <param name="vertices">���_</param>
	/// <param name="indices">���_�C���f�b�N�X</param>
	Geometry (vector<Vertex> vertices, vector<VertexIndex> indices);

	/// <summary>
	/// �R���X�g���N�^(���_�C���f�b�N�X�Ȃ�)
	/// </summary>
	/// <param name="vertices">���_</param>
	Geometry (vector<Vertex> vertices);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Geometry ();

	/// <summary>
	/// ���_�����擾����
	/// </summary>
	/// <returns>�`��̒��_��</returns>
	int GetVertexNum ();

	/// <summary>
	/// ���_�����擾����
	/// </summary>
	/// <returns>���_���</returns>
	vector<Vertex> GetVertices ();

	/// <summary>
	/// ���_���z����擾����
	/// </summary>
	/// <returns>���_���z��</returns>
	shared_ptr<Vertex> GetVertexArray ();

	/// <summary>
	/// ���_���W�Q����`��𐶐�����
	/// </summary>
	/// <param name="vertexPositions">���_���W�Q</param>
	/// <returns>�`��</returns>
	static Geometry CreateGeometryFromXMFloat3Array (vector<XMFLOAT3> vertexPositions);

private:
	/// <summary>
	/// ���_
	/// </summary>
	vector<Vertex> m_vertices;

	/// <summary>
	/// ���_�C���f�b�N�X
	/// </summary>
	vector<VertexIndex> m_indices;

};
