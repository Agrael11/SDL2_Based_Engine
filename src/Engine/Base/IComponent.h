#pragma once

namespace Engine::Base
{
	class IComponent
	{
	public:
		virtual ~IComponent() = default;
		virtual void Update(float deltaTime) = 0;
		virtual void Init() = 0;
		virtual void Destroy() = 0;
	};
}