#pragma once

#include <SFML/Audio.hpp>
#include <sfml/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Arr.h"

using namespace sf;

class Supply
{
    private:
        Sprite s;
        float duration;
        int type;
    public:
        Supply(Texture* texture,Vector2f pos,float duration,int type);
        virtual ~Supply();

        FloatRect getsupply();
        int& getType();
        bool move();
        void render(RenderTarget *target);
};