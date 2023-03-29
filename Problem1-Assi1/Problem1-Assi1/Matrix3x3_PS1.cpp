
// COS30008, tutorial 3, 2023

#define _USE_MATH_DEFINES     // must be defined before any #include

#include "Matrix3x3.h"

#include <cassert>
#include <cmath>



Matrix3x3 Matrix3x3::operator*(const Matrix3x3& aOther) const noexcept
{
    //Vector3D row1 = Vector3D(row(0).dot(aOther.column(0)),
    //    row(0).dot(aOther.column(1)),
    //    row(0).dot(aOther.column(2)));

    //Vector3D row2 = Vector3D(row(1).dot(aOther.column(0)),
    //    row(1).dot(aOther.column(1)),
    //    row(1).dot(aOther.column(2)));

    //Vector3D row3 = Vector3D(row(2).dot(aOther.column(0)),
    //    row(2).dot(aOther.column(1)),
    //    row(2).dot(aOther.column(2)));

    //return Matrix3x3(row1, row2, row3);

    Vector3D row1 = Vector3D(row(0).dot(aOther.column(0)),
        (row(0).dot(aOther.column(1))), row(0).dot(aOther.column(2)));

    Vector3D row2 = Vector3D(row(1).dot(aOther.column(0)), row(1).dot(aOther.column(1)), row(1).dot(aOther.column(2)));
    Vector3D row3 = Vector3D(row(2).dot(aOther.column(0)), row(2).dot(aOther.column(1)), row(2).dot(aOther.column(2)));

    return Matrix3x3(row1, row2, row3);
}


float Matrix3x3::det() const noexcept
{
    //float a = fRows[0][0];
    //float b = fRows[0][1];
    //float c = fRows[0][2];
    //float d = fRows[1][0];
    //float e = fRows[1][1];
    //float f = fRows[1][2];
    //float g = fRows[2][0];
    //float h = fRows[2][1];
    //float i = fRows[2][2];
    //return a * (e * i - f * h) - b * (d * i - f * g) + c * (d * h - e * g);

    float a = fRows[0][0];
    float b = fRows[0][1];
    float c = fRows[0][2];
    float d = fRows[1][0];
    float e = fRows[1][1];
    float f = fRows[1][2];
    float g = fRows[2][0];
    float h = fRows[2][1];
    float i = fRows[2][2];

    return  a * (e * i - h * f) - b * (d * i - f * g) + c * (d * h - e * g);
}

//bool Matrix3x3::hasInverse() const noexcept
//{
//    float determinant = det();
//    return (determinant > 0.0f || determinant < 0.0f);
//}
//
//Matrix3x3 Matrix3x3::transpose() const noexcept
//{
//
//
//    return Matrix3x3(Vector3D(fRows[0][0], fRows[1][0], fRows[2][0]),
//        Vector3D(fRows[0][1], fRows[1][1], fRows[2][1]),
//        Vector3D(fRows[0][2], fRows[1][2], fRows[2][2]));
//
//}

bool Matrix3x3::hasInverse() const noexcept
{
    float determinat = det();
    return(determinat < 0.0f || determinat > 0.0f);
}

Matrix3x3 Matrix3x3::transpose() const noexcept
{
    return Matrix3x3(Vector3D(fRows[0][0], fRows[1][0], fRows[2][0]),
        Vector3D(fRows[0][1], fRows[1][1], fRows[2][1]),
        Vector3D(fRows[0][2], fRows[1][2], fRows[2][2]));
}

Matrix3x3 Matrix3x3::inverse() const
{

    if (hasInverse())
    {


        float a = fRows[0][0];
        float b = fRows[0][1];
        float c = fRows[0][2];
        float d = fRows[1][0];
        float e = fRows[1][1];
        float f = fRows[1][2];
        float g = fRows[2][0];
        float h = fRows[2][1];
        float i = fRows[2][2];
        float detInv = 1.0f / det();
        float a11 = (e * i - f * h) * detInv;
        float a12 = (c * h - b * i) * detInv;
        float a13 = (b * f - c * e) * detInv;
        float a21 = (f * g - d * i) * detInv;
        float a22 = (a * i - c * g) * detInv;
        float a23 = (c * d - a * f) * detInv;
        float a31 = (d * h - e * g) * detInv;
        float a32 = (b * g - a * h) * detInv;
        float a33 = (a * e - b * d) * detInv;

        return Matrix3x3(Vector3D(a11, a12, a13), Vector3D(a21, a22, a23), Vector3D(a31, a32, a33));
    }
    else
    {
        std::cout << "Matrix is not invertible" << std::endl;
    }
}

std::ostream& operator<<(std::ostream& aOStream, const Matrix3x3& aMatrix)
{
    aOStream <<"["<< aMatrix.row(0) << "," << aMatrix.row(1) << "," << aMatrix.row(2) <<"]"<< std::endl;
    return aOStream;
}



