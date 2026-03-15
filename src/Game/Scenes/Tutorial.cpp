#include "../Game/Engine/ECS/Components/Components.h"
#include "../Game/Engine/ECS/Systems/MeshRenderer.h"
#include "../Game/Engine/ECS/Systems/PlayerController.h"
#include "../Game/Engine/ECS/Systems/CheckWin.h"
#include "../Game/Engine/ECS/Systems/TextRenderer.h"
#include "Scenes/Levels.h"
#include "../ContestAPI/app.h"


using namespace ECS;

void Tutorial::AddAssets() {

	// The Main Cam
	EntityID cam = world->addEntity();
	world->addComponent(cam, Position(0, 0, 0));
	world->addComponent(cam, Rotation(0, 0, 0));
	world->addComponent(cam, Camera(1, 1000));
	world->addComponent(cam, Player());

	// The Goal Camera
	EntityID secondCam = world->addEntity();
	world->addComponent(secondCam, Position(10, 0, 0));
	world->addComponent(secondCam, Rotation(0, 0, 0));
	world->addComponent(secondCam, Camera(Matrix4x4({
		{1064, 0, 0, 0},
		{0, 768, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 1, 0}
		})));
	world->addComponent(secondCam, Material{0.5f, 0.5f, 0.5f, true, false, true});
	world->addComponent(secondCam, GoalPerspective());

	// The Monkey Model
	Model* m = readFromFile("./data/TestData/suzanne.obj");
	EntityID monkey = world->addEntity();
	world->addComponent(monkey, Position(10, 0, 50));
	world->addComponent(monkey, Rotation(0, 3.14, 0));
	world->addComponent(monkey, Scale{ 10 });
	world->addComponent(monkey, Mesh{ m });

	// The Room Model
	Model* roomModel = readFromFile("./data/TestData/room.obj");
	EntityID room = world->addEntity();
	world->addComponent(room, Position(0, 0, 0));
	world->addComponent(room, Rotation(0, 0, 0));
	world->addComponent(room, Scale{ 50 });
	world->addComponent(room, Mesh{ roomModel });
	world->addComponent(room, Material(0.5, 0, 0, false, false, true));

	EntityID text1 = world->addEntity();
	world->addComponent(text1, Text(controlsText1, 300, 100, GLUT_BITMAP_TIMES_ROMAN_24));
	world->addComponent(text1, Material{ 1, 1, 1 });

	EntityID text2 = world->addEntity();
	world->addComponent(text2, Text(controlsText2, 300, 130, GLUT_BITMAP_TIMES_ROMAN_24));
	world->addComponent(text2, Material{ 1, 1, 1 });


	EntityID text3 = world->addEntity();
	world->addComponent(text3, Text(tutorialText2, 310, 170, GLUT_BITMAP_TIMES_ROMAN_24));
	world->addComponent(text3, Material{ 1, 1, 1 });


	// Register Systems
	world->systems.push_back(new PlayerController(world, Vec3<float>(-25, -25, -25), Vec3<float>(25, 25, 25)));
	world->systems.push_back(new CheckWin(world));
	world->systems.push_back(new MeshRenderer(world));
	world->systems.push_back(new TextRenderer(world));

}
