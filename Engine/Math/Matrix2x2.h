#pragma once
#include "Vector2.h"

namespace nc
{
	struct Matrix2x2
	{
		float m[2][2]; //Column / Row
		//m[0][0] m[1][0]
		//m[0][1] m[1][1]
		
		Matrix2x2() = default;
		Matrix2x2(const Vector2& column1, const Vector2& column2) 
		{
			//Column 1
			m[0][0] = column1[0];
			m[0][1] = column1[1];

			//Column 2
			m[1][0] = column2[0];
			m[1][1] = column2[1];
		}

		void Scale(float s)
		{
			//Column 1
			m[0][0] = s;
			m[0][1] = 0.0f;

			//Column 2
			m[1][0] = 0.0f;
			m[1][1] = s;
		}
		void Scale(float sx, float sy)
		{
			//Column 1
			m[0][0] = sx;
			m[0][1] = 0.0f;

			//Column 2
			m[1][0] = 0.0f;
			m[1][1] = sy;
		}
		void Scale(const Vector2& s)
		{
			//Column 1
			m[0][0] = s.x;
			m[0][1] = 0.0f;

			//Column 2
			m[1][0] = 0.0f;
			m[1][1] = s.y;
		}

		void Rotate(float angle)
		{
			//Column 1
			m[0][0] = std::cos(angle);
			m[0][1] = -std::sin(angle);

			//Column 2
			m[1][0] = std::sin(angle);
			m[1][1] = std::cos(angle);
		}

		void SetIdentity()
		{
			//Column 1
			m[0][0] = 1.0f;
			m[0][1] = 0.0f;

			//Column 2
			m[1][0] = 0.0f;
			m[1][1] = 1.0f;
		}

		Matrix2x2 operator * (const Matrix2x2& mx)
		{
			Matrix2x2 result;

			//Column 1
			result.m[0][0] = (m[0][0] * mx.m[0][0]) + (m[1][0] * mx.m[0][1]);
			result.m[0][1] = (m[0][1] * mx.m[0][0]) + (m[1][1] * mx.m[0][1]);

			//Column 2
			result.m[1][0] = (m[0][0] * mx.m[1][0]) + (m[1][0] * mx.m[1][1]);
			result.m[1][1] = (m[0][1] * mx.m[1][0]) + (m[1][1] * mx.m[1][1]);

			return result;
		}

		Vector2 operator * (const Vector2& v)
		{
			Vector2 result;

			result.x = v.x * m[0][0] + v.y * m[0][1];
			result.y = v.x * m[1][0] + v.y * m[1][1];

			return result;
		}
		friend Vector2 operator * (const Vector2& v, const Matrix2x2 mx)
		{
			Vector2 result;

			result.x = v.x * mx.m[0][0] + v.y * mx.m[0][1];
			result.y = v.x * mx.m[1][0] + v.y * mx.m[1][1];

			return result;
		}

	};
}