#include "../Game/Scenes/SceneManager.h"

struct MainMenu : public Scene {
	char* titleText = "<<SEEING DOUBLE>>";
	char* startText = "Press Space to Start";
	void AddAssets() override;
};

struct Level1 : public Scene {
	char* tutorialText1 = "Use Arrow Keys to Move, and WASD to look around";
	char* tutorialText2 = "Align your view with the outline to win!";
	void AddAssets() override;
};
