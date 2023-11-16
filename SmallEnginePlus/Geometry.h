#pragma once
#include <vector>
#include <d3d12.h>
#include "pch.h"
#include "Vertex.h"
#include "VertexIndex.h"
#include "VertexBuffer.h"

using namespace std;
using winrt::com_ptr;

/// <summary>
/// 頂点を組み合わせた形状
/// </summary>
class Geometry : public winrt::implements<Geometry>
{
public:
	/// <summary>
	/// コンストラクタ(頂点インデックスあり)
	/// </summary>
	/// <param name="vertices">頂点</param>
	/// <param name="indices">頂点インデックス</param>
	Geometry (vector<shared_ptr<Vertex>> vertices, vector<shared_ptr<VertexIndex>> indices, com_ptr<VertexBuffer> vertexBuffer);

	/// <summary>
	/// コンストラクタ(頂点インデックスなし)
	/// </summary>
	/// <param name="vertices">頂点</param>
	Geometry (vector<shared_ptr<Vertex>> vertices, com_ptr<VertexBuffer> vertexBuffer);

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
	vector<shared_ptr<Vertex>> GetVertices ();

	/// <summary>
	/// 頂点情報配列を取得する
	/// </summary>
	/// <returns>頂点情報配列</returns>
	shared_ptr<Vertex>* GetVertexArray ();

private:
	/// <summary>
	/// 頂点
	/// </summary>
	vector<shared_ptr<Vertex>> m_vertices;

	/// <summary>
	/// 頂点インデックス
	/// </summary>
	vector<shared_ptr<VertexIndex>> m_indices;

	/// <summary>
	/// 頂点バッファ
	/// </summary>
	com_ptr<VertexBuffer> m_vertexBuffer;
};
