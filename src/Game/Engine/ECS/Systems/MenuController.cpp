#include "MenuController.h"
#include "../Game/Scenes/SceneManager.h"
#include "app.h"

void MenuController::Update(float deltaTime) {
	if (App::IsKeyPressed(App::KEY_SPACE))
	{
		SceneManager &manager = SceneManager::getInstance();
		manager.requestSceneLoad(manager.currScene + 1);
	}
}