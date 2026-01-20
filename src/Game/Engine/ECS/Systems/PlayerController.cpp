#include "../Game/Engine/ECS/Entity/EntityComponentSystem.h"
#include "../Game/Engine/ECS/Components/Components.h"
#include "../Game/Engine/ECS/Systems/PlayerController.h"
#include "../ContestAPI/app.h"

using namespace ECS;

void PlayerController::Update(float deltaTime) {
	float newMouseX, newMouseY;
	App::GetMousePos(newMouseX, newMouseY);

	for (EntityID e : player.entities) {
		// Rotate the player Based on WASD movement
		Vec3<float>& rot = world->getComponent<Rotation>(e)->rot;
		float lookX = App::GetController().GetRightThumbStickX();
		float lookY = App::GetController().GetRightThumbStickY();

		rot.y += -lookX * sensitivity * deltaTime;
		rot.x += lookY * sensitivity * deltaTime;

		rot.x = max(rot.x, -3.14 / 8);
		rot.x = min(rot.x, 3.14 / 8);

		Vec3<float>& pos = world->getComponent<Position>(e)->pos;
		float moveX = App::GetController().GetLeftThumbStickX();
		float moveY = App::GetController().GetLeftThumbStickY();
		
		// Orient movement vector based on where we are facing
		Vec3<float> moveVec(moveX, 0, moveY);
		Matrix4x4 rotMat = getRotationMatrix(-rot.y, 0, 0);
		moveVec = rotMat.mul(moveVec) * speed * deltaTime;
		pos.x += moveVec.x;
		pos.z += moveVec.z;

		if (bounded) {
			for (int i = 0; i < 3; i++) {
				if (pos[i] < minBound[i]) {
					pos[i] = minBound[i];
				}

				if (pos[i] > maxBound[i]) {
					pos[i] = maxBound[i];
				}
			}
		}
	}
}
