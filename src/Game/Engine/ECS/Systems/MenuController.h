# pragma once
#include "../Game/Engine/ECS/Entity/EntityComponentSystem.h"
#include "../Game/Engine/ECS/Components/Components.h"

struct MenuController : public ECS::System {
	int nextScene;
	MenuController(ECS::World* world, int nextScene) : ECS::System(world), nextScene(nextScene){}
	void Update(float deltaTime) override;
};