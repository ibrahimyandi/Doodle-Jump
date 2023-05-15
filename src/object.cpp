#include <iostream>
#include <cmath>
#include "../Framework.h"
#include "../game.h"

using namespace std;


void Object::PositionUpdate(int x, int y){
    this->x = x;
    this->y = y;
}

void Object::DrawSprite(){
    drawSprite(sprite, x, y);
}

bool Object::OnScreen(int objectX, int objectY, int screenWidth, int screenHeight){
    if (objectY < 0 || objectY > screenHeight || objectX < 0 || objectX > screenWidth)
        return false;
    return true;
}