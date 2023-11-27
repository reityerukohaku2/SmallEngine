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
	// ���_�̍쐬
	vector<XMFLOAT3> vertexPositions = 
	{
		 { 0.0f, 0.57733f , 0.0f },
		 { -0.5f, -0.288667f , 0.0f },
		 { 0.5f, -0.288667f , 0.0f }
	};

	// �`��̍쐬
	Geometry geometry = Geometry::CreateGeometryFromXMFloat3Array (vertexPositions);

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
