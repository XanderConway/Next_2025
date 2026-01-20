#include "MenuController.h"
#include "../Game/Scenes/SceneManager.h"
#include "app.h"

void MenuController::Update(float deltaTime) {
	if (App::IsKeyPressed(App::KEY_SPACE) || App::GetController().CheckButton(App::BTN_A))
	{
		SceneManager &manager = SceneManager::getInstance();
		manager.requestSceneLoad(nextScene);
	}
}