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
	Geometry (VertexCollection vertices, VertexIndex indices);

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
	/// 頂点インデックス数を取得する
	/// </summary>
	/// <returns>形状の頂点インデックス数</returns>
	int GetIndexNum ();

	/// <summary>
	/// 頂点情報を取得する
	/// </summary>
	/// <returns>頂点情報</returns>
	VertexCollection GetVertices ();

	/// <summary>
	/// 頂点インデックスを取得する
	/// </summary>
	/// <returns></returns>
	VertexIndex GetIndices ();

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

	/// <summary>
	/// 頂点座標群と頂点インデックスから形状を生成する
	/// </summary>
	/// <param name="vertexPositions">頂点座標</param>
	/// <param name="indice">頂点インデックス</param>
	/// <returns>形状</returns>
	static Geometry CreateGeometryFromPosAndIndex (vector<XMFLOAT3> vertexPositions, vector<DWORD> indices);

	/// <summary>
	/// 頂点座標群と頂点インデックスから形状を生成する
	/// </summary>
	/// <param name="vertexPositions">頂点座標</param>
	/// <param name="indice">頂点インデックス</param>
	/// <returns>形状</returns>
	static Geometry CreateGeometryFromPosAndIndex (vector<XMFLOAT3> vertexPositions, VertexIndex indices);

private:
	/// <summary>
	/// 頂点群
	/// </summary>
	VertexCollection m_vertices;

	/// <summary>
	/// 頂点インデックス
	/// </summary>
	VertexIndex m_indices;

};
