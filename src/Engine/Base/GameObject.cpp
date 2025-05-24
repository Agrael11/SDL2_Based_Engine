#include "GameObject.h"

#include "IComponent.h"
#include "../Helper/Logger.h"
#include "../Managers/GameObjectManager.h"

using namespace Engine::Managers;
using namespace Engine::Base;
using namespace Engine::Helper;

GameObject::GameObject(std::string name)
{
	m_name = name;
	Logger::log(Logger::Level::Info, "Initializing GameObject '{}'", m_name);
}

void GameObject::Update(float deltaTime)
{
	Logger::log(Logger::Level::Debug, "Updating GameObject '{}' with deltaTime: {}", m_name, deltaTime);
	for (const auto& component : m_components)
	{
		component->Update(*this, deltaTime);
	}
}

void GameObject::Destroy()
{
	Logger::log(Logger::Level::Info, "Destroying GameObject '{}'", m_name);
	for (const auto& component : m_components)
	{
		component->Destroy(*this);
	}
	m_components.clear();
	for (auto& child : m_children)
	{
		Engine::Managers::GameObjectManager::RemoveGameObject(child); 
	}
	m_children.clear();
	Logger::log(Logger::Level::Info, "GameObject '{}' destroyed", m_name);
}

std::string GameObject::GetName()
{
	return m_name;
}

std::vector<std::shared_ptr<IComponent>>& GameObject::GetComponents()
{
	return m_components;
}

std::vector<std::string>& GameObject::GetChildren()
{
	return m_children;
}

void GameObject::AddComponent(std::shared_ptr<IComponent> component)
{
	component->Init(*this);
	m_components.emplace_back(component);
	Logger::log(Logger::Level::Info, "Component added to GameObject '{}'", m_name);
}

void GameObject::AddChild(std::string& child)
{
	if (!GameObjectManager::GameObjectExists(child))
	{
		Logger::log(Logger::Level::Warning, "Child GameObject '{}' doesn't exists, cannot add to parent '{}'", child, m_name);
		return;
	}

	GameObject& other = GameObjectManager::GetGameObject(child);
	if (other.GetParent() != ROOT_NAME && other.GetParent() != m_name)
	{
		Logger::log(Logger::Level::Warning, "Child GameObject '{}' already has a parent '{}', cannot add to parent '{}'", child, other.GetParent(), m_name);
		return;
	}

	other.SetParent(m_name);

	if (this->ChildExists(child))
	{
		Logger::log(Logger::Level::Warning, "Child GameObject '{}' already exists in parent '{}'", child, m_name);
		return;
	}

	m_children.emplace_back(child);
	Logger::log(Logger::Level::Info, "Child GameObject '{}' added to parent '{}'", child, m_name);
}

bool GameObject::ChildExists(std::string name)
{
	for (const auto& child : m_children)
	{
		return true;
	}
	return false;
}

std::string GameObject::GetParent()
{
	return m_parent;
}

void GameObject::SetParent(std::string name)
{	
	m_parent = name;
	Logger::log(Logger::Level::Info, "Parent of GameObject '{}' set to '{}'", m_name, m_parent);
}

bool GameObject::IsTopLevel() const
{
	return m_parent == ROOT_NAME;
}