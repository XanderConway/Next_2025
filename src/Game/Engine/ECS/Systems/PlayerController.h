#include "../Game/Engine/ECS/Entity/EntityComponentSystem.h"
#include "../Game/Engine/ECS/Components/Components.h"

struct PlayerController : public ECS::System {
	ECS::SceneView<Player, Camera, Position, Rotation> player;
	float sensitivity = 0.001;
	float speed = 0.03;
	//float prevMouseX, prevMouseY;

	PlayerController(ECS::World* s) : ECS::System(s), player(s) {}

	void Update(float deltaTime) override;
};