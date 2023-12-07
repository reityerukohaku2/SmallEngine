#pragma once
#include "pch.h"
#include "ICollection.h"
#include "VertexIndex.h"

class VertexIndexCollection : public ICollection<class VertexIndex>
{
public:
	VertexIndexCollection () {};

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="geometries">VertexIndex�̔z��</param>
	VertexIndexCollection (vector<VertexIndex> indices);

	/// <summary>
	/// �z��̖����ɗv�f��ǉ�����
	/// </summary>
	/// <param name="geometry">�ǉ�����v�f</param>
	void push_back (VertexIndex index);

	/// <summary>
	/// �z��̐擪�|�C���^��Ԃ�
	/// </summary>
	/// <returns>�z��̐擪�|�C���^</returns>
	VertexIndex* data ();

	/// <summary>
	/// �z��̊J�n�n�_�������C�e���[�^�[��Ԃ�
	/// </summary>
	/// <returns></returns>
	typename vector<VertexIndex>::const_iterator begin ();

	/// <summary>
	/// �z��̏I���n�_�������C�e���[�^�[��Ԃ�
	/// </summary>
	/// <returns></returns>
	typename vector<VertexIndex>::const_iterator end ();

	/// <summary>
	/// targetPos�̈ʒu�ɔz���}������
	/// </summary>
	/// <param name="targetPos">�}����</param>
	/// <param name="begin">�}������z��̊J�n�n�_</param>
	/// <param name="end">�}������z��̏I���n�_</param>
	/// <returns></returns>
	typename vector<VertexIndex>::const_iterator insert
	(
		typename vector<VertexIndex>::const_iterator targetPos,
		typename vector<VertexIndex>::const_iterator begin,
		typename vector<VertexIndex>::const_iterator end
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
	/// �`��̔z��
	/// </summary>
	vector<VertexIndex> m_indices;
};

