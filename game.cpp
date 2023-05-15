#include <iostream>
#include <cstring>
#include "Framework.h"
#include "game.h"

using namespace std;

/* Test Framework realization */
class MyFramework : public Framework {
public:
	int screenWidth;
	int screenHeight;
	int mouse_x;
	int mouse_y;
	GameScene gameScene;
	
	MyFramework(int& w, int& h){
   		screenWidth = w;
		screenHeight = h;
	}
	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		width = screenWidth;
		height = screenHeight;
		fullscreen = true;
	}

	virtual bool Init() {
		gameScene.CreateGameScene();
		return true;
	}

	virtual void Close() {
	}

	virtual bool Tick() {
		gameScene.DrawGameScene();
		return false;
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) {
		mouse_x = x;
		mouse_y = y;
	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) {
		if (button == FRMouseButton::LEFT) {
			gameScene.character.FireBullet(mouse_x, mouse_y);
			gameScene.MouseClick(mouse_x, mouse_y);
		}
	}

	virtual void onKeyPressed(FRKey k) {
		if (k == FRKey::LEFT) {
			gameScene.character.leftKeyPressed = true;
		}
		else if (k == FRKey::RIGHT) {
			gameScene.character.rightKeyPressed = true;
		}
	}

	virtual void onKeyReleased(FRKey k) {
		if (k == FRKey::LEFT) {
			gameScene.character.leftKeyPressed = false;
		}
		else if (k == FRKey::RIGHT) {
			gameScene.character.rightKeyPressed = false;
		}	
	}
	
	virtual const char* GetTitle() override
	{
		return "Arcanoid";
	}
};


int main(int argc, char *argv[])
{
	int screenWidth = 800;
	int screenHeight = 600;
    bool fullscreen = false;

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-window") == 0)
        {
            if (i + 1 < argc)
            {
                sscanf(argv[i + 1], "%dx%d", &screenWidth, &screenHeight);
            }
        }
    }
    MyFramework framework(screenWidth, screenHeight);
	return run(&framework);
}
