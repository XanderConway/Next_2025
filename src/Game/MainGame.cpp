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
	MainMenu* menuLevel = new MainMenu;
	Tutorial* tutorialLevel = new Tutorial;
	Station* stationLevel = new Station;
	Observatory* obervatoryLevel = new Observatory;
	EndScreen* endScreen = new EndScreen;

	manager.scenes.push_back(menuLevel);
	manager.scenes.push_back(tutorialLevel);
	manager.scenes.push_back(stationLevel);
	manager.scenes.push_back(obervatoryLevel);
	manager.scenes.push_back(endScreen);
	manager.requestSceneLoad(0);
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(const float deltaTime)
{
	manager.Update(deltaTime);

}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{	//------------------------------------------------------------------------
	manager.Render();
}
//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{

	manager.Shutdown();
}