#include "GameObjectManager.h"

#include <unordered_map>
#include <memory>
#include "../Helper/Logger.h"

#include "../Base/GameObject.h"


using namespace Engine::Helper;
using namespace Engine::Managers;
using namespace Engine::Base;


std::unordered_map<std::string, std::unique_ptr<GameObject>> m_gameobjects;

GameObjectManager::GameObjectManager()
{
}

bool GameObjectManager::AddGameObject(std::string id, GameObject& gameobject)
{
	if (GameObjectExists(id))
	{
		Logger::log(Logger::Level::Error, "Game Object {} already loaded", id);
		return false;
	}

	m_gameobjects[id] = std::make_unique<GameObject>(std::move(gameobject));
	return true;
}

GameObject& GameObjectManager::AddNewGameObject(std::string name)
{
	if (GameObjectExists(name))
	{
		throw std::runtime_error("Game Object " + name + "already loaded");
	}

	m_gameobjects[name] = std::make_unique<GameObject>(name);
	Logger::log(Logger::Level::Info, "Added {} to Game Object Manager", name);
	return *m_gameobjects[name];
}

bool GameObjectManager::GameObjectExists(std::string id)
{
	return (m_gameobjects.count(id) > 0);
}

GameObject& GameObjectManager::GetGameObject(std::string id)
{
	if (!GameObjectExists(id))
	{
		throw std::runtime_error("Game Object " + id + " does not exist");
	}
	return *m_gameobjects[id];
}

void GameObjectManager::Update(float deltaTime)
{
	for (auto& gameobject : m_gameobjects)
	{
		gameobject.second->Update(deltaTime); // Assuming a fixed delta time for simplicity
	}
}

bool GameObjectManager::RemoveGameObject(std::string id)
{
	if (!GameObjectExists(id))
	{
		Logger::log(Logger::Level::Error, "Game Object {} does not exist", id);
		return false;
	}

	m_gameobjects[id]->Destroy();
	m_gameobjects[id].reset();
	m_gameobjects.erase(id);
	Logger::log(Logger::Level::Info, "Removed {} from Game Object Manager", id);
	return true;
}

bool GameObjectManager::RemoveAll()
{
	for (auto& shader : m_gameobjects)
	{
		shader.second.reset();
	}
	m_gameobjects.clear();
	Logger::log(Logger::Level::Info, "Removed all Game Objects from Game Object Manager");
	return true;
}