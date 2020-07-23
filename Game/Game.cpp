#include "Game.h"
#include <string>
#include <vector>
#include <list>

#include "Math/Math.h"
#include "Math/Random.h"
#include "Math/Color.h"
#include "Math/Transform.h"
#include "Graphics/Shape.h"
#include "Graphics/ParticleSystem.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"

void Game::Startup()
{
	m_scene.Startup();
	g_particleSystem.Startup();
	m_scene.SetGame(this);
}

void Game::Shutdown()
{
	m_scene.Shutdown();
	g_particleSystem.Shutdown();
}

bool Game::Update(float dt)
{
	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);
	m_frametime = dt;

	switch (m_state)
	{
	case Game::eState::INIT:
		break;
	case Game::eState::TITLE:
		if (Core::Input::IsPressed(VK_SPACE))
		{
			m_state = Game::eState::START_GAME;
		}
		break;
	case Game::eState::START_GAME:
	{
		nc::Actor* player = new Player;
		player->Load("Player.txt");
		m_scene.AddActor(player);

		for (int i = 0; i < 3; i++)
		{
			nc::Actor* enemy = new Enemy;
			enemy->Load("Enemy.txt");
			dynamic_cast<Enemy*>(enemy)->SetTarget(player);
			enemy->GetTransform().position = nc::Vector2{ nc::random(0, 800), nc::random(0, 600) };
			dynamic_cast<Enemy*>(enemy)->SetThrust(nc::random(50, 100));

			m_scene.AddActor(enemy);
		}
	}

		m_state = Game::eState::GAME;
		break;
	case Game::eState::GAME:
	{
		m_spawntimer += dt;
		if (m_spawntimer >= 3.0f)
		{
			m_spawntimer = 0.0f;

			//Add enemy to m_scene
			nc::Actor* enemy = new Enemy;
			enemy->Load("Enemy.txt");
			dynamic_cast<Enemy*>(enemy)->SetTarget(m_scene.GetActor<Player>());
			enemy->GetTransform().position = nc::Vector2{ nc::random(0, 800), nc::random(0, 600) };
			dynamic_cast<Enemy*>(enemy)->SetThrust(nc::random(50, 100));

			m_scene.AddActor(enemy);
		}
	}
		m_scene.Update(dt);
		break;
	case Game::eState::GAME_OVER:
		break;
	default:
		break;
	}


	if (Core::Input::IsPressed(Core::Input::BUTTON_LEFT))
	{
		int x, y;
		Core::Input::GetMousePos(x, y);

		nc::Color colors[] = { nc::Color::white, nc::Color::red, nc::Color::yellow };
		nc::Color color = colors[rand() % 3];

		g_particleSystem.Create({ x, y }, 0, 180, 30, color, 1, 50, 100);
	}

	g_particleSystem.Update(dt);

	return quit;
}

void Game::Draw(Core::Graphics& graphics)
{
	graphics.SetColor(nc::Color{ 1, 1, 1 });
	graphics.DrawString(10, 10, std::to_string(m_frametime).c_str());
	graphics.DrawString(10, 20, std::to_string(1.0f / m_frametime).c_str());

	g_particleSystem.Draw(graphics);

	switch (m_state)
	{
	case Game::eState::INIT:
		break;
	case Game::eState::TITLE:
		graphics.SetColor(nc::Color::green);
		graphics.DrawString(400, 300, "VECTOROIDS");
	case Game::eState::START_GAME:
		break;
	case Game::eState::GAME:
		graphics.SetColor(nc::Color::white);
		graphics.DrawString(700, 40, std::to_string(m_score).c_str());
		m_scene.Draw(graphics);
		break;
	case Game::eState::GAME_OVER:
		graphics.SetColor(nc::Color::green);
		graphics.DrawString(400, 300, "GAME OVER");
		break;
	default:
		break;
	}
}
