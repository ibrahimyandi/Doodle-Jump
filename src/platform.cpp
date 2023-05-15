#include <iostream>
#include "../Framework.h"
#include "../game.h"

using namespace std;

void Platform::SpriteCreate(int w, int h){
    this->w = w;
    this->h = h;
    sprite = createSprite("assets/platform.png");
    setSpriteSize(sprite, w, h);
}