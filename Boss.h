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
class Boss{

    private:
        Sprite s;
        int Hp;
        int Maxhp;
        int Exp;
        int hurtTime;
        int damage;
        float shootTime;

    public:
        Boss(Texture *texure,int Hp,int damage);
        virtual ~Boss();

        FloatRect getPos();
        Vector2f Getpos();
        void move(int a,int b);
        void hurt(int);
        void set(Vector2f pos);
        int getMaxHp();
        int getdamage();
        int getHp();
        void render(RenderTarget *target);
        void restart();

        static Arr<Bullet>bullet;
        static vector<Texture>texture;
        static void Init();
};