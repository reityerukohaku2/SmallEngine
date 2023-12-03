#pragma once
#include "pch.h"
#include "Vertex.h"
#include "VertexIndex.h"
#include "VertexBuffer.h"
#include "VertexCollection.h"

using namespace std;
using winrt::com_ptr;

/// <summary>
/// 頂点を組み合わせた形状
/// </summary>
class Geometry
{
public:
	/// <summary>
	/// コンストラクタ(頂点インデックスあり)
	/// </summary>
	/// <param name="vertices">頂点</param>
	/// <param name="indices">頂点インデックス</param>
	Geometry (VertexCollection vertices, vector<VertexIndex> indices);

	/// <summary>
	/// コンストラクタ(頂点インデックスなし)
	/// </summary>
	/// <param name="vertices">頂点</param>
	Geometry (VertexCollection vertices);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Geometry ();

	/// <summary>
	/// 頂点数を取得する
	/// </summary>
	/// <returns>形状の頂点数</returns>
	int GetVertexNum ();

	/// <summary>
	/// 頂点情報を取得する
	/// </summary>
	/// <returns>頂点情報</returns>
	VertexCollection GetVertices ();

	/// <summary>
	/// 頂点情報配列を取得する
	/// </summary>
	/// <returns>頂点情報配列</returns>
	shared_ptr<Vertex> GetVertexArray ();

	/// <summary>
	/// 頂点座標群から形状を生成する
	/// </summary>
	/// <param name="vertexPositions">頂点座標群</param>
	/// <returns>形状</returns>
	static Geometry CreateGeometryFromXMFloat3Array (vector<XMFLOAT3> vertexPositions);

private:
	/// <summary>
	/// 頂点
	/// </summary>
	VertexCollection m_vertices;

	/// <summary>
	/// 頂点インデックス
	/// </summary>
	vector<VertexIndex> m_indices;

};
