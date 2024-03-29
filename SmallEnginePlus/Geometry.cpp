#include "pch.h"
#include "Geometry.h"

/// <summary>
/// コンストラクタ(頂点インデックスあり)
/// </summary>
/// <param name="triangles"></param>
Geometry::Geometry (vector<Vertex> vertices, VertexIndex indices) {
	m_vertices = std::move (vertices);
	m_indices = std::move (indices);
}

/// <summary>
/// コンストラクタ(頂点インデックスなし)
/// </summary>
/// <param name="triangles"></param>
Geometry::Geometry (vector<Vertex> vertices) {
	m_vertices = std::move (vertices);
}

/// <summary>
/// デストラクタ
/// </summary>
Geometry::~Geometry () {
	for (const auto vertex : m_vertices) {
		vertex.~Vertex ();
	}

	m_indices.~VertexIndex ();

	m_vertices.clear();
}

/// <summary>
/// 頂点情報を取得する
/// </summary>
/// <returns>頂点情報</returns>
vector<Vertex> Geometry::GetVertices () {
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

Geometry Geometry::CreateGeometryFromPosAndIndex (vector<XMFLOAT3> vertexPositions, vector<DWORD> indicesData)
{
	auto vertices = Vertex::CreateVerticesFromXMFLOAT3Array (vertexPositions);
	VertexIndex indices = move(indicesData);

	return Geometry (vertices, indices);
}


/// <summary>
/// 頂点数を取得する
/// </summary>
/// <returns>形状の頂点数</returns>
int Geometry::GetVertexNum () {
	return m_vertices.size();
}

/// <summary>
/// 頂点インデックス数を取得する
/// </summary>
/// <returns>形状の頂点インデックス数</returns>
int Geometry::GetIndexNum ()
{
	return m_indices.size();
}

/// <summary>
/// 頂点インデックスを取得する
/// </summary>
/// <returns></returns>
VertexIndex Geometry::GetIndices () {
	return m_indices;
}