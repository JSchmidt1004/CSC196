// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.


#include <iostream>
#include <string>
#include <vector>
#include <list>

#include "core.h"
#include "Math/Math.h"
#include "Math/Random.h"
#include "Math/Color.h"
#include "Math/Transform.h"
#include "Graphics/Shape.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"


//Player player;
//Enemy enemy;

std::list<nc::Actor*> actors;

nc::Vector2 velocity;
float thrust = 200.0;


float frametime;
float spawntimer = 0.0f;


/*
void exampleCode() {
	nc::Vector2 point;
	point.x = 3;
	point.y = 5;

	{{-3, -7}, {-1.5f, 5}, { 0, -7 }, { 7, 7 }, { -7, 7 }, { 0, -7 }}, nc::Color(52, 201, 235)


	graphics.SetColor(RGB(rand() % 256, rand() % 256, rand() % 256));
	graphics.DrawLine(static_cast<float>(rand() % 800), static_cast<float>(rand() % 600), static_cast<float>(rand() % 800), static_cast<float>(rand() % 600));

	
	for (size_t i = 0; i < NUM_POINTS - 1; i++)
	{
		nc::Vector2 p1 = position + points[i];
		nc::Vector2 p2 = position + points[i + 1];

		graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
	}

	Core::Input::GetMousePos(x, y);

	nc::Vector2 target = nc::Vector2{ x, y };
	nc::Vector2 direction = target - position;
	direction.Normalize();

	position += direction * 5.0f;
	
	if (Core::Input::IsPressed('A')) { position += nc::Vector2::left * speed * dt; }
	if (Core::Input::IsPressed('D')) { position += nc::Vector2::right * speed * dt; }
	if (Core::Input::IsPressed('W')) { position += nc::Vector2::up * speed * dt; }
	if (Core::Input::IsPressed('S')) { position += nc::Vector2::down * speed * dt; }

	for (size_t i = 0; i < NUM_POINTS; i++)
	{
		points.push_back({ nc::random(0.0f, 800.0f), nc::random(0.0f, 600.0f) });
	}


	for (nc::Vector2& point : transform.points)
	{
		point = { nc::random(-10.0f, 10.0f), nc::random(-10.0f, 10.0f) };
	}

	const size_t NUM_POINTS = 40;
	std::vector<nc::Vector2> points;
	nc::Color color;
	nc::Vector2 position{ 400, 300 };
	float angle = 0.0f;
	float scale = 2.0f;

	nc::Shape ship{ points, color };

	nc::Shape ship;
	nc::Transform transform{ {400, 300}, 2, 0 };

	Gravity
	force = force + nc::Vector2{ 0, 200 };

	if (roundTime >= 5) gameOver = true;
	if (gameOver) dt = 0;

	player.GetTransform().position = nc::Clamp(player.GetTransform().position, { 0, 0 }, { 800, 600 });

	DWORD time = GetTickCount();
	deltaTime = time - prevTime;
	prevTime = time;

	frametime = dt;
	roundTime += dt;

	DWORD ticks = GetTickCount();
	std::cout << ticks / 1000 / 60 / 60 << std::endl;
	prevTime = GetTickCount();

	float roundTime = 0;
bool gameOver = false;

DWORD prevTime;
DWORD deltaTime;

	graphics.DrawString(10, 30, std::to_string(deltaTime / 1000.0f).c_str());

	if (gameOver) graphics.DrawString(400, 300, "Game Over");

	player.Update(dt);
	enemy.Update(dt);

	player.Draw(graphics);
	enemy.Draw(graphics);

	player.Load("Player.txt");
	enemy.Load("Enemy.txt");
	enemy.SetTarget(&player);

	in Shape.cpp
	while (!stream.eof())
		{
			Vector2 point;
			stream >> point;

			if (!stream.eof())
			{
				m_points.push_back(point);
			}
		}
}
*/

template <typename T>
nc::Actor* GetActor()
{
	nc::Actor* result = nullptr;

	for (nc::Actor* actor : actors)
	{
		result = dynamic_cast<T*>(actor);
		if (result) break;
	}

	return result;
}

template <typename T>
std::vector<nc::Actor*> GetActors()
{
	std::vector<nc::Actor*> results;

	for (nc::Actor* actor : actors)
	{
		T*result = dynamic_cast<T*>(actor);
		if (result)
		{
			results.push_back(result);
		}
	}

	return results;
}

bool Update(float dt)
{
	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);
	frametime = dt;

	if (Core::Input::IsPressed(VK_SPACE))
	{
		auto removeActors = GetActors<Enemy>();
		for (auto actor : removeActors)
		{
			auto iter = std::find(actors.begin(), actors.end(), actor);
			delete* iter;
			actors.erase(iter);
		}
	}

	spawntimer += dt;
	if (spawntimer >= 3.0f)
	{
		spawntimer = 0.0f;

		//Add enemy to scene
		nc::Actor* enemy = new Enemy;
		enemy->Load("Enemy.txt");
		dynamic_cast<Enemy*>(enemy)->SetTarget(GetActor<Player>());
		enemy->GetTransform().position = nc::Vector2{ nc::random(0, 800), nc::random(0, 600) };
		dynamic_cast<Enemy*>(enemy)->SetThrust(nc::random(50, 100));

		actors.push_back(enemy);
	}

	for (nc::Actor* actor : actors)
	{
		actor->Update(dt);
	}

	return quit;
}

void Draw(Core::Graphics& graphics)
{
	graphics.DrawString(10, 10, std::to_string(frametime).c_str());
	graphics.DrawString(10, 20, std::to_string(1.0f / frametime).c_str());


	for (nc::Actor* actor : actors)
	{
		actor->Draw(graphics);
	}

}

int main()
{
	nc::Actor* player = new Player;
	player->Load("Player.txt");
	actors.push_back(player);

	for (int i = 0; i < 3; i++)
	{
		nc::Actor* enemy = new Enemy;
		enemy->Load("Enemy.txt");
		dynamic_cast<Enemy*>(enemy)->SetTarget(player);
		enemy->GetTransform().position = nc::Vector2{ nc::random(0, 800), nc::random(0, 600) };
		dynamic_cast<Enemy*>(enemy)->SetThrust(nc::random(50, 100));

		actors.push_back(enemy);
	}

	char name[] = "CSC196";
	Core::Init(name, 800, 600, 90);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();
}
