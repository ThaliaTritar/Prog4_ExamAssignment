#pragma once
#include <memory>
#include <vector>

#include "Transform.h"
#include "BaseComponent.h"



namespace dae
{
	class Texture2D;

	// todo: this should become final.
	class GameObject final
	{
	public:
		GameObject() = default;
		~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;


		// Datamember functions
		//------------------
		void Update(float deltaTime);
		void LateUpdate(float deltaTime);
		void FixedUpdate(float fixedStep);
		void Render() const;
		Transform GetTransform()const;

		// MOVE
		void SetSpeed(const float speed);
		void Move(float dx, float dy);

		// COMPONENTS
		void AddComponent(std::shared_ptr<BaseComponent> component)
		{
			m_components.push_back(component);
		}
		template <typename T>	void RemoveComponent()
		{

			if (m_components.size() == 0)
				return;

			for (auto& component : m_components)
			{
				if (auto* castedComponent = dynamic_cast<T*>(component.get()))
				{
					castedComponent->pendingRemove = true;
				}
			}
		}
		template <typename T>	void RemoveAllComponents()
		{
			if (m_components.size() == 0)
				return;

			for (const auto& component : m_components)
			{
				if (auto* castedComponent = dynamic_cast<T*>(component.get()))
				{
					castedComponent->pendingRemove = true;
				}
			}
		};
		template <typename T>	T* GetComponent()
		{

			if (m_components.size() == 0)
				return nullptr;

			for (const auto& component : m_components)
			{
				if (auto* castedComponent = dynamic_cast<T*>(component.get()))
				{
					return castedComponent;
				}
			}

			return nullptr;
		}
		template <typename T>	bool CheckComponentAdded()
		{
			for (const auto& component : m_components)
			{
				if (auto* castedComponent = dynamic_cast<T*>(component.get()))
				{
					return true;
				}
			}

			return false;
		}


		// PARENT-CHILD
		void SetParent(GameObject* parent, bool keepWorldPosition);
		GameObject* GetParent() const;
		size_t GetChildCount()const;
		GameObject* GetChildAt(unsigned int index)const;
		bool IsChild(GameObject* object)const;

		// TRANSFORM
		void SetPositionDirty();
		void SetLocalPosition(const glm::vec3& pos);
		const glm::vec3& GetWorldPosition();
		void UpdateWorldPosition();

		bool m_pendingRemoval = false;
	private:
		Transform m_transform{};

		std::vector<std::shared_ptr<BaseComponent>> m_components{};

		GameObject* m_parent{};
		std::vector<GameObject*> m_children{};

		bool m_positionIsDirty{};
		glm::vec3 m_localPosition{};
		glm::vec3 m_worldPosition{};

		float m_speed;

	};
}
