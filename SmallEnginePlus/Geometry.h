#pragma once
#include "pch.h"
#include "Vertex.h"
#include "VertexIndex.h"
#include "VertexBuffer.h"
#include "VertexCollection.h"

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
	Geometry (VertexCollection vertices, VertexIndex indices);

	/// <summary>
	/// �R���X�g���N�^(���_�C���f�b�N�X�Ȃ�)
	/// </summary>
	/// <param name="vertices">���_</param>
	Geometry (VertexCollection vertices);

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
	/// ���_�C���f�b�N�X�����擾����
	/// </summary>
	/// <returns>�`��̒��_�C���f�b�N�X��</returns>
	int GetIndexNum ();

	/// <summary>
	/// ���_�����擾����
	/// </summary>
	/// <returns>���_���</returns>
	VertexCollection GetVertices ();

	/// <summary>
	/// ���_�C���f�b�N�X���擾����
	/// </summary>
	/// <returns></returns>
	VertexIndex GetIndices ();

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

	/// <summary>
	/// ���_���W�Q�ƒ��_�C���f�b�N�X����`��𐶐�����
	/// </summary>
	/// <param name="vertexPositions">���_���W</param>
	/// <param name="indice">���_�C���f�b�N�X</param>
	/// <returns>�`��</returns>
	static Geometry CreateGeometryFromPosAndIndex (vector<XMFLOAT3> vertexPositions, vector<DWORD> indices);

	/// <summary>
	/// ���_���W�Q�ƒ��_�C���f�b�N�X����`��𐶐�����
	/// </summary>
	/// <param name="vertexPositions">���_���W</param>
	/// <param name="indice">���_�C���f�b�N�X</param>
	/// <returns>�`��</returns>
	static Geometry CreateGeometryFromPosAndIndex (vector<XMFLOAT3> vertexPositions, VertexIndex indices);

private:
	/// <summary>
	/// ���_�Q
	/// </summary>
	VertexCollection m_vertices;

	/// <summary>
	/// ���_�C���f�b�N�X
	/// </summary>
	VertexIndex m_indices;

};
