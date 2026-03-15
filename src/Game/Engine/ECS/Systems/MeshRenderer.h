#include "../Game/Engine/ECS/Entity/EntityComponentSystem.h"
#include "../Game/Engine/ECS/Components/Components.h"

struct MeshRenderer : public ECS::System {

	ECS::SceneView<Position, Rotation, Scale, Mesh> view;
	ECS::SceneView<Camera, Position, Rotation> camView;

	MeshRenderer(ECS::World* s) : ECS::System(s), view(s), camView(s) {}

	Matrix4x4 computeCamRotMat(ECS::EntityID camId);

	Matrix4x4 computeCamTranslationMat(ECS::EntityID camId);

	void Render() override;
};