#include "CheckWin.h"
#include "../Game/Engine/ECS/Entity/EntityComponentSystem.h"
#include "../Game/Scenes/SceneManager.h"
#include "cmath"

using namespace ECS;

void CheckWin::Update(float deltaTime) {
	// Check how closely the current views align
	EntityID player = playerView.entities[0];
	Rotation &playerRot = *s->getComponent<Rotation>(player);
	Position &playerPos = *s->getComponent<Position>(player);

	EntityID goal = goalView.entities[0];
	Rotation &goalRot = *s->getComponent<Rotation>(goal);
	Position &goalPos = *s->getComponent<Position>(goal);

	Vec3<float> playerViewAngle = getRotationMatrix(playerRot).mul(Vec3<float>{0, 0, 1});
	Vec3<float> goalViewAngle = getRotationMatrix(goalRot).mul(Vec3<float>{0, 0, 1});

	float viewDiff = dot(playerViewAngle, goalViewAngle);
	viewDiff = fmin(viewDiff, 1);
	viewDiff = fmax(viewDiff, -1);
	float angleDiff = acos(viewDiff);

	float posDiff = norm(playerPos - goalPos);

	if (posDiff < 1 && abs(angleDiff) < 1) {
		playerRot = goalRot;
		playerPos = goalPos;
	}
}