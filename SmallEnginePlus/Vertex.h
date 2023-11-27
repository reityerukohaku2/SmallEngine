#pragma once
#include "pch.h"
using namespace DirectX;
using namespace std;
using winrt::com_ptr;
using std::shared_ptr;

/// <summary>
/// ���_�������N���X
/// </summary>
class Vertex
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">���_�ʒu</param>
	Vertex (XMFLOAT3 pos);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Vertex ();

	/// <summary>
	/// ���_���W��Ԃ�
	/// </summary>
	/// <returns>���_���W</returns>
	XMFLOAT3 GetXMFLOATPosition();

	/// <summary>
	/// �����̒��_���W���璸�_���̔z��𐶐�����
	/// </summary>
	/// <param name="positions">���_���W�Q</param>
	/// <returns>���_���̔z��</returns>
	static vector<Vertex> CreateVerticesFromXMFloat3Array (vector<XMFLOAT3> positions);
private:
	/// <summary>
	/// ���_���W
	/// </summary>
	XMFLOAT3 m_pos;
};
