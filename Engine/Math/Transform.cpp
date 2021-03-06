#include "pch.h"
#include "Transform.h"


namespace nc
{
	std::istream& operator>>(std::istream& stream, Transform& transform)
	{
		stream >> transform.position;

		std::string line;
		std::getline(stream, line);
		transform.scale = stof(line);

		std::getline(stream, line);
		transform.angle = stof(line);

		return stream;
	}
	void Transform::Update()
	{
		Matrix3x3 mxScale;
		mxScale.Scale(scale);

		Matrix3x3 mxRotate;
		mxRotate.Rotate(angle);

		Matrix3x3 mxTranslate;
		mxTranslate.Translate(position);

		matrix = mxScale * mxRotate * mxTranslate;
	}
}