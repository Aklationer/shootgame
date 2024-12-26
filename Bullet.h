#pragma once

#include <SFML/Audio.hpp>
#include <sfml/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Bullet
{
    private:
        Texture *bulletTexture;
        Sprite s;
        Vector2f Maxspeed; //可移動最大速度
        Vector2f speed;   //移動速度
        Vector2f dir;

        float speed_up; //速度累加值
    public:
        Bullet(Texture *texture,Vector2f pos,Vector2f scale,float speed_up,Vector2f speed = Vector2f(20.f,0),Vector2f dir=Vector2f(1,0),float duration=30);
        virtual ~Bullet();

        Vector2f nor(Vector2f v,float length);
        FloatRect GetPos();
        float Len(Vector2f length);
    
        void Move();
        void upate();
        void render(RenderTarget *target);
};