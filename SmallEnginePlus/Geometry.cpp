#include "Geometry.h"

/// <summary>
/// コンストラクタ(頂点インデックスあり)
/// </summary>
/// <param name="triangles"></param>
Geometry::Geometry (vector<shared_ptr<Vertex>> vertices, vector<shared_ptr<VertexIndex>> indices, com_ptr<VertexBuffer> vertexBuffer) {
	m_vertices = std::move (vertices);
	m_indices = std::move (indices);
	m_vertexBuffer = vertexBuffer;
}

/// <summary>
/// コンストラクタ(頂点インデックスなし)
/// </summary>
/// <param name="triangles"></param>
Geometry::Geometry (vector<shared_ptr<Vertex>> vertices, com_ptr<VertexBuffer> vertexBuffer) {
	this->m_vertices = std::move (vertices);

	void* data;
	CD3DX12_RANGE readRange (0, 0);

	m_vertexBuffer = vertexBuffer;

	m_vertexBuffer->Map (0, nullptr, &data);
	memcpy (data, vertices.data (), vertices.size () * sizeof (Vertex));
	m_vertexBuffer->Unmap (0, nullptr);
}

/// <summary>
/// デストラクタ
/// </summary>
Geometry::~Geometry () {
	for (const auto vertex : m_vertices) {
		vertex->~Vertex ();
	}

	for (const auto index : m_indices) {
		index->~VertexIndex ();
	}

	m_vertices.clear();
}

/// <summary>
/// 頂点情報を取得する
/// </summary>
/// <returns>頂点情報</returns>
vector<shared_ptr<Vertex>> Geometry::GetVertices () {
	return m_vertices;
}

/// <summary>
/// 頂点情報配列を取得する
/// </summary>
/// <returns>頂点情報配列</returns>
shared_ptr<Vertex>* Geometry::GetVertexArray () {
	return m_vertices.data ();
}

/// <summary>
/// 頂点数を取得する
/// </summary>
/// <returns>形状の頂点数</returns>
int Geometry::GetVertexNum () {
	return this->m_vertices.size();
}