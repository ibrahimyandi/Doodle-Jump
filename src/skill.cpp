#include <iostream>
#include <cmath>
#include "../Framework.h"
#include "../game.h"

using namespace std;

void Skill::SpriteCreate(int w, int h){
    this->w = w;
    this->h = h;
    sprite = createSprite("assets/autoAim.png");
    setSpriteSize(sprite, w, h);
}


void Skill::CreateSkill(Platform& p){
    x = p.x + p.w / 2 - w / 2;
    y = p.y - h;
}