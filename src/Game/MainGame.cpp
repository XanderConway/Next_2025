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
#include "../Game/Engine/GameObject.h"

#include <vector>

//------------------------------------------------------------------------
// Example data....
//------------------------------------------------------------------------
CSimpleSprite* testSprite;
enum
{
	ANIM_FORWARDS,
	ANIM_BACKWARDS,
	ANIM_LEFT,
	ANIM_RIGHT,
};
//------------------------------------------------------------------------


std::vector<GameObject*> gameObjectScenes;


//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	//------------------------------------------------------------------------
	// Example Sprite Code....
	testSprite = App::CreateSprite("./data/TestData/Test.bmp", 8, 4);
	testSprite->SetPosition(400.0f, 400.0f);
	const float speed = 1.0f / 15.0f;
	testSprite->CreateAnimation(ANIM_BACKWARDS, speed, { 0,1,2,3,4,5,6,7 });
	testSprite->CreateAnimation(ANIM_LEFT, speed, { 8,9,10,11,12,13,14,15 });
	testSprite->CreateAnimation(ANIM_RIGHT, speed, { 16,17,18,19,20,21,22,23 });
	testSprite->CreateAnimation(ANIM_FORWARDS, speed, { 24,25,26,27,28,29,30,31 });
	testSprite->SetScale(1.0f);

	GameObject *MainCamera = new GameObject();
	Camera *cam = new Camera(0, 1000);
	MainCamera->addComponent(cam);
	MainCamera->rot.y += 180;

	GameObject *go = new GameObject();;
	Model suzanne = readFromFile("./data/TestData/suzanne.obj");
	go->addComponent(new MeshRenderer(*cam, suzanne));

	gameObjectScenes.push_back(go);
	gameObjectScenes.push_back(MainCamera);

	for (GameObject *g : gameObjectScenes) {
		for (Component *c : g->components) {
			c->Start();
		}
	}

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
	testSprite->Update(deltaTime);
	for (GameObject* g : gameObjectScenes) {
		for (Component* c : g->components) {
			c->Update(deltaTime);
		}
	}

}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{


	for (GameObject* g : gameObjectScenes) {
		for (Component* c : g->components) {
			c->Render();
		}
	}
	// Render Suzanne
	//cam.Render(suzanne);
}
//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{
	//------------------------------------------------------------------------
	// Example Sprite Code....
	delete testSprite;
	//------------------------------------------------------------------------
}