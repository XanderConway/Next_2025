#include "../Game/Engine/ECS/Entity/EntityComponentSystem.h"
#include "../Game/Engine/ECS/Components/Components.h"

struct MoveParticles : public ECS::System {
	ECS::SceneView<Particle, Velocity> particles;
	float sensitivity = 0.001;
	float speed = 0.03;
	const Vec3<float> minCorner;
	const Vec3<float> maxCorner;
	const Vec3<float> globalVel;
	//float prevMouseX, prevMouseY;

	MoveParticles(ECS::World* s, Vec3<float> minCorner, Vec3<float> maxCorner, Vec3<float> vel) : ECS::System(s), particles(s), minCorner(minCorner), maxCorner(maxCorner), globalVel(vel) {}

	void Update(float deltaTime) override;
};