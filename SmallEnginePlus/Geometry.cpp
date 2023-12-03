#include "pch.h"
#include "Geometry.h"

/// <summary>
/// コンストラクタ(頂点インデックスあり)
/// </summary>
/// <param name="triangles"></param>
Geometry::Geometry (VertexCollection vertices, vector<VertexIndex> indices) {
	m_vertices = std::move (vertices);
	m_indices = std::move (indices);
}

/// <summary>
/// コンストラクタ(頂点インデックスなし)
/// </summary>
/// <param name="triangles"></param>
Geometry::Geometry (VertexCollection vertices) {
	this->m_vertices = std::move (vertices);

	void* data;
	CD3DX12_RANGE readRange (0, 0);
}

/// <summary>
/// デストラクタ
/// </summary>
Geometry::~Geometry () {
	for (const auto vertex : m_vertices) {
		vertex.~Vertex ();
	}

	for (const auto index : m_indices) {
		index.~VertexIndex ();
	}

	m_vertices.clear();
}

/// <summary>
/// 頂点情報を取得する
/// </summary>
/// <returns>頂点情報</returns>
VertexCollection Geometry::GetVertices () {
	return m_vertices;
}

/// <summary>
/// 頂点座標群から形状を生成する
/// </summary>
/// <param name="vertexPositions">頂点座標群</param>
/// <returns>形状</returns>
Geometry Geometry::CreateGeometryFromXMFloat3Array (vector<XMFLOAT3> vertexPositions)
{
	auto vertices = Vertex::CreateVerticesFromXMFLOAT3Array (vertexPositions);
	return Geometry (vertices);
}


/// <summary>
/// 頂点数を取得する
/// </summary>
/// <returns>形状の頂点数</returns>
int Geometry::GetVertexNum () {
	return this->m_vertices.size();
}