#pragma once
#include "pch.h"
#include "Geometry.h"
#include "VertexIndex.h"

/// <summary>
/// Geometry�̔z��
/// </summary>
class GeometryCollection : private vector<Geometry>
{
public:

	/// <summary>
	/// �`����ɑ��݂���S�Ă̒��_����Ԃ�
	/// </summary>
	/// <returns>�`����ɑ��݂���S�Ă̒��_��</returns>
	UINT GetVertexNum ();

	/// <summary>
	/// �`��̃o�C�g����Ԃ�
	/// </summary>
	/// <returns></returns>
	UINT GetGeometriesSize ();

	/// <summary>
	/// �S�Ă̒��_�����擾����
	/// </summary>
	vector<Vertex> GetVertices ();

	/// <summary>
	/// ���_�̃o�C�g����Ԃ�
	/// </summary>
	/// <returns></returns>
	UINT GetVerticesSize ();

	/// <summary>
	/// �S�Ă̒��_�C���f�b�N�X���擾����
	/// </summary>
	/// <returns></returns>
	VertexIndex GetIndices ();

	/// <summary>
	/// ���_�C���f�b�N�X�̃o�C�g����Ԃ�
	/// </summary>
	/// <returns>���_�C���f�b�N�X�̃o�C�g��</returns>
	UINT GetIndicesSize ();

	/// <summary>
	/// ���_�C���f�b�N�X�̐���Ԃ�
	/// </summary>
	/// <returns>���_�C���f�b�N�X�̐�</returns>
	UINT GetIndexNum ();


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

private:
	/// <summary>
	/// ���_���Čv�Z�p�֐�
	/// </summary>
	/// <returns>�S���_��</returns>
	UINT CountVertexNum ();

	/// <summary>
	/// ���_�C���f�b�N�X���Čv�Z�p�֐�
	/// </summary>
	/// <returns>�S���_�C���f�b�N�X��</returns>
	UINT CountIndexNum ();

	/// <summary>
	/// �S���_��
	/// </summary>
	UINT m_vertexNum;

	/// <summary>
	/// ���_�C���f�b�N�X��
	/// </summary>
	UINT m_indexNum;
};

