#pragma once

#include <SFML/Audio.hpp>
#include <sfml/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include "Tag.h"
#include "Arr.h"
#include "Boss.h"
#include "Supply.h"
#include <iostream>
#include <fstream>

using namespace sf;
using namespace std;
class Game{
    private:
        RenderWindow *window;
        vector<Texture> textures,Bg;
        Arr<Player> player;
        Font f;
        Text EnemyHp,GameOver,UserInformation,Point,Hint,Hint2,board,WIN,People;
        Event evt;
        Arr<Texture> right,left,mid,skill;
        Arr<Enemy> enemies;
        Arr<Tag> tags,crash;
        Arr<Supply>supply;
        vector<Boss> boss;
        RectangleShape expbar,shield,ice,bossHp;
        Texture Bubble;
        Sprite bubble;
        int pp,aa,bb;  //pp 用來算boss何時變移動方向
        int boosIndex;
        View view;
        float spawntime;
        float spawntime2;
        float spawntime3;
        float supplytime;
        float Min;
        int keytime;
        int point;
        int y;
        int index;
        int Bestpoint;
        float shieldTime;
        float iceTime;
        bool gg;
        bool start;
        bool win;
        bool people;
        bool bossTime;
    public:
        Game();
        virtual ~Game();

        bool run();
        void InitWindow();
        void InitVariable();
        void InitText();
        void PollEvent();
        void update();
        void UpdatePlayrBulletSize(); //看子彈有沒有超過視窗
        void UpdateText_expbar(int num);
        void UpdateEnemy();
        void UpdateTag();
        void Spawn();
        void render();
        void restart();
        void rdFile(string s,Arr<Texture>& t);
};

