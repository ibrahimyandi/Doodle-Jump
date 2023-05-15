#include <iostream>
#include <cmath>
#include "../Framework.h"
#include "../game.h"

using namespace std;

Bullet::Bullet(int startX, int startY, int targetX, int targetY){
    x = startX;
    y = startY;
    w = 16;
    h = 16;
    SpriteCreate();
    CalculatePosition(startX, startY, targetX, targetY);
}

void Bullet::SpriteCreate(){
    sprite = createSprite("assets/bullet.png");
    setSpriteSize(sprite, w, h);
}

void Bullet::DrawSprite() {
    x += dx;
    y += dy;
    drawSprite(sprite, x, y);
}

void Bullet::CalculatePosition(int startX, int startY, int targetX, int targetY){
    double angle = atan2(targetY - startY, targetX - startX);
    double speed = 2.0;

    dx = speed * cos(angle);
    dy = speed * sin(angle);
    
    x = startX;
    y = startY;
}