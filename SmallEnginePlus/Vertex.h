#pragma once
#include "pch.h"
#include "VertexCollection.h"

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
	Vertex (XMVECTOR pos);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Vertex ();

	/// <summary>
	/// 頂点座標を返す
	/// </summary>
	/// <returns>頂点座標</returns>
	XMVECTOR GetXMVECTORPosition();

	/// <summary>
	/// 複数の頂点座標から頂点情報の配列を生成する
	/// </summary>
	/// <param name="positions">頂点座標群</param>
	/// <returns>頂点情報の配列</returns>
	static class VertexCollection CreateVerticesFromXMFLOAT3Array (vector<XMFLOAT3> positions);
private:
	/// <summary>
	/// 頂点座標
	/// </summary>
	XMVECTOR m_pos;
};
