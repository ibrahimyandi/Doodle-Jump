#ifndef GAME_H
#define GAME_H
#include <vector>

using namespace std;

class GameScene;
class Object;
class Scoring;
class Platform;
class Bullet;
class Enemy;
class Skill;
class Sprite;
class Character;
class Numbers;

class Object {
public:
    Sprite* sprite;
    int x, y, w, h;
    bool active;

    virtual void PositionUpdate(int x, int y);
    void ScreenOutControl();
    virtual void DrawSprite();
    bool OnScreen(int objectX, int objectY, int screenWidth, int screenHeight);
};


class Character : public Object {
public:
    Sprite* characterL;
    Sprite* characterR;
    vector<Bullet> bullets;
    int speed = 0;
	float jumpForce = 15.0f;
	float gravity = 1.0f;
    int controlSpeed = 10;
    int timerMove = 0;
    int reloadTimer = 0;
	int reloadSpeed = 500;
    int bulletSpeed = 6;
    int rotation = true;
    bool leftKeyPressed = false;
	bool rightKeyPressed = false;
    bool autoAim = false;

    void SpriteCreate(int w, int h);
    void Jump();
    void Move(int screenW, int screenH, int resolutionRatio);
    void FireBullet(int mouseX, int mouseY);
    void AutoFireBullet(int mouseX, int mouseY);
    void DrawSprite() override;
    void BulletUpdate(int screenW, int screenH, int resolutionRatio);
};

class Scoring {
public:
	Sprite* number_0;
	Sprite* number_1;
	Sprite* number_2;
	Sprite* number_3;
	Sprite* number_4;
	Sprite* number_5;
	Sprite* number_6;
	Sprite* number_7;
	Sprite* number_8;
	Sprite* number_9;
	Sprite* scoreBg;
    Sprite* healthBG;

    int health = 5;
    int w, h;
    
    void SpriteCreate(int w, int h);
    void DrawScoreBG();
    void DrawNumber(int x, int y, int number);
};

class Platform : public Object {
public:
    void SpriteCreate(int w, int h);
};

class Bullet : public Object {
public:
    int dx, dy, angle;

    Bullet(int startX, int startY, int targetX, int targetY);
    void SpriteCreate();
    void DrawSprite() override;
    void CalculatePosition(int startX, int startY, int targetX, int targetY);
};

class Enemy : public Object {
public:
    void SpriteCreate(int w, int h);
    void CreateEnemy(Platform& p);
};

class Skill : public Object {
public:
    int healthX;
    int healthY;
    int durationX;
    int durationY;
    int duration = 20;
    Sprite* number_0;
	Sprite* number_1;
	Sprite* number_2;
	Sprite* number_3;
	Sprite* number_4;
	Sprite* number_5;
	Sprite* number_6;
	Sprite* number_7;
	Sprite* number_8;
	Sprite* number_9;
    void SpriteCreate(int w, int h);
    void CreateSkill(Platform& p);
    void SkillDuration(int duration);
};
class GameScene {
public:
	Scoring scoring;
    Character character;
    Enemy enemy;
    Skill skill;
    bool rotation = true;
    bool gameOver = true;
    vector<Platform> platforms;
	Sprite* backgroundSprite;
    Sprite* health;
    Sprite* playButton;
    int timerBullet = 0;
    int timerBulletY = 0;
    int timerPlatform = 0;
    int timerSkill = 0;
    int scorePoints = 0;
    int scorePlatform = 0;
    int bottomPlatform = 0;
    bool moveDown = true;
    float minY = 100;
    float maxY = 200;
    int playButtonW, playButtonH;
    int resolutionRatio = 1;
    float widthScale, heightScale;

    void PlatformUpdate();
    void EnemyOnScreen();
    void CharacterAutoAimActive();
    void CharacterOnScreenBottom();
    void CreateGameScene();
    void DrawGameScene();
    void DrawScore();
    int GetWidth();
    int GetHeight();
    void CheckSkillCollection();
    void CheckEnemyCollision();
    bool OnScreen(int objectX, int objectY);
    bool OnScreenBottom(int objectY);
    void CreatePlatform(Platform& p, int index);
    bool CheckcharacterBottomCollision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
    bool CheckCollision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
    Platform GetBottomPlatform();
    void ResetWorld();
    void MouseClick(int x, int y);
};


#endif // GAME_H
