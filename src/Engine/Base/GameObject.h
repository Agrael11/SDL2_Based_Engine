#pragma once

#include <string>
#include <vector>
#include <memory>

#include "IComponent.h"

constexpr auto ROOT_NAME = "root";

namespace Engine::Base
{
	class GameObject
	{
	private:
		std::vector<std::shared_ptr<IComponent>> m_components;
		std::vector<std::string> m_children;
		std::string m_name;
		std::string m_parent = ROOT_NAME;

	public:
		GameObject(std::string name);
		void Update(float deltaTime);
		void Destroy();
		std::string GetName();
		std::vector<std::shared_ptr<IComponent>>& GetComponents();
		std::vector<std::string>& GetChildren();
		bool ChildExists(std::string name);
		void AddComponent(std::shared_ptr<IComponent> component);
		void AddChild(std::string& child);
		std::string GetParent();
		void SetParent(std::string name);
		bool IsTopLevel() const;


		template<typename T = IComponent>
		std::vector<std::shared_ptr<T>> GetComponentsOfType()
		{
			std::vector<std::shared_ptr<T>> componentsOfType;
			for (const auto& component : m_components)
			{
				if (auto castedComponent = dynamic_cast<T*>(component.get()))
				{
					componentsOfType.push_back(std::dynamic_pointer_cast<T>(component));
				}
			}
			return componentsOfType;
		}
	};
}