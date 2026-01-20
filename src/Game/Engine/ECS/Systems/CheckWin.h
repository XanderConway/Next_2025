#include "../Game/Engine/ECS/Entity/EntityComponentSystem.h"
#include "../Game/Engine/ECS/Components/Components.h"

struct CheckWin : public ECS::System {
	ECS::SceneView<Player> playerView;
	ECS::SceneView<GoalPerspective> goalView;
	float timer;
	bool hasWon;

	CheckWin(ECS::World* s) : ECS::System(s), playerView(s), goalView(s), timer(0), hasWon(false){}

	void Update(float deltaTime) override;
};