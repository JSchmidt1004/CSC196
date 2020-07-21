#include "Projectile.h"

bool Projectile::Load(const std::string& filename)
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

        stream.close();
    }

    return success;
}


void Projectile::Update(float dt)
{
	nc::Vector2 direction = nc::Vector2::Rotate( nc::Vector2::forward, m_transform.angle );
	m_velocity = direction * m_thrust;
	m_transform.position += m_velocity * dt;

    m_transform.Update();
}

void Projectile::Draw(Core::Graphics& graphics)
{
	Actor::Draw(graphics);
}

void Projectile::OnCollision(Actor* actor)
{
    if (actor->GetType() == eType::ENEMY)
    {
        m_destroy = true;
    }
}
