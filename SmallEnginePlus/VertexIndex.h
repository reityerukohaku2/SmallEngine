#pragma once
#include "pch.h"
#include "VertexIndexCollection.h"

/// <summary>
/// ���_�C���f�b�N�X
/// </summary>
class VertexIndex
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="index">���_�C���f�b�N�X</param>
	VertexIndex (DWORD index);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~VertexIndex ();

	/// <summary>
	/// DWORD�̔z�񂩂璸�_�C���f�b�N�X�z��𐶐�����
	/// </summary>
	/// <param name="indices">���_�C���f�b�N�X���</param>
	/// <returns>���_�C���f�b�N�X�z��</returns>
	static class VertexIndexCollection CreateIndicesFromDWORDArray (vector<DWORD> indices);
private:
	/// <summary>
	/// ���_�C���f�b�N�X
	/// </summary>
	DWORD m_index;
};
