#pragma once

#include <SFML/Audio.hpp>
#include <sfml/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Tag
{
    private:
        Font f;
        Text text;
        Vector2f direction;
        Sprite s;
        int duration;
        int maxduration;
        float speed;
    public:
        Tag(Font &font,string s,Color color,Vector2f pos,Vector2f dir,int size,int duration,float speed);
        Tag(Vector2f pos,Vector2f dir,int duration,float speed,float rotation);
        virtual ~Tag();

        Vector2f nor(Vector2f v,float length);
        int& getDuration();
        float Len(Vector2f length);
        void update();
        void Move();
        void render(RenderTarget *target);
        void render2(RenderTarget *target);

        static Texture temp;
        static void InitCrash();
};
