#pragma once
#include <fstream>
#include "Object/Actor.h"


class Projectile : public nc::Actor
{
	public:
		Projectile() {}
		virtual ~Projectile() {}

		virtual eType GetType() { return eType::PROJECTILE; }

		virtual bool Load(const std::string& filename) override;

		virtual void Update(float dt) override;
		virtual void Draw(Core::Graphics& graphics) override;

		virtual void OnCollision(Actor* actor) override;

		void SetThrust(float thrust) { m_thrust = thrust; }
		void SetTarget(Actor* actor) { m_target = actor; }

	protected:
		nc::Vector2 m_velocity;
		Actor* m_target = nullptr;
		float m_thrust = 0.0f;
		float m_lifetime = 3;

		
};