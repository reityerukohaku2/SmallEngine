#include "pch.h"
#include "Direct3D.h"
#include <windows.h>

void Direct3D::CreateInstance() 
{
	// インスタンスを削除してから生成
	DeleteInstance();

	s_instance = new Direct3D();

}

void Direct3D::DeleteInstance() 
{
	// インスタンスが存在する場合、削除
	if (s_instance != nullptr)
	{
		delete s_instance;
		s_instance = nullptr;
	}
}

Direct3D& Direct3D::GetInstance() {
	// インスタンスが存在しない場合、生成
	if (s_instance == nullptr) {
		CreateInstance();
	}
	return *s_instance;
}

/// <summary>
/// 初期化メソッド
/// </summary>
/// <param name="hWnd">ウィンドウハンドラ</param>
/// <returns>初期化成功時にtrue、失敗時にfalse</returns>
bool Direct3D::Initialize(HWND hWnd)
{
	// 形状の作成
	InitModels ();

	m_renderer = Renderer (m_geometries, hWnd);

	return true;
}

/// <summary>
/// モデルの初期化
/// </summary>
/// <returns>成功したらSUCCEEDED</returns>
HRESULT Direct3D::InitModels () {
	// 頂点の作成
	vector<XMFLOAT3> vertexPositions = 
	{
		 { 0.0f, 0.57733f , 0.0f },
		 { -0.5f, -0.288667f , 0.0f },
		 { 0.5f, -0.288667f , 0.0f }
	};

	// 形状の作成
	Geometry geometry = Geometry::CreateGeometryFromXMFloat3Array (vertexPositions);

	// 形状の追加
	m_geometries.push_back(geometry);

	return S_OK;
}

/// <summary>
/// レンダリングを行う
/// </summary>
void Direct3D::Render() {
	m_renderer.Render ();
}
