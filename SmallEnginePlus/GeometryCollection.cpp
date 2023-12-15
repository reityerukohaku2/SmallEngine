#include "pch.h"
#include "GeometryCollection.h"

/// <summary>
/// �`��Ɋ܂܂��S�Ă̒��_����Ԃ�
/// </summary>
/// <returns></returns>
UINT GeometryCollection::GetVertexNum ()
{
    UINT vertexNum = 0;

    for (auto geometry: *this) {
        vertexNum += geometry.GetVertexNum ();
    }

    return vertexNum;
}

/// <summary>
/// �`��Ɋ܂܂��S�Ă̒��_�C���f�b�N�X����Ԃ�
/// </summary>
/// <returns></returns>
UINT GeometryCollection::GetIndexNum ()
{
    UINT indexNum = 0;

    for (auto geometry: *this) {
        indexNum += geometry.GetIndexNum ();
    }

    return indexNum;
}

/// <summary>
/// �`��̃o�C�g����Ԃ�
/// </summary>
/// <returns></returns>
UINT GeometryCollection::GetGeometriesSize ()
{
    return GetVertexNum () * sizeof (Vertex);
}

/// <summary>
/// ���_�C���f�b�N�X�̃o�C�g����Ԃ�
/// </summary>
/// <returns>���_�C���f�b�N�X�̃o�C�g��</returns>
UINT GeometryCollection::GetIndicesSize ()
{
    return GetIndexNum () * sizeof (DWORD);
}

/// <summary>
/// �S�Ă̒��_�����擾����
/// </summary>
vector<Vertex> GeometryCollection::GetVertices ()
{
    vector<Vertex> allVertices;

    // ���g�̗v�f��1�����o���ď�������
    for (auto& geometry : *this) {
        auto vertices = geometry.GetVertices();
        allVertices.reserve(allVertices.size() + vertices.size());
        allVertices.insert(allVertices.end(), vertices.begin(), vertices.end());
    }

    return allVertices;
}

UINT GeometryCollection::GetVerticesSize ()
{
    return GetVertices().size() * sizeof(XMVECTOR);
}

/// <summary>
/// ���_�C���f�b�N�X���擾����
/// </summary>
/// <returns></returns>
VertexIndex GeometryCollection::GetIndices ()
{
    VertexIndex allIndices;

    for (auto& geometry : *this) {
        auto indices = geometry.GetIndices ();
        allIndices.reserve (allIndices.size () + indices.size());
        allIndices.insert (allIndices.end (), indices.begin (), indices.end ());
    }

    return allIndices;
}

/// <summary>
/// ���_�����Čv�Z����
/// </summary>
/// <returns>�S���_��</returns>
UINT GeometryCollection::CountVertexNum ()
{
    UINT vertexNum = 0;
    for (auto& geometry : *this) {
        vertexNum += geometry.GetVertexNum ();
    }

    return vertexNum;
}

/// <summary>
/// ���_�C���f�b�N�X�����Čv�Z����
/// </summary>
/// <returns>�S���_�C���f�b�N�X��</returns>
UINT GeometryCollection::CountIndexNum ()
{
    UINT indexNum = 0;
    for (auto& geometry : *this) {
        indexNum += geometry.GetIndexNum ();
    }

    return indexNum;
}
