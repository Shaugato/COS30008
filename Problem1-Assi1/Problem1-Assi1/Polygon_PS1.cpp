#include "Polygon.h"

#include <cassert>



//float Polygon::getSignedArea() const noexcept
//{
//    float signedArea = 0.0f;
//    {
//        const Vector2D& vi = fVertices[i];
//        const Vector2D& vip1 = fVertices[(i + 1) % fNumberOfVertices];
//        signedArea += (vi.y() + vip1.y()) * (vi.x() - vip1.x());
//    }
//    signedArea /= 2.0f;
//
//    return signedArea;
//}


float Polygon::getSignedArea() const noexcept
{
    float aingnedArea =0.0f;
    for (size_t i = 0; i < fNumberOfVertices, ++i)
    {
        const Vector2D& vi = fVertices[i];
        const Vector2D& vip1 = fVertices[(i + 1) % fNumberOfVertices];
        aingnedArea += ((vi.y() + vip1.y() * (vi.x() - vip1.x())));
    }
    aingnedArea /= 2.0f;
    return aingnedArea;
}



//Polygon Polygon::transform(const Matrix3x3& aMatrix) const noexcept
//{
//    Polygon transformedPolygon;
//    for (size_t i = 0; i < fNumberOfVertices; ++i)
//    {
//        const Vector2D& vertex = fVertices[i];
//        Vector3D transformedVertex = aMatrix * Vector3D(vertex.x(), vertex.y(), 1.0f);
//        transformedPolygon.fVertices[i] = Vector2D(transformedVertex.x() / transformedVertex.w(),
//            transformedVertex.y() / transformedVertex.w());
//    }
//    transformedPolygon.fNumberOfVertices = fNumberOfVertices;
//    return transformedPolygon;
//}


Polygon Polygon::transform(const Matrix3x3& aMatrix) const noexcept
{
    Polygon transformPolygon;
    for (size_t i = 0; i < fNumberOfVertices; ++i)
    {
        const Vector2D& vertex = fVertices[i];
        Vector3D transformedVertex = aMatrix * Vector3D(vertex.x(), vertex.y(), 1.0f);
        transformPolygon.fVertices[i] = Vector2D(transformedVertex.x() / transformedVertex.w(), transformedVertex.y() / transformedVertex.w());

    }

    transformPolygon.fNumberOfVertices = fNumberOfVertices;
    return transformPolygon;
}




//Polygon Polygon::transform(const Matrix3x3& aMatrix) const noexcept
//{
//    Polygon transformedPolygon;
//    transformedPolygon.fNumberOfVertices = fNumberOfVertices;
//    for (size_t i = 0; i < fNumberOfVertices; ++i)
//    {
//        const Vector2D& v = fVertices[i];
//        Vector2D transformedVertex = aMatrix * v;
//        transformedPolygon.fVertices[i] = transformedVertex;
//    }
//    return transformedPolygon;
//}
