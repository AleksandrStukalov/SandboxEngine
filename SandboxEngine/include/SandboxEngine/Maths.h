#pragma once

namespace SE
{
    struct Vec2f
    {
    public:
        union {
            float x;
            float r;
            float s;
        };
        union {
            float y;
            float g;
            float t;
        };
        Vec2f()
            : x{ 0.0f }, y{ 0.0f } {}
        Vec2f(float x, float y)
            : x{ x }, y{ y } {}
        Vec2f(float value)
            : x{ value }, y{ value } {}
    };
    struct Vec3f
    {
    public:
        union {
            float x;
            float r;
            float s;
        };
        union {
            float y;
            float g;
            float t;
        };
        union {
            float z;
            float b;
            float r;
        };

        Vec3f(float x, float y, float z)
            : x{ x }, y{ y }, z{ z } {}
        Vec3f(float value)
            : x{ value }, y{ value }, z{ value } {}
    };
    struct Mat4f
    {
    public:
        union {
            float matrix[4][4];
            float m[4][4];
        };

        Mat4f(float a00, float a01, float a02, float a03,
              float a10, float a11, float a12, float a13,
              float a20, float a21, float a22, float a23,
              float a30, float a31, float a32, float a33)
        {
            m[0][0] = a00; m[0][1] = a01; m[0][2] = a02; m[0][3] = a03;
            m[1][0] = a10; m[1][1] = a11; m[1][2] = a12; m[1][3] = a13;
            m[2][0] = a20; m[2][1] = a21; m[2][2] = a22; m[2][3] = a23;
            m[3][0] = a30; m[3][1] = a31; m[3][2] = a32; m[3][3] = a33;
        }
        Mat4f()
        {
            m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
            m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
            m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
            m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
        }

        // Switches row and column indices
        void transpose()
        {
            Mat4f temp;
            for (int i{}; i < 4; ++i)
            {
                for (int j{}; j < 4; ++j)
                {
                    temp.matrix[i][j] = this->matrix[j][i];
                }
            }
            *this = temp;
        }

        void operator=(const Mat4f& right)
        {
            for (unsigned int i{}; i < 4; ++i)
            {
                for (unsigned int j{}; j < 4; ++j)
                {
                    this->matrix[i][j] = right.matrix[i][j];
                }
            }
        }

    };

}