#pragma once
#include "pch.h"
#include "ICollection.h"

/// <summary>
/// ���_�C���f�b�N�X
/// </summary>
class VertexIndex: public ICollection<DWORD>
{
public:
	VertexIndex () {};
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="indices">���_�C���f�b�N�X</param>
	VertexIndex (vector<DWORD> indices);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~VertexIndex ();

	/// <summary>
	/// ���_�C���f�b�N�X�̃o�C�g����Ԃ�
	/// </summary>
	/// <returns>���_�C���f�b�N�X�̃o�C�g��</returns>
	UINT GetIndicesSize ();

	//***************************/
	// ICollection�̏������z�֐�
	//***************************/

	/// <summary>
	/// �z��̖����ɗv�f��ǉ�����
	/// </summary>
	/// <param name="geometry">�ǉ�����v�f</param>
	void push_back (DWORD geometry);

	/// <summary>
	/// �z��̐擪�|�C���^��Ԃ�
	/// </summary>
	/// <returns>�z��̐擪�|�C���^</returns>
	DWORD* data ();

	/// <summary>
	/// �z��̊J�n�n�_�������C�e���[�^�[��Ԃ�
	/// </summary>
	/// <returns></returns>
	typename vector<DWORD>::const_iterator begin ();

	/// <summary>
	/// �z��̏I���n�_�������C�e���[�^�[��Ԃ�
	/// </summary>
	/// <returns></returns>
	typename vector<DWORD>::const_iterator end ();

	/// <summary>
	/// targetPos�̈ʒu�ɔz���}������
	/// </summary>
	/// <param name="targetPos">�}����</param>
	/// <param name="begin">�}������z��̊J�n�n�_</param>
	/// <param name="end">�}������z��̏I���n�_</param>
	/// <returns></returns>
	typename vector<DWORD>::const_iterator insert
	(
		typename vector<DWORD>::const_iterator targetPos,
		typename vector<DWORD>::const_iterator begin,
		typename vector<DWORD>::const_iterator end
	);

	/// <summary>
	/// �z��̗v�f����Ԃ�
	/// </summary>
	/// <returns></returns>
	size_t size ();

	/// <summary>
	/// �z��v�f��S�č폜
	/// </summary>
	void clear ();

private:
	/// <summary>
	/// ���_�C���f�b�N�X
	/// </summary>
	vector<DWORD> m_indices;
};
