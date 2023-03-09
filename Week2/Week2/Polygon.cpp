#include "Polygon.h"
#include <cmath>

Polygon::Polygon() noexcept
    : fNumberOfVertices(0)
{
}

void Polygon::readData(std::istream& aIStream)
{
    Vector2D vertex;
    while (aIStream >> vertex)
    {
        if (fNumberOfVertices < MAX_VERTICES)
        {
            fVertices[fNumberOfVertices] = vertex;
            ++fNumberOfVertices;
        }
    }
}

size_t Polygon::getNumberOfVertices() const noexcept
{
    return fNumberOfVertices;
}

const Vector2D& Polygon::getVertex(size_t aIndex) const
{
    return fVertices[aIndex % fNumberOfVertices];
}

float Polygon::getPerimeter() const noexcept
{
    float perimeter = 0.0f;
    for (size_t i = 0; i < fNumberOfVertices; ++i)
    {
        const Vector2D& vertex1 = getVertex(i);
        const Vector2D& vertex2 = getVertex((i + 1) % fNumberOfVertices);
        const Vector2D segment = vertex2 - vertex1;
        perimeter += std::sqrt(segment.dot(segment));
    }
    return perimeter;
}

Polygon Polygon::scale(float aScalar) const noexcept
{
    Polygon result = *this;
    for (size_t i = 0; i < fNumberOfVertices; ++i)
    {
        result.fVertices[i] = fVertices[i] * aScalar;
    }
    return result;
}
