#include <iostream>
#include "../Framework.h"
#include "../game.h"

using namespace std;

void Character::SpriteCreate(int w, int h){
    this->w = w;
    this->h = h;
    characterL = createSprite("assets/doodle-left.png");
    setSpriteSize(characterL, w, h);
    characterR = createSprite("assets/doodle-right.png");
    setSpriteSize(characterR, w, h);
}


void Character::DrawSprite(){
    if (rotation == true)
    {
        drawSprite(characterL, x, y);
    }
    else
    {
        drawSprite(characterR, x, y);
    }
}

void Character::Jump(){
    speed = -jumpForce;
}

void Character::FireBullet(int mouseX, int mouseY) {
    if (!autoAim)
    {
        if (getTickCount() - reloadSpeed >= 500) {
            reloadSpeed = getTickCount();
            Bullet newBullet(x, y, mouseX, mouseY);
            bullets.push_back(newBullet);
        }
    }
}

void Character::AutoFireBullet(int mouseX, int mouseY) {
    Bullet newBullet(x, y, mouseX, mouseY);
    bullets.push_back(newBullet);
}

void Character::BulletUpdate(int screenW, int screenH, int resolutionRatio){
    for (int i = 0; i < bullets.size(); i++)
    {
        if (bullets[i].y > screenH || bullets[i].y < 0)
        {
            bullets.erase(bullets.begin() + i);
        }
        else{
            bullets[i].w *= resolutionRatio;
            bullets[i].h *= resolutionRatio;
            bulletSpeed *= resolutionRatio;
            bullets[i].DrawSprite();
            if (bullets[i].x - bullets[i].w > screenW) {
                bullets[i].x = - bullets[i].w;
            }
            if (bullets[i].x + bullets[i].w < 0) {
                bullets[i].x = screenW + bullets[i].w;
            }
        }
    }
}

void Character::Move(int screenW, int screenH, int resolutionRatio){
    if (getTickCount() - timerMove >= 20) {
        timerMove = getTickCount();
        if (leftKeyPressed)
        {
            x -= controlSpeed;
            rotation = true;
        }
        if (rightKeyPressed)
        {
            x += controlSpeed;
                rotation = false;
        }
        y += speed;
        speed += gravity * resolutionRatio;
    }

    if (x - w > screenW) {
        x = - w;
    }
    if (x + w < 0) {
        x = screenW + w;
    }
}