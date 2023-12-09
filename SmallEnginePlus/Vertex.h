#pragma once
#include "pch.h"
#include "VertexCollection.h"

/// <summary>
/// ���_�������N���X
/// </summary>
class Vertex
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">���_�ʒu</param>
	Vertex (XMVECTOR pos);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Vertex ();

	/// <summary>
	/// ���_���W��Ԃ�
	/// </summary>
	/// <returns>���_���W</returns>
	XMVECTOR GetXMVECTORPosition();

	/// <summary>
	/// �����̒��_���W���璸�_���̔z��𐶐�����
	/// </summary>
	/// <param name="positions">���_���W�Q</param>
	/// <returns>���_���̔z��</returns>
	static class VertexCollection CreateVerticesFromXMFLOAT3Array (vector<XMFLOAT3> positions);
private:
	/// <summary>
	/// ���_���W
	/// </summary>
	XMVECTOR m_pos;
};
