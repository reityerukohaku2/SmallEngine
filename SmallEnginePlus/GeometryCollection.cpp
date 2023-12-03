#include "pch.h"
#include "GeometryCollection.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="geometries">Geometry�̔z��</param>
GeometryCollection::GeometryCollection (vector<Geometry> geometries)
{
    m_geometries = geometries;
}

/// <summary>
/// �z��̖����ɗv�f��ǉ�����
/// </summary>
/// <param name="geometry">�ǉ�����v�f</param>
void GeometryCollection::push_back (Geometry geometry)
{
    m_geometries.push_back (geometry);
}

/// <summary>
/// �z��̐擪�|�C���^��Ԃ�
/// </summary>
/// <returns>�z��̐擪�|�C���^</returns>
Geometry* GeometryCollection::data () {
    return m_geometries.data ();
}

/// <summary>
/// �z��̏I���n�_�������C�e���[�^�[��Ԃ�
/// </summary>
/// <returns></returns>
typename vector<Geometry>::const_iterator GeometryCollection::end () {
    return m_geometries.end ();
}

typename vector<Geometry>::const_iterator GeometryCollection::begin ()
{
    return m_geometries.begin ();
}

/// <summary>
/// �`��Ɋ܂܂��S�Ă̒��_����Ԃ�
/// </summary>
/// <returns></returns>
UINT GeometryCollection::GetVertexNum ()
{
    UINT vertexNum = 0;
    for (auto geometry: m_geometries) {
        vertexNum += geometry.GetVertexNum ();
    }

    return vertexNum;
}

/// <summary>
/// �`��̃o�C�g����Ԃ�
/// </summary>
/// <returns></returns>
UINT GeometryCollection::GetGeometriesSize ()
{
    return this->GetVertexNum () * sizeof(Vertex);
}

/// <summary>
/// �S�Ă̒��_�����擾����
/// </summary>
VertexCollection GeometryCollection::GetVertices ()
{
    vector<Vertex> allVertices;
    for (auto geometry : m_geometries) {
        auto vertices = geometry.GetVertices ();
        copy (vertices.begin (), vertices.end (), back_inserter (allVertices));
    }

    return allVertices;
}

/// <summary>
/// �z��̗v�f����Ԃ�
/// </summary>
/// <returns></returns>
size_t GeometryCollection::size ()
{
    return m_geometries.size();
}

/// <summary>
/// �z��v�f��S�č폜
/// </summary>
void GeometryCollection::clear ()
{
    m_geometries.clear ();
}

