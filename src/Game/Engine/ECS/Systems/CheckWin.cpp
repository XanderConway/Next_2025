#include "CheckWin.h"
#include "../Game/Engine/ECS/Entity/EntityComponentSystem.h"
#include "../Game/Scenes/SceneManager.h"
#include "cmath"

using namespace ECS;

const float WIN_TRANSITION_TIME = 4000;

void CheckWin::Update(float deltaTime) {
	// Check how closely the current views align
	EntityID player = playerView.entities[0];
	Rotation &playerRot = *world->getComponent<Rotation>(player);
	Position &playerPos = *world->getComponent<Position>(player);

	EntityID goal = goalView.entities[0];
	Rotation &goalRot = *world->getComponent<Rotation>(goal);
	Position &goalPos = *world->getComponent<Position>(goal);

	Vec3<float> playerViewAngle = getRotationMatrix(playerRot.rot).mul(Vec3<float>{0, 0, 1});
	Vec3<float> goalViewAngle = getRotationMatrix(goalRot.rot).mul(Vec3<float>{0, 0, 1});

	float viewDiff = dot(playerViewAngle, goalViewAngle);
	viewDiff = fmin(viewDiff, 1);
	viewDiff = fmax(viewDiff, -1);
	float angleDiff = acos(viewDiff);

	float posDiff = norm(playerPos.pos - goalPos.pos);

	if (posDiff < 1.5 && abs(angleDiff) < 0.2) {
		playerRot = goalRot;
		playerPos = goalPos;
		hasWon = true;
	}

	if (hasWon) {
		timer += deltaTime;

		if (world->hasComponent<Material>(goal)) {
			Material& mat = *world->getComponent<Material>(goal);
			mat.rgb = { 0, (timer / WIN_TRANSITION_TIME) + 0.2f, 0 };
		}

		if (timer > WIN_TRANSITION_TIME) {
			SceneManager::getInstance().requestNextScene();
		}
	}
}