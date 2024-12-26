#pragma once

#include <SFML/Audio.hpp>
#include <sfml/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Bullet.h"
#include "Arr.h"

using namespace sf;
using namespace std;

class Player                                        //未處理問題 玩家死掉 3號敵人 沒有人可以追蹤
{
    private:
        vector<Texture*> BulletModel;
        Sprite s,s2,right,left,mid,skill;
        RectangleShape box;
        Arr<Texture> *Right,*Left,*Mid,*Skill;
        Arr<Bullet> bullets;
        Vector2f dir;
        int level;
        int exp;
        int nextexp;
        int hp;
        int maxhp;
        int damage;
        int number;   //玩家編號
        int control[6];  //上 下 左 右 射擊  換型態
        int ShootTime;   
        int hurtTime;
        int mode; //子彈型號
        int change;
        int skillChange;
        int changeTime;   //換裝時間
        bool survive;   //生還
    public:
        Player(vector<Texture>& textures,Arr<Texture>& Right,Arr<Texture>& Left,Arr<Texture>& Mid,Arr<Texture>& Skill,int up =22 ,int down =18,int left=0,int right=3,int shoot =57,int change=38);
        virtual ~Player();

        static int PlayerNumber;

        Arr<Bullet>& GetBullet();
        const Vector2f& GetPlayerPos();
        Vector2f playermid();
        FloatRect getplayer();

        string updateUserInformation();
        int& getdamage();
        int& gethp();
        int& getlevel();
        void up();
        int& getexp();
        int& getNextExp();
        void hurt(int Damege);
        bool addExp(int Exp);
        void addHp(int hp);
        void UpdateShoot();
        void SetSurvive();
        bool GetSurvive();
        void UpdateArm();
        void InitVariable();
        void Move(float min);
        void update(float min);
        void restart();
        void render(RenderTarget *target);
        void back();

};

