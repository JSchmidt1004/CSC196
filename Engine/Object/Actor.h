#pragma once
#include "../Math/Transform.h"
#include "../Graphics/Shape.h"
#include "../Math/Math.h"

namespace nc
{
	class Scene;

	class Actor
	{
	public:
		enum class eType
		{
			PLAYER,
			ENEMY,
			PROJECTILE
		};

	public:
		Actor() {}
		Actor(const Transform& transform, const Shape& shape) : m_transform{ transform }, m_shape{ shape } {}  
		virtual ~Actor() {}

		virtual bool Load(const std::string& filename);
		virtual void Load(std::istream& stream);

		virtual void Update(float dt);
		virtual void Draw(Core::Graphics& graphics);

		virtual void OnCollision(Actor* actor) {}

		virtual eType GetType() = 0;

		Transform& GetTransform() { return m_transform; } 
		Shape& GetShape() { return m_shape; }
		void SetScene(Scene* scene) { m_scene = scene; }
		void SetDestroy(bool destroy) { m_destroy = destroy; }
		bool IsDestroy() { return m_destroy; }


	protected:
		bool m_destroy = false;
		Scene* m_scene = nullptr;
		Transform m_transform;
		Shape m_shape;
	};
}
