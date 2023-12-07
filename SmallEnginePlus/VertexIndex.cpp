#include "pch.h"
#include "VertexIndex.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="index">���_�C���f�b�N�X</param>
VertexIndex::VertexIndex (DWORD index) {
	this->m_index = index;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
VertexIndex::~VertexIndex (){}

/// <summary>
/// DWORD�̔z�񂩂璸�_�C���f�b�N�X���쐬����
/// </summary>
/// <param name="indicesData"></param>
/// <returns></returns>
VertexIndexCollection VertexIndex::CreateIndicesFromDWORDArray (vector<DWORD> indicesData)
{
	VertexIndexCollection indices;

	for (auto index : indicesData) {
		indices.push_back (VertexIndex(index));
	}

	return indices;
}
