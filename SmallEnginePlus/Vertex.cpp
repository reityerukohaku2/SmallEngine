#include "pch.h"
#include "Vertex.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="pos">頂点位置</param>
Vertex::Vertex (XMVECTOR pos) {
	this->m_pos = pos;
}

/// <summary>
/// デストラクタ
/// </summary>
Vertex::~Vertex () {}

/// <summary>
/// 頂点座標を返す
/// </summary>
/// <returns>頂点座標</returns>
XMVECTOR Vertex::GetXMVECTORPosition ()
{
	return m_pos;
}

/// <summary>
/// 複数の頂点座標から頂点情報の配列を生成する
/// </summary>
/// <param name="positions">頂点座標群</param>
/// <returns>頂点情報の配列</returns>
VertexCollection Vertex::CreateVerticesFromXMFLOAT3Array (vector<XMFLOAT3> positions) {
	VertexCollection vertexArray = {};

	// positionsからpositionを取り出し、Vertexオブジェクトを生成
	for (const auto position : positions) {
		XMVECTOR vectorPos = XMLoadFloat3(&position);
		Vertex vertex = Vertex (vectorPos);

		// VertexオブジェクトをvertexArrayに格納していく
		vertexArray.push_back (vertex);
	}

	return vertexArray;
}
