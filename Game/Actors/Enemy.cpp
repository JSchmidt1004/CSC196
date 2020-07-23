#include "Enemy.h"
#include "Graphics/ParticleSystem.h"
#include "Object/Scene.h"
#include "../Game.h"

bool Enemy::Load(const std::string& filename)
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


void Enemy::Update(float dt)
{
	nc::Vector2 direction = m_target->GetTransform().position - m_transform.position;
	m_velocity = direction.Normalized() * m_thrust;
	m_transform.position += m_velocity * dt;
	m_transform.angle = std::atan2(direction.y, direction.x)+ nc::DegreesToRadians(90.0f);

    m_transform.Update();
}

void Enemy::Draw(Core::Graphics& graphics)
{
	Actor::Draw(graphics);
}

void Enemy::OnCollision(Actor* actor)
{
    if (actor->GetType() == eType::PROJECTILE) 
    {
        m_destroy = true;

        //Set game score
        m_scene->GetGame()->AddPoints(100);


        nc::Color colors[] = { nc::Color::white, nc::Color::red, nc::Color::yellow };
        nc::Color color = colors[rand() % 3];

        g_particleSystem.Create(m_transform.position, 0, 180, 30, color, 1, 50, 100);
    }
}
