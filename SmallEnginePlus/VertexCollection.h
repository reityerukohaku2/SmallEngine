#pragma once
#include "pch.h"
#include "Vertex.h"
#include "ICollection.h"

/// <summary>
/// Vertex�̔z��
/// </summary>
class VertexCollection: public ICollection<class Vertex>
{
public:
	VertexCollection () {};

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="vertices">���_�z��</param>
	VertexCollection (vector<Vertex> vertices);

	/// <summary>
	/// �z��̖����ɗv�f��ǉ�����
	/// </summary>
	void push_back (Vertex vertex);

	/// <summary>
	/// �z��v�f�̐擪�|�C���^��Ԃ�
	/// </summary>
	/// <returns>�z��̐擪�|�C���^</returns>
	Vertex* data ();

	/// <summary>
	/// �z��̊J�n�n�_�������C�e���[�^�[��Ԃ�
	/// </summary>
	/// <returns></returns>
	typename vector<Vertex>::const_iterator begin ();

	/// <summary>
	/// �z��̏I���n�_�������C�e���[�^�[��Ԃ�
	/// </summary>
	/// <returns></returns>
	typename vector<Vertex>::const_iterator end ();

	/// <summary>
	/// �z��v�f��S�č폜
	/// </summary>
	void clear ();

	/// <summary>
	/// �z��̗v�f����Ԃ�
	/// </summary>
	size_t size ();

	/// <summary>
	/// �v���~�e�B�u�^�z��ɂ������_�z���Ԃ�
	/// </summary>
	/// <returns>�v���~�e�B�u�^�z��ɂ������_�z��</returns>
	vector<XMFLOAT3> GetArrayOfXMFLOAT3Position ();

	/// <summary>
	/// targetPos�̈ʒu�ɔz���}������
	/// </summary>
	/// <param name="targetPos">�}����</param>
	/// <param name="begin">�}������z��̊J�n�n�_</param>
	/// <param name="end">�}������z��̏I���n�_</param>
	/// <returns></returns>
	typename vector<Vertex>::const_iterator insert (typename vector<Vertex>::const_iterator targetPos, typename vector<Vertex>::const_iterator begin, typename vector<Vertex>::const_iterator end);

	/// <summary>
	/// �z��S�̂̃o�C�g����Ԃ�
	/// </summary>
	/// <returns></returns>
	UINT GetVerticesSize ();
private:
	vector<Vertex> m_vertices;
};


