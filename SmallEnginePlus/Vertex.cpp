#include "pch.h"
#include "Vertex.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="pos">���_�ʒu</param>
Vertex::Vertex (XMFLOAT3 pos) {
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
XMFLOAT3 Vertex::GetXMFLOATPosition ()
{
	return m_pos;
}

/// <summary>
/// �����̒��_���W���璸�_���̔z��𐶐�����
/// </summary>
/// <param name="positions">���_���W�Q</param>
/// <returns>���_���̔z��</returns>
vector<Vertex> Vertex::CreateVerticesFromXMFloat3Array (vector<XMFLOAT3> positions) {
	vector<Vertex> vertexArray = {};

	// positions����position�����o���AVertex�I�u�W�F�N�g�𐶐�
	for (const auto position : positions) {
		Vertex vertex = Vertex (position);

		// Vertex�I�u�W�F�N�g�̃X�}�[�g�|�C���^��vertexArray�Ɋi�[���Ă���
		vertexArray.push_back (vertex);
	}

	return vertexArray;
}
