#include <iostream>
#include "../Framework.h"
#include "../game.h"

using namespace std;

void Scoring::SpriteCreate(int w, int h){
    this->w = w;
    this->h = h;
    scoreBg = createSprite("assets/scoreBg.png");
    setSpriteSize(scoreBg, w, 60);
    healthBG = createSprite("assets/health.png");
    number_0 = createSprite("assets/scoreDigits/number_0.png");
    number_1 = createSprite("assets/scoreDigits/number_1.png");
    number_2 = createSprite("assets/scoreDigits/number_2.png");
    number_3 = createSprite("assets/scoreDigits/number_3.png");
    number_4 = createSprite("assets/scoreDigits/number_4.png");
    number_5 = createSprite("assets/scoreDigits/number_5.png");
    number_6 = createSprite("assets/scoreDigits/number_6.png");
    number_7 = createSprite("assets/scoreDigits/number_7.png");
    number_8 = createSprite("assets/scoreDigits/number_8.png");
    number_9 = createSprite("assets/scoreDigits/number_9.png");
}

void Scoring::DrawScoreBG(){
    drawSprite(scoreBg, 0, 0);
}
void Scoring::DrawNumber(int x, int y, int number){
    if (number == 0)
    {
        drawSprite(number_0, x, y);
    }
    
    while (number > 0) {
        int digit = number % 10;
        number /= 10;

        Sprite* digit_surface = NULL;
        switch (digit) {
            case 0:
                digit_surface = number_0;
                break;
            case 1:
                digit_surface = number_1;
                break;
            case 2:
                digit_surface = number_2;
                break;
            case 3:
                digit_surface = number_3;
                break;
            case 4:
                digit_surface = number_4;
                break;
            case 5:
                digit_surface = number_5;
                break;
            case 6:
                digit_surface = number_6;
                break;
            case 7:
                digit_surface = number_7;
                break;
            case 8:
                digit_surface = number_8;
                break;
            case 9:
                digit_surface = number_9;
                break;
        }
        drawSprite(digit_surface, x, y);
        x -= 24;
    }
}
