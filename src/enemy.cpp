#include <iostream>
#include <cmath>
#include "../Framework.h"
#include "../game.h"

using namespace std;

void Enemy::SpriteCreate(int w, int h){
    this->w = w;
    this->h = h;
    sprite = createSprite("assets/enemy.png");
    setSpriteSize(sprite, w, h);
}

void Enemy::CreateEnemy(Platform& p){
    x = p.x + p.w / 2 - w / 2;
    y = p.y - h;
}
