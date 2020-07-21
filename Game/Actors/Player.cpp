#include "Player.h"
#include "Projectile.h"
#include "Object/Scene.h"

bool Player::Load(const std::string& filename)
{
	bool success = false;

	std::ifstream stream(filename);
	if (stream.is_open())
	{
		success = true;

		// load the base actor members
		Actor::Load(stream);

		// stream into thrust
		stream >> m_thrust;
		// stream into rotation rate
		stream >> m_rotation;

		stream.close();
	}

	return success;
}

void Player::Update(float dt)
{
	m_fireTimer += dt;

	if (Core::Input::IsPressed(VK_SPACE) && m_fireTimer >= m_fireRate)
	{
		m_fireTimer = 0.0f;
		nc::Actor* projectile = new Projectile;
		projectile->Load("Projectile.txt");
		projectile->GetTransform().position = m_transform.position;
		projectile->GetTransform().angle = m_transform.angle;

		m_scene->AddActor(projectile);
	}

	//position
	nc::Vector2 force;
	if (Core::Input::IsPressed('W')) { force = nc::Vector2::forward * m_thrust; }
	force = nc::Vector2::Rotate(force, m_transform.angle);

	m_velocity = m_velocity + (force * dt);
	m_velocity = m_velocity * 0.98f;

	m_transform.position += m_velocity * dt;

	//rotate
	if (Core::Input::IsPressed('A')) m_transform.angle -= nc::DegreesToRadians(m_rotation) * dt;
	if (Core::Input::IsPressed('D')) m_transform.angle += nc::DegreesToRadians(m_rotation) * dt;

	if (m_transform.position.x > 800) m_transform.position.x = 0;
	if (m_transform.position.x < 0) m_transform.position.x = 800;
	if (m_transform.position.y > 600) m_transform.position.y = 0;
	if (m_transform.position.y < 0) m_transform.position.y = 600;

	m_transform.Update();

	
}

void Player::Draw(Core::Graphics& graphics)
{
	Actor::Draw(graphics);
}
