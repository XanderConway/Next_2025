#include "../Game/Engine/ECS/Entity/EntityComponentSystem.h"
#include "../Game/Engine/ECS/Components/Components.h"

struct MenuController : public ECS::System {
	using System::System;
	void Update(float deltaTime) override;
};