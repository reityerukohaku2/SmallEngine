#pragma once
#include "pch.h"
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
private:
	/// <summary>
	/// ���_�C���f�b�N�X
	/// </summary>
	DWORD m_index;
};
