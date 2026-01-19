#include "Scenes/Levels.h"
#include "../Game/Engine/ECS/Components/Components.h"
#include "../Game/Engine/ECS/Systems/TextRenderer.h"
#include "../Game/Engine/ECS/Systems/MenuController.h"
#include "../Game/Engine/ECS/Systems/MeshRenderer.h"
#include "../Game/Engine/ECS/Systems/Spin.h"

#include "../ContestAPI/app.h"

using namespace ECS;

void MainMenu::AddAssets() {

	EntityID title = world->addEntity();
	world->addComponent(title, Text(titleText, 500, 500, GLUT_BITMAP_TIMES_ROMAN_24));
	world->addComponent(title, Material{ 1, 1, 1 });

	EntityID start = world->addEntity();
	world->addComponent(start, Text(startText, 1064 / 2, 350, GLUT_BITMAP_TIMES_ROMAN_24));
	world->addComponent(start, Material{1, 1, 1});

	Model* cubeModel = readFromFile("./data/TestData/room.obj");

	EntityID cam = world->addEntity();
	world->addComponent(cam, Position(0, 0, -200));
	world->addComponent(cam, Rotation(0, 0, 0));
	world->addComponent(cam, Camera(1, 1000));
	world->addComponent(cam, Player());

	// The Goal Camera
	EntityID secondCam = world->addEntity();
	world->addComponent(secondCam, Position(10, 0, -200));
	world->addComponent(secondCam, Rotation(0, 0, 0));
	world->addComponent(secondCam, Camera(Matrix4x4({
		{1064, 0, 0, 0},
		{0, 768, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 1, 0}
		})));
	world->addComponent(secondCam, Material{ 0.5f, 0.5f, 0.5f, true, false, true });
	world->addComponent(secondCam, GoalPerspective());


	for (int i = 0; i < 100; i++) {

		Vec3<float> p = getRand(-100, 100);
		Vec3<float> r = getRand(0, 6);
		Vec3<float> s = getRand(0.5, 1);

		EntityID cube = world->addEntity();
		world->addComponent(cube, Position(p.x, p.y, p.z));
		world->addComponent(cube, Rotation(r.x, r.y, r.z));
		world->addComponent(cube, Scale{ s.x * 10 });
		world->addComponent(cube, Mesh{ cubeModel });
		world->addComponent(cube, Material(s.y, s.z, 1, false, true, false));
	}

	world->systems.push_back(new MeshRenderer(world));
	world->systems.push_back(new MenuController(world));
	world->systems.push_back(new TextRenderer(world));
	world->systems.push_back(new Spin(world));

}
