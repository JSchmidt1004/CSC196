#pragma once
#include "Vector2.h"

namespace nc
{
	struct Matrix3x3
	{
		float m[3][3]; //Column / Row
		//m[0][0] m[1][0] m[2][0]
		//m[0][1] m[1][1] m[2][1]
		//m[0][2] m[1][2] m[2][2]

		/*
		Matrix3x3() = default;
		Matrix3x3(const Vector2& column1, const Vector2& column2)
		{
			//Column 1
			m[0][0] = column1[0];
			m[0][1] = column1[1];

			//Column 2
			m[1][0] = column2[0];
			m[1][1] = column2[1];
		}
		*/

		void Scale(float s)
		{
			//Column 1
			m[0][0] = s;
			m[0][1] = 0.0f;
			m[0][2] = 0.0f;

			//Column 2
			m[1][0] = 0.0f;
			m[1][1] = s;
			m[1][2] = 0.0f;

			//Column 3
			m[2][0] = 0.0f;
			m[2][1] = 0.0f;
			m[2][2] = 1.0f;
		}
		void Scale(float sx, float sy)
		{
			//Column 1
			m[0][0] = sx;
			m[0][1] = 0.0f;
			m[0][2] = 0.0f;

			//Column 2
			m[1][0] = 0.0f;
			m[1][1] = sy;
			m[1][2] = 0.0f;

			//Column 3
			m[2][0] = 0.0f;
			m[2][1] = 0.0f;
			m[2][2] = 1.0f;
		}
		void Scale(const Vector2& s)
		{
			//Column 1
			m[0][0] = s.x;
			m[0][1] = 0.0f;
			m[0][2] = 0.0f;

			//Column 2
			m[1][0] = 0.0f;
			m[1][1] = s.y;
			m[1][2] = 0.0f;

			//Column 3
			m[2][0] = 0.0f;
			m[2][1] = 0.0f;
			m[2][2] = 1.0f;
		}

		void Rotate(float angle)
		{
			//Column 1
			m[0][0] = std::cos(angle);
			m[0][1] = -std::sin(angle);
			m[0][2] = 0.0f;

			//Column 2
			m[1][0] = std::sin(angle);
			m[1][1] = std::cos(angle);
			m[1][2] = 0.0f;

			//Column 3
			m[2][0] = 0.0f;
			m[2][1] = 0.0f;
			m[2][2] = 1.0f;
		}

		void Translate(const Vector2& v)
		{
			//Column 1
			m[0][0] = 1.0f;
			m[0][1] = 0.0f;
			m[0][2] = v.x;

			//Column 2
			m[1][0] = 0.0f;
			m[1][1] = 1.0f;
			m[1][2] = v.y;

			//Column 3
			m[2][0] = 0.0f;
			m[2][1] = 0.0f;
			m[2][2] = 1.0f;
		}

		void SetIdentity()
		{
			//Column 1
			m[0][0] = 1.0f;
			m[0][1] = 0.0f;
			m[0][2] = 0.0f;

			//Column 2
			m[1][0] = 0.0f;
			m[1][1] = 1.0f;
			m[1][2] = 0.0f;

			//Column 3
			m[2][0] = 0.0f;
			m[2][1] = 0.0f;
			m[2][2] = 1.0f;
		}

		Matrix3x3 operator * (const Matrix3x3& mx)
		{
			Matrix3x3 result;

			//Column 1
			result.m[0][0] = (m[0][0] * mx.m[0][0]) + (m[1][0] * mx.m[0][1]) + (mx.m[2][0] * mx.m[0][2]);
			result.m[0][1] = (m[0][1] * mx.m[0][0]) + (m[1][1] * mx.m[0][1]) + (mx.m[2][1] * mx.m[0][2]);
			result.m[0][2] = (m[0][2] * mx.m[0][0]) + (m[1][2] * mx.m[0][1]) + (mx.m[2][2] * mx.m[0][2]);

			//Column 2
			result.m[1][0] = (m[0][0] * mx.m[1][0]) + (m[1][0] * mx.m[1][1]) + (mx.m[2][0] * mx.m[1][2]);
			result.m[1][1] = (m[0][1] * mx.m[1][0]) + (m[1][1] * mx.m[1][1]) + (mx.m[2][1] * mx.m[1][2]);
			result.m[1][2] = (m[0][2] * mx.m[1][0]) + (m[1][2] * mx.m[1][1]) + (mx.m[2][2] * mx.m[1][2]);

			//Column 3
			result.m[2][0] = (m[0][0] * mx.m[2][0]) + (m[1][0] * mx.m[2][1]) + (mx.m[2][0] * mx.m[2][2]);
			result.m[2][1] = (m[0][1] * mx.m[2][0]) + (m[1][1] * mx.m[2][1]) + (mx.m[2][1] * mx.m[2][2]);
			result.m[2][2] = (m[0][2] * mx.m[2][0]) + (m[1][2] * mx.m[2][1]) + (mx.m[2][2] * mx.m[2][2]);

			return result;
		}

		Vector2 operator * (const Vector2& v)
		{
			Vector2 result;

			result.x = v.x * m[0][0] + v.y * m[0][1] + m[0][2];
			result.y = v.x * m[1][0] + v.y * m[1][1] + m[1][2];

			return result;
		}
		friend Vector2 operator * (const Vector2& v, const Matrix3x3 mx)
		{
			Vector2 result;

			result.x = v.x * mx.m[0][0] + v.y * mx.m[0][1] + mx.m[0][2];
			result.y = v.x * mx.m[1][0] + v.y * mx.m[1][1] + mx.m[1][2];

			return result;
		}

	};
}