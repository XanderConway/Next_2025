#include "../Game/Engine/ECS/Entity/EntityComponentSystem.h"
#include "../Game/Engine/ECS/Components/Components.h"
#include "../Game/Engine/ECS/Systems/MoveParticles.h"
#include "../ContestAPI/app.h"

using namespace ECS;

void MoveParticles::Update(float deltaTime) {

	for (EntityID e : particles.entities) {
		Vec3<float>& pos = world->getComponent<Position>(e)->pos;
		Vec3<float>& rot = world->getComponent<Rotation>(e)->rot;
		Vec3<float>& vel = world->getComponent<Velocity>(e)->vel;
		Vec3<float>& angularVel = world->getComponent<AngularVel>(e)->vel;

		pos = pos + (globalVel + vel) * deltaTime;
		rot = rot + angularVel * deltaTime;

		for (int i = 0; i < 3; i++) {
			if (pos[i] < minCorner[i]) {
				pos[i] = maxCorner[i];
			}

			if (pos[i] > maxCorner[i]) {
				pos[i] = minCorner[i];
			}
		}
	}
}
