#pragma once
#include "pch.h"
#include "Geometry.h"

class GeometryCollection:public vector<Geometry>
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
};

