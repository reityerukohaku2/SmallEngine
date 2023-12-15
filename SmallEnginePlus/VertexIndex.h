#pragma once
#include "pch.h"
#include "ICollection.h"

/// <summary>
/// ���_�C���f�b�N�X
/// </summary>
class VertexIndex: private vector<DWORD>
{
public:
	VertexIndex () {}
	VertexIndex (vector<DWORD> &&indicecsData);

	/// <summary>
	/// ���_�C���f�b�N�X�̃o�C�g����Ԃ�
	/// </summary>
	/// <returns>���_�C���f�b�N�X�̃o�C�g��</returns>
	UINT GetIndicesSize ();


	//***************************/
	// vector�N���X�̊֐�
	//***************************/

	using vector::push_back;
	using vector::data;
	using vector::begin;
	using vector::end;
	using vector::insert;
	using vector::size;
	using vector::clear;
	using vector::reserve;
};
