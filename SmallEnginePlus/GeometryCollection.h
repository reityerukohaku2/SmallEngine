#pragma once
#include "pch.h"
#include "Geometry.h"
#include "VertexCollection.h"
#include "ICollection.h"

/// <summary>
/// Geometry�̔z��
/// </summary>
class GeometryCollection : public ICollection<Geometry>
{
public:
	GeometryCollection () {};

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="geometries">Geometry�̔z��</param>
	GeometryCollection (vector<Geometry> geometries);

	/// <summary>
	/// �z��̖����ɗv�f��ǉ�����
	/// </summary>
	/// <param name="geometry">�ǉ�����v�f</param>
	void push_back (Geometry geometry);

	/// <summary>
	/// �z��̐擪�|�C���^��Ԃ�
	/// </summary>
	/// <returns>�z��̐擪�|�C���^</returns>
	Geometry* data ();

	/// <summary>
	/// �z��̊J�n�n�_�������C�e���[�^�[��Ԃ�
	/// </summary>
	/// <returns></returns>
	typename vector<Geometry>::const_iterator begin ();

	/// <summary>
	/// �z��̏I���n�_�������C�e���[�^�[��Ԃ�
	/// </summary>
	/// <returns></returns>
	typename vector<Geometry>::const_iterator end ();

	/// <summary>
	/// targetPos�̈ʒu�ɔz���}������
	/// </summary>
	/// <param name="targetPos">�}����</param>
	/// <param name="begin">�}������z��̊J�n�n�_</param>
	/// <param name="end">�}������z��̏I���n�_</param>
	/// <returns></returns>
	typename vector<Geometry>::const_iterator insert 
	(
		typename vector<Geometry>::const_iterator targetPos, 
		typename vector<Geometry>::const_iterator begin, 
		typename vector<Geometry>::const_iterator end
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
	VertexCollection GetVertices ();

private:
	/// <summary>
	/// ���_���Čv�Z�p�֐�
	/// </summary>
	/// <returns>�S���_��</returns>
	UINT CountVertexNum ();

	vector<Geometry> m_geometries;

	/// <summary>
	/// �S���_��
	/// </summary>
	UINT m_vertexNum;
};

