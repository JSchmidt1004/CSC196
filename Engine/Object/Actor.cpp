#include "pch.h"
#include <fstream>
#include <string>
#include "Actor.h"

namespace nc
{
	bool nc::Actor::Load(const std::string& filename)
	{
		bool success = false;

		std::ifstream stream(filename);
		if (stream.is_open())
		{
			/*
			success = true;
			std::string shapename;

			//Load transforms
			stream >> m_transform;

			//Load Shape
			stream >> shapename;
			m_shape.Load(shapename);

			stream.close();
			*/
			success = true;

			Load(stream);

			stream.close();
		}
		return success;
	}

	void Actor::Load(std::istream& stream)
	{
		stream >> m_transform;

		std::string shapename;
		stream >> shapename;
		m_shape.Load(shapename);
	}


	void Actor::Update(float dt)
	{
		// nothing
	}

	void Actor::Draw(Core::Graphics& graphics)
	{
		m_shape.Draw(graphics, m_transform);
	}

	float Actor::GetRadius()
	{
		return m_shape.GetRadius() * m_transform.scale;
	}

}