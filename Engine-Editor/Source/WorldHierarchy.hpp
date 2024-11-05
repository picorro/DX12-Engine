#pragma once
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx11.h>

#include <unordered_map>
#include <memory>
#include <string>
#include <iostream>

#include <cereal/cereal.hpp>
#include <cereal/types/unordered_map.hpp>
#include <cereal/types/string.hpp>

#include "TransformComponent.hpp"
#include "TerrainComponent.hpp"
#include "WorldHierarchyComponent.hpp"

#include "ECS.hpp"
//#include "World.hpp"

class World; // forward declaration

class WorldHierarchy : public ISystem
{
	ECS* _ecs;
	World* _world = nullptr; // non owning

	bool _enabled = false;

public:
	WorldHierarchy();
	WorldHierarchy(ECS* ecs, World* world);

	void Render() override;
	void Update(float deltaTime) override;
	void PeriodicUpdate(float deltaTime) override;

	int CreatePrimitiveGeometry3D(PrimitiveGeometryType3D type, std::string name, std::unordered_map<Entity, std::string>& entityToName);

	void SetWorld(World* world);

	void Toggle();
};

