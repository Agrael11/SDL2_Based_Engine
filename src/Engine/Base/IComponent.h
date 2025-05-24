#pragma once

namespace Engine::Base
{	
	class GameObject;
	class IComponent
	{
	private:
	public:
		virtual ~IComponent() = default;
		virtual void Update(GameObject& parent, float deltaTime);
		virtual void Init(GameObject& parent);
		virtual void Destroy(GameObject& parent);
	};
}