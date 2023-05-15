#include <iostream>
#include <vector>
#include <math.h> 
#include "../Framework.h"
#include "../game.h"

using namespace std;

void GameScene::CreateGameScene(){
    srand(time(0));
    resolutionRatio = GetWidth() / 800;
    character.controlSpeed *= resolutionRatio;
    character.jumpForce *= resolutionRatio;
    scoring.SpriteCreate(GetWidth(), GetHeight());
    character.SpriteCreate(64*resolutionRatio, 64*resolutionRatio);
    skill.SpriteCreate(48*resolutionRatio, 48*resolutionRatio);
    enemy.SpriteCreate(80*resolutionRatio, 54*resolutionRatio);
    enemy.active = false;
    enemy.PositionUpdate(GetWidth()*2, GetHeight()*2);
    skill.PositionUpdate(GetWidth()*2, GetHeight()*2);
    backgroundSprite = createSprite("assets/background.png");
    setSpriteSize(backgroundSprite, GetWidth(), GetHeight());
    playButton = createSprite("assets/play.png");
    getSpriteSize(playButton, playButtonW, playButtonH);
    health = createSprite("assets/health.png");
    setSpriteSize(health, 48*GetWidth()/800, 48*GetHeight()/600);

    for (int i = 0; i < 10; i++) {
        Platform p;
        p.SpriteCreate(100*resolutionRatio, 20*resolutionRatio);
        platforms.push_back(p);
        p.PositionUpdate(rand() % (GetWidth() - 100), GetHeight() - 100 - GetHeight() / 10 * i);
    }
    character.PositionUpdate(GetBottomPlatform().x, GetBottomPlatform().y);
}

void GameScene::DrawGameScene(){
    if (!gameOver)
    {
        drawSprite(backgroundSprite, 0, 0);
        if (OnScreen(enemy.x, enemy.y))
        {
            enemy.active = true;
            EnemyOnScreen();
        }
        else
        {
            enemy.active = false;
        }

        character.DrawSprite();
        PlatformUpdate();
        skill.DrawSprite();
        drawSprite(health, GetWidth() - 48*resolutionRatio, 50);
        if (character.y < GetHeight()/2)
        {
            if (!OnScreenBottom(skill.y) && !character.autoAim)
            {
                skill.y += 1 * resolutionRatio;
            }
            if (!OnScreenBottom(enemy.y))
            {
                enemy.y += 1 * resolutionRatio;
            }
        }
        character.BulletUpdate(GetWidth(), GetHeight(), resolutionRatio);
        DrawScore();
        character.Move(GetWidth(), GetHeight(), resolutionRatio);

        scorePoints = scorePlatform*GetHeight()/10;
        CheckSkillCollection();
        
        if (character.autoAim)
        {
            CharacterAutoAimActive();
        }
    
        if (OnScreenBottom(character.y))
        {
            CharacterOnScreenBottom();
        }
    }
    else
    {
        drawSprite(backgroundSprite, 0, 0);
        DrawScore();
        drawSprite(playButton, GetWidth()/2-playButtonW/2, GetHeight()/2-playButtonH/2);
    }
}


void GameScene::PlatformUpdate(){
    for (int i = 0; i < platforms.size(); i++) {
        if (OnScreenBottom(platforms[i].y))
        {
            scorePlatform++;
            CreatePlatform(platforms[i], i);
        }
        if (CheckcharacterBottomCollision(character.x, character.y, character.w, character.h, platforms[i].x, platforms[i].y, platforms[i].w, platforms[i].h))
        {
            if (character.speed > 0 && OnScreen(platforms[i].x, platforms[i].y))
            {
                character.Jump();
            }
        }
        if (character.y < GetHeight()/2)
        {
            platforms[i].y += 1 * resolutionRatio;
            if (getTickCount() - timerBulletY >= 2) {
                timerBulletY = getTickCount();
                for (int i = 0; i < character.bullets.size(); i++)
                {
                    character.bullets[i].y += 1;
                }
            }
            
            
        }
        
        platforms[i].DrawSprite();
    }
    if (getTickCount() - timerPlatform >= 10) {
        timerPlatform = getTickCount();
        if (moveDown)
        {
            platforms[4].y += 1 * resolutionRatio;
            if (platforms[4].y >= maxY)
            {
                moveDown = false;
            }
        }
        else
        {
            platforms[4].y -= 1 * resolutionRatio;
            if (platforms[4].y <= minY)
            {
                moveDown = true;
            }
        }
    }    
}

void GameScene::EnemyOnScreen(){
    enemy.DrawSprite();
    for (int i = 0; i < character.bullets.size(); i++)
    {
        if (CheckCollision(character.bullets[i].x, character.bullets[i].y, character.bullets[i].w, character.bullets[i].h, enemy.x, enemy.y, enemy.w, enemy.h))
        {
            character.bullets.erase(character.bullets.begin() + i);
            enemy.x = -200;
            enemy.y = -200;
        }
        if (character.autoAim && enemy.active)
        {
            character.bullets[i].CalculatePosition(character.bullets[i].x, character.bullets[i].y, enemy.x, enemy.y);
        }
    }
    if (CheckCollision(character.x, character.y, character.w, character.h, enemy.x, enemy.y, enemy.w, enemy.h))
    {
        if (character.x + character.w >= enemy.x &&
            character.x <= enemy.x + enemy.w &&
            character.y + character.h >= enemy.y &&
            character.y <= enemy.y + enemy.h &&
            character.y + character.h < enemy.y + 20) 
        {
            enemy.x = -200;
            enemy.y = -200;
        }
        else{
            gameOver = true;
        }
    }
}

void GameScene::CharacterAutoAimActive(){
    scoring.DrawNumber(skill.x+24, skill.y+10, skill.duration);
    if (getTickCount() - timerBullet >= 500) {
        timerBullet = getTickCount();

        if (OnScreen(enemy.x, enemy.y))
        {
            character.AutoFireBullet(enemy.x+enemy.w/2, enemy.y+enemy.h/2);
        }
    }
    if (getTickCount() - timerSkill >= 1000) {
        timerSkill = getTickCount();
        if (skill.duration > 0)
        {
            skill.duration--;
        }
        else{
            skill.duration = 20;
            character.autoAim = false;
            skill.x = GetWidth();
            skill.y = GetHeight();
        }
    }
}

void GameScene::CharacterOnScreenBottom(){
    scoring.health--;

    if (scoring.health > 0)
    {
        if (character.autoAim)
        {
            skill.PositionUpdate(GetWidth(), GetHeight());
        }
        
        skill.duration = 20;
        character.PositionUpdate(GetBottomPlatform().x, GetBottomPlatform().y);
        character.autoAim = false;
    }
    else
    {
        gameOver = true;
    }
}

void GameScene::DrawScore(){
    scoring.DrawScoreBG();
    scoring.DrawNumber(GetWidth()-30, 5, scorePoints);
    scoring.DrawNumber(100, 5, scorePlatform);
    if (!gameOver)
    {
        scoring.DrawNumber(GetWidth()-skill.w+12, 60, scoring.health);
    }
}

int GameScene::GetWidth(){
    int w, h;
    getScreenSize(w, h);
    return w;
}
int GameScene::GetHeight(){
    int w, h;
    getScreenSize(w, h);
    return h;
}

void GameScene::CheckSkillCollection(){
    if (CheckCollision(character.x, character.y, character.w, character.h, skill.x, skill.y, skill.w, skill.h))
    {
        character.autoAim = true;
        skill.x = GetWidth() - skill.w;
        skill.y = 50+skill.h;
    }
}

void GameScene::CheckEnemyCollision(){
    if (CheckCollision(character.x, character.y, character.w, character.h, enemy.x, enemy.y, enemy.w, enemy.h))
    {
        gameOver = true;
        enemy.x = GetWidth() - 50;
        enemy.y = 50;
    }
}

bool GameScene::OnScreen(int objectX, int objectY){
    if (objectY < 0 || objectY > GetHeight() || objectX < 0 || objectX > GetWidth())
        return false;
    return true;
}

bool GameScene::OnScreenBottom(int objectY){
    if (GetHeight() < objectY)
        return true;
    return false;
}

void GameScene::CreatePlatform(Platform& p, int index){
    bool skillCreated = false;
    p.PositionUpdate(rand() % (GetWidth() - 100), -GetHeight() / 10);
    
    int r = rand() % 100;
    if (OnScreenBottom(skill.y))
    {
        if (r < 50) {
            if (character.autoAim == false && index != 4)
            {
                skill.CreateSkill(p);
                skillCreated = true;
            }
        }
    }
    if (OnScreenBottom(enemy.y) && skillCreated == false && index != 4)
    {
        if (r < 75) {
            enemy.CreateEnemy(p);
        }
    }
}

bool GameScene::CheckcharacterBottomCollision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2){
    if ((y1 + h1) > y2 &&
        y1 < (y2 + h2) &&
        (x1 + w1) > x2 &&
        x1 < (x2 + w2)) {
        return true;
    }
    return false;
}


bool GameScene::CheckCollision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
    if (x1 + w1 >= x2 &&
        x1 <= x2 + w2 &&
        y1 + h1 >= y2 &&
        y1 <= y2 + h2) {
        return true;
    }
    return false;
}

Platform GameScene::GetBottomPlatform(){
    Platform p = platforms[0];
    for (int i = 1; i < platforms.size(); i++)
    {
        if (platforms[i].y > p.y)
        {
            p = platforms[i];
        }
    }
    return p;
}

void GameScene::ResetWorld(){
    platforms.clear();
    character.bullets.clear();
    for (int i = 0; i < 10; i++) {
        Platform p;
        p.SpriteCreate(100*resolutionRatio, 20*resolutionRatio);
        platforms.push_back(p);
        p.PositionUpdate(rand() % (GetWidth() - 100), GetHeight() - 100 - GetHeight() / 10 * i);
    }
    character.timerMove = 0;
    timerBullet = 0;
    timerSkill = 0;
    scorePoints = 0;
    character.autoAim = false;
    scorePlatform = 0;
    character.PositionUpdate(GetBottomPlatform().x, GetBottomPlatform().y);
    scoring.health = 5;
    enemy.PositionUpdate(-200, -200);
    skill.PositionUpdate(-200, -200);
    gameOver = false;
}

void GameScene::MouseClick(int x, int y){
    if (gameOver)
    {
        if (GetWidth()/2-playButtonW/2 < x && GetWidth()/2-playButtonW/2 + playButtonW > x && GetHeight()/2-playButtonH/2 < y && GetHeight()/2-playButtonH/2 + playButtonH > y)
        {
            ResetWorld();
        }
    }
}
