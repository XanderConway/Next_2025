#pragma once

#include "../Game/Engine/ECS/Entity/EntityComponentSystem.h"
#include "../Game/Engine/ECS/Components/Components.h"

struct Spin : public ECS::System {

	ECS::SceneView<Position, Rotation, Scale> view;

	Spin(ECS::World* s) : ECS::System(s), view(s) {}

	float currTime = 0;

	void Update(float deltaTime) override {
		for (ECS::EntityID e : view.entities) {
			Vec3<float> &pos = world->getComponent<Position>(e)->pos;
			Vec3<float> &rot = world->getComponent<Rotation>(e)->rot;
			rot.y += deltaTime * 0.001;
			rot.x += deltaTime * 0.0007;
			rot.z += deltaTime * 0.0005;
			currTime += deltaTime;
		}
	}
};
