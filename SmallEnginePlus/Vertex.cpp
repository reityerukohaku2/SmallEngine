#include "pch.h"
#include "Vertex.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="pos">���_�ʒu</param>
Vertex::Vertex (XMVECTOR pos) {
	this->m_pos = pos;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Vertex::~Vertex () {}

/// <summary>
/// ���_���W��Ԃ�
/// </summary>
/// <returns>���_���W</returns>
XMVECTOR Vertex::GetXMVECTORPosition ()
{
	return m_pos;
}

/// <summary>
/// �����̒��_���W���璸�_���̔z��𐶐�����
/// </summary>
/// <param name="positions">���_���W�Q</param>
/// <returns>���_���̔z��</returns>
VertexCollection Vertex::CreateVerticesFromXMFLOAT3Array (vector<XMFLOAT3> positions) {
	VertexCollection vertexArray = {};

	// positions����position�����o���AVertex�I�u�W�F�N�g�𐶐�
	for (const auto position : positions) {
		XMVECTOR vectorPos = XMLoadFloat3(&position);
		Vertex vertex = Vertex (vectorPos);

		// Vertex�I�u�W�F�N�g��vertexArray�Ɋi�[���Ă���
		vertexArray.push_back (vertex);
	}

	return vertexArray;
}
