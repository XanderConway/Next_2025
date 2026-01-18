#include "../Game/Engine/ECS/Entity/EntityComponentSystem.h"
#include "../Game/Engine/ECS/Components/Components.h"

struct MeshRenderer : public ECS::System {

	ECS::SceneView<Position, Rotation, Scale, Mesh> view;
	ECS::SceneView<Camera, Position, Rotation> cam;

	MeshRenderer(ECS::Scene* s) : ECS::System(s), view(s), cam(s) {}

	Matrix4x4 computeCamRotMat(ECS::EntityID camId);

	Matrix4x4 computeCamTranslationMat(ECS::EntityID camId);

	void Render() override;
};