#pragma once
#include <vector>
#include <memory>
#include "Archetype.hpp"
#include "System.hpp"
#include "Entity.hpp"

class ECS
{
	std::vector<Archetype> _archetypes;
	std::vector<std::unique_ptr<ISystem>> _systems;
	
	// ids
	std::uint32_t _nextEntityId = 0;

public:
	// Constructors
	ECS() {};
	~ECS() {};

	// Core Loops
	// Add loops here

	// Entity Management
	Entity GetNextEntityId() const;

	Entity CreateEntity();
	void DestroyEntity(Entity entity);

	// Component Management
	template<typename TComponent>
	void AddComponent(Entity entity, const TComponent& component) const
	{
		std::cout << "added in addedinecs" << std::endl;
		//auto typeId = GetComponentTypeId<TComponent>();
		//if()
		// find existing? if no then create new
		// move entity to the archetype container
		// add component to the entity in that archetype
	}

	template<typename TComponent>
	void RemoveComponent(Entity entity) const
	{

	}

	// Systems

	template<typename TSystem, typename... Args>
	TSystem& AddSystem(Args&&... args)
	{
		TSystem* system = new TSystem(std::forward<Args>(args)...);
		_systems.emplace_back(system);
		return *system;
	}
	
	// Loops
	void Render();
	void Update(float deltaTime);
	void PeriodicUpdate(float deltaTime);
};