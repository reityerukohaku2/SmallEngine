#pragma once
#include "pch.h"
using namespace DirectX;
using namespace std;
using winrt::com_ptr;
using std::shared_ptr;

/// <summary>
/// 頂点情報を持つクラス
/// </summary>
class Vertex
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">頂点位置</param>
	Vertex (XMFLOAT3 pos);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Vertex ();

	/// <summary>
	/// 頂点座標を返す
	/// </summary>
	/// <returns>頂点座標</returns>
	XMFLOAT3 GetXMFLOATPosition();

	/// <summary>
	/// 複数の頂点座標から頂点情報の配列を生成する
	/// </summary>
	/// <param name="positions">頂点座標群</param>
	/// <returns>頂点情報の配列</returns>
	static vector<Vertex> CreateVerticesFromXMFloat3Array (vector<XMFLOAT3> positions);
private:
	/// <summary>
	/// 頂点座標
	/// </summary>
	XMFLOAT3 m_pos;
};
