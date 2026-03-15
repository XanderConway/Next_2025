#include "../Game/Engine/ECS/Entity/EntityComponentSystem.h"
#include "../Game/Engine/ECS/Components/Components.h"

struct TextRenderer : public ECS::System {

	ECS::SceneView<Text, Material> textEntities;

	TextRenderer(ECS::World* s) : ECS::System(s), textEntities(s) {}

	void Render() override;
};