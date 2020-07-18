#pragma once
#include <fstream>
#include "Object/Actor.h"


class Player : public nc::Actor
{
	public: 
		Player() {}
		virtual ~Player() {}

		virtual bool Load(const std::string& filename) override;
		virtual void Update(float dt) override;
		virtual void Draw(Core::Graphics& graphics) override;

	protected:
		nc::Vector2 m_velocity;
		float m_thrust;
		float m_rotation;
};