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

#include "../Game/Camera.h"

#include <vector>

#include "../Game/Engine/ECS/Entity/Entity.h"
#include "../Game/Engine/ECS/Components/Transform.h"
#include "../Game/Engine/ECS/Systems/MeshRenderer.h"
#include "../Game/Engine/ECS/Systems/Spin.h"



Scene s;

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	EntityID cam = s.addEntity();
	s.addComponent(cam, Position(0, 0, 0));
	s.addComponent(cam, Rotation(0, 0, 0));
	s.addComponent(cam, Camera(1, 100));

	Model *m = readFromFile("./data/TestData/suzanne.obj");

	EntityID monkey = s.addEntity();
	s.addComponent(monkey, Position(0, 0, 50));
	s.addComponent(monkey, Rotation(0, 0, 0));
	s.addComponent(monkey, Scale{10});
	s.addComponent(monkey, Mesh{m});


	s.systems.push_back(new MeshRenderer(&s));
	s.systems.push_back(new Spin(&s));

	//------------------------------------------------------------------------
	s.Start();
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(const float deltaTime)
{
	//------------------------------------------------------------------------
	// Example Sprite Code....
	s.Update(deltaTime);

}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{	//------------------------------------------------------------------------

	// Render Suzanne
	//cam.Render(suzanne);
	s.Render();
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
}