#pragma once

#include <SFML/Audio.hpp>
#include <sfml/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Arr.h"
#include "Bullet.h"
#include <iostream>


using namespace sf;
using namespace std;
class Enemy
{
    private:
        Texture *texture;
        Sprite s;
        Vector2f length;

        int hp;
        int hpmax;
        int damage;
        int hurtTime;
        int exp;
        int type;
        int playerNB;
        float shootTime;

    public:
        Enemy(Texture * texture,Texture * texture2,Vector2u pos,int type,int playerNB,int playerLevel,int min);  
        virtual ~Enemy();

        FloatRect getpos();
        Vector2i gethp_hpmax();
        Vector2f Getpos();
        Vector2f nor(Vector2f v,float length);
        int getdamage();
        int getExp();
        int getPlayerNB();   //追蹤的玩家是哪位
        int getEnemyType();   //是哪一類的敵人

        void hurt(int damage);
        void Move(Vector2f playerPos,int type);
        float Len(Vector2f length);
        void render(RenderTarget *target);

        static Arr<Bullet> bullet;
};