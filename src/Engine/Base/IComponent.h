#pragma once

namespace Engine::Base
{
	class IComponent
	{
	public:
		virtual ~IComponent() = default;
		virtual void Update(float deltaTime);
		virtual void Init();
		virtual void Destroy();
	};
}