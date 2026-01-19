#include "../Game/Engine/ECS/Entity/EntityComponentSystem.h"
#include "../Game/Engine/ECS/Components/Components.h"
#include "../Game/Engine/ECS/Systems/TextRenderer.h"
#include "../ContestAPI/app.h"

using namespace ECS;

void TextRenderer::Render() {
	for (EntityID e : textEntities.entities) {
		Text t = *s->getComponent<Text>(e);
		Material m = *s->getComponent<Material>(e);
		App::Print(t.x, t.y, t.text, m.x, m.y, m.z, t.font);
	}
}