#pragma once

#include "../Game/Engine/ECS/Entity/Entity.h"
#include "../Game/Engine/ECS/Components/Transform.h"

struct Spin : public System {

	SceneView<Position, Rotation, Scale> view;

	Spin(Scene* s) : System(s), view(s) {}

	float currTime = 0;

	void Update(float deltaTime) override {
		for (EntityID e : view.entities) {
			Position &pos = *s->getComponent<Position>(e);
			Rotation& rot = *s->getComponent<Rotation>(e);
			//rot.y += deltaTime * 0.001;
			rot.x += deltaTime * 0.0007;
			//rot.z += deltaTime * 0.0005;


			currTime += deltaTime;
			//pos.y += sin(currTime);
		}
	}
};
