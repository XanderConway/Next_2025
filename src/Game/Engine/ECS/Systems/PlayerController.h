#include "../Game/Engine/ECS/Entity/EntityComponentSystem.h"
#include "../Game/Engine/ECS/Components/Components.h"

struct PlayerController : public ECS::System {
	ECS::SceneView<Player, Camera, Position, Rotation> player;
	float sensitivity = 0.001;
	float speed = 0.03;
	const bool bounded;
	const Vec3<float> minBound;
	const Vec3<float> maxBound;
	//float prevMouseX, prevMouseY;

	PlayerController(ECS::World* s) : ECS::System(s), player(s), bounded(false), minBound{ 0, 0, 0 }, maxBound{ 0, 0, 0 } {}

	PlayerController(ECS::World* s, Vec3<float> minBound, Vec3<float> maxBound) : ECS::System(s), player(s), bounded(true), minBound(minBound), maxBound(maxBound) {}

	void Update(float deltaTime) override;
};