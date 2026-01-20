#include "../Game/Engine/ECS/Entity/EntityComponentSystem.h"
#include "../Game/Engine/ECS/Components/Components.h"
#include "../Game/Engine/ECS/Systems/TextRenderer.h"
#include "../ContestAPI/app.h"

using namespace ECS;

void TextRenderer::Render() {
	for (EntityID e : textEntities.entities) {
		Text t = *world->getComponent<Text>(e);
		Material m = *world->getComponent<Material>(e);
		App::Print(t.x, t.y, t.text, m.rgb.x, m.rgb.y, m.rgb.z, t.font);
	}
}