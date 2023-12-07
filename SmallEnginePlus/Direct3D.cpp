#include "pch.h"
#include "Direct3D.h"
#include <windows.h>

void Direct3D::CreateInstance() 
{
	// �C���X�^���X���폜���Ă��琶��
	DeleteInstance();

	s_instance = new Direct3D();

}

void Direct3D::DeleteInstance() 
{
	// �C���X�^���X�����݂���ꍇ�A�폜
	if (s_instance != nullptr)
	{
		delete s_instance;
		s_instance = nullptr;
	}
}

Direct3D& Direct3D::GetInstance() {
	// �C���X�^���X�����݂��Ȃ��ꍇ�A����
	if (s_instance == nullptr) {
		CreateInstance();
	}
	return *s_instance;
}

/// <summary>
/// ���������\�b�h
/// </summary>
/// <param name="hWnd">�E�B���h�E�n���h��</param>
/// <returns>��������������true�A���s����false</returns>
bool Direct3D::Initialize(HWND hWnd)
{
	// �`��̍쐬
	InitModels ();

	m_renderer = Renderer (m_geometries, hWnd);

	return true;
}

/// <summary>
/// ���f���̏�����
/// </summary>
/// <returns>����������SUCCEEDED</returns>
HRESULT Direct3D::InitModels () {
	// ���_���W
	vector<XMFLOAT3> vertexPositions = 
	{
		{ -0.5f, 0.5f , 0.0f },
		{ -0.5f, -0.5f , 0.0f },
		{ 0.5f, -0.5f , 0.0f },

		{ -0.5f, 0.5f , 0.0f },
		{ 0.5f, -0.5f , 0.0f },
		{ 0.5f, 0.5f , 0.0f }
	};

	// ���_�C���f�b�N�X
	vector<DWORD> indices =
	{
		0, 1, 2,
		0, 2, 3,
	};

	// �`��̍쐬
	Geometry geometry = Geometry::CreateGeometryFromPosAndIndex (vertexPositions, indices);

	// �`��̒ǉ�
	m_geometries.push_back(geometry);

	return S_OK;
}

/// <summary>
/// �����_�����O���s��
/// </summary>
void Direct3D::Render() {
	m_renderer.Render ();
}
