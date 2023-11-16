#pragma once
#include "pch.h"

/// <summary>
/// 頂点インデックス
/// </summary>
class VertexIndex
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="index">頂点インデックス</param>
	VertexIndex (DWORD index);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~VertexIndex ();
private:
	/// <summary>
	/// 頂点インデックス
	/// </summary>
	DWORD m_index;
};
