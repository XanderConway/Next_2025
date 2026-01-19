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
		Rotation &rot = *s->getComponent<Rotation>(e);
		float lookX = App::GetController().GetLeftThumbStickX();
		float lookY = App::GetController().GetLeftThumbStickY();

		rot.y += -lookX * sensitivity * deltaTime;
		rot.x += lookY * sensitivity * 0.7f * deltaTime;

		rot.x = max(rot.x, -3.14 / 8);
		rot.x = min(rot.x, 3.14 / 8);

		Position& pos = *s->getComponent<Position>(e);
		float moveX = App::GetController().GetRightThumbStickX();
		float moveY = App::GetController().GetRightThumbStickY();
		
		// Orient movement vector based on where we are facing
		Vec3<float> moveVec(moveX, 0, -moveY);
		Matrix4x4 rotMat = getRotationMatrix(-rot.y, 0, 0);
		moveVec = rotMat.mul(moveVec) * speed * deltaTime;
		pos.x += moveVec.x;
		pos.z += moveVec.z;


	}





	// Move the player based on keyboard input
}
