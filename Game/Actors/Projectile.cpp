#include "Projectile.h"
#include "Graphics/ParticleSystem.h"

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
    m_lifetime -= dt;
    m_destroy = (m_lifetime <= 0);

	nc::Vector2 direction = nc::Vector2::Rotate( nc::Vector2::forward, m_transform.angle );
	m_velocity = direction * m_thrust;
	m_transform.position += m_velocity * dt;

    g_particleSystem.Create(m_transform.position, m_transform.angle + nc::PI, 20, 1, nc::Color::white, 1, 50, 100);

    

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
