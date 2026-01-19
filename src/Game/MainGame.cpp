///////////////////////////////////////////////////////////////////////////////
// Filename: GameTest.cpp
// Provides a demo of how to use the API
///////////////////////////////////////////////////////////////////////////////

#if BUILD_PLATFORM_WINDOWS
//------------------------------------------------------------------------
#include <windows.h> 
#endif

#include <iostream>
//------------------------------------------------------------------------
#include <math.h>  
//------------------------------------------------------------------------
#include "../ContestAPI/app.h"
//------------------------------------------------------------------------

#include "../Game/Utils/ReadObj.h"

#include <vector>

#include "../Game/Engine/ECS/Entity/EntityComponentSystem.h"
#include "../Game/Engine/ECS/Components/Components.h"
#include "../Game/Engine/ECS/Systems/MeshRenderer.h"
#include "../Game/Engine/ECS/Systems/Spin.h"

#include "../Game/Scenes/SceneManager.h"

#include "../Game/Scenes/Levels.h"


using namespace ECS;

SceneManager& manager = SceneManager::getInstance();

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	MainMenu *m = new MainMenu;
	Level1 *l1 = new Level1;

	manager.scenes.push_back(m);
	manager.scenes.push_back(l1);
	manager.requestSceneLoad(0);


	//------------------------------------------------------------------------
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(const float deltaTime)
{
	//------------------------------------------------------------------------
	// Example Sprite Code....
	manager.Update(deltaTime);
	//s.Update(deltaTime);

}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{	//------------------------------------------------------------------------

	// Render Suzanne
	//cam.Render(suzanne);
	manager.Render();

	//s.Render();
}
//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{
	//------------------------------------------------------------------------
	// Example Sprite Code....
	//------------------------------------------------------------------------
	manager.Shutdown();
}