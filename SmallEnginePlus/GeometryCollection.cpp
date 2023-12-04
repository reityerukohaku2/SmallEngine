#include "pch.h"
#include "GeometryCollection.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="geometries">Geometry�̔z��</param>
GeometryCollection::GeometryCollection (vector<Geometry> geometries)
{
    m_geometries = geometries;
    m_vertexNum = CountVertexNum ();
}

/// <summary>
/// �z��̖����ɗv�f��ǉ�����
/// </summary>
/// <param name="geometry">�ǉ�����v�f</param>
void GeometryCollection::push_back (Geometry geometry)
{
    m_geometries.push_back (geometry);
    m_vertexNum = CountVertexNum ();
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
    return m_vertexNum;
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
    VertexCollection allVertices;
    vector<Vertex> hoge, hoge2;

    for (auto geometry : m_geometries) {
        auto vertices = geometry.GetVertices ();

        // �����ɔz���ǉ�
        allVertices.insert (allVertices.end(), vertices.begin(), vertices.end());
    }

    return allVertices;
}

/// <summary>
/// ���_�����Čv�Z����
/// </summary>
/// <returns>�S���_��</returns>
UINT GeometryCollection::CountVertexNum ()
{
    UINT vertexNum = 0;
    for (auto geometry : m_geometries) {
        vertexNum += geometry.GetVertexNum ();
    }

    return vertexNum;
}

/// <summary>
/// targetPos�̈ʒu�ɔz���}������
/// </summary>
/// <param name="targetPos">�}����</param>
/// <param name="begin">�}������z��̊J�n�n�_</param>
/// <param name="end">�}������z��̏I���n�_</param>
/// <returns></returns>
typename vector<Geometry>::const_iterator GeometryCollection::insert 
(
    typename vector<Geometry>::const_iterator targetPos, 
    typename vector<Geometry>::const_iterator begin, 
    typename vector<Geometry>::const_iterator end
){
    return m_geometries.insert (targetPos, begin, end);
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
    m_vertexNum = 0;
}

