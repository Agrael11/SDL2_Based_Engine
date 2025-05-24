#pragma once

#include <string>

namespace Engine::Base
{
	class GameObject;
}

namespace Engine::Managers
{
	class GameObjectManager
	{
	private:
		GameObjectManager();

	public:
		static bool AddGameObject(std::string id, Engine::Base::GameObject& material);
		static Engine::Base::GameObject& AddNewGameObject(std::string name);

		static bool GameObjectExists(std::string id);

		static Engine::Base::GameObject& GetGameObject(std::string id);
		
		static void Update(float deltaTime);

		static bool RemoveGameObject(std::string id);
		static bool RemoveAll();
	};
};