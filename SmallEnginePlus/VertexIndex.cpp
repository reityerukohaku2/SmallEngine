#include "pch.h"
#include "VertexIndex.h"

VertexIndex::VertexIndex (vector<DWORD> &&indicesData) : vector<DWORD>(move(indicesData)){}

/// <summary>
/// ���_�C���f�b�N�X�̃o�C�g����Ԃ�
/// </summary>
/// <returns>���_�C���f�b�N�X�̃o�C�g��</returns>
UINT VertexIndex::GetIndicesSize () 
{
	return this->size () * sizeof (DWORD);
}
