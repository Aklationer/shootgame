#include "Enemy.h"

Arr<Bullet> Enemy::bullet;
//construstor destructor
Enemy::Enemy(Texture * texture,Texture * texture2,Vector2u pos,int type,int playerNB,int playerLevel,int min){
    int temp;
    if(type==5){
        temp=rand()%4+1;
        this->s.setScale(0.2f,0.2f);
    }  
    else if(type==6){
        temp=rand()%3+1;
        this->s.setScale(0.2f,0.2f);
    }
    else{
        temp=rand()%2+1;
        this->s.setScale(0.3f,0.3f);
    }
    this->shootTime=0.f;
    this->type=type;
    this->hpmax=temp+2*playerLevel;
    this->hp=temp+2*playerLevel;
    this->exp=temp+2*playerLevel;
    this->damage=rand()%2+playerLevel;   
    this->s.setTexture(*texture);
    this->texture=texture2;
    this->s.setPosition(float(pos.x)+min,float(abs(rand()%pos.y-this->s.getGlobalBounds().height)));
    this->hurtTime=0;   //變紅的時間
    this->playerNB=playerNB;
}

Enemy::~Enemy(){

}

//Function
FloatRect Enemy::getpos(){
    return this->s.getGlobalBounds();
}

Vector2i Enemy::gethp_hpmax(){
    return Vector2i(this->hp,this->hpmax);
}

Vector2f Enemy::Getpos(){
    return this->s.getPosition();
}

int Enemy::getdamage(){
    return this->damage;
}

int Enemy::getPlayerNB(){
    return this->playerNB;
}

int Enemy::getExp(){
    return this->exp;
}

int Enemy::getEnemyType(){
    return this->type;
}

float Enemy::Len(Vector2f length){
    return sqrt(pow(length.x,2)+pow(length.y,2));
}

Vector2f Enemy::nor(Vector2f v,float length){
    return v/length;
}

void Enemy::Move(Vector2f playerPos,int type){
    if(this->type==5){
        Vector2f rota;    //length旋轉角度  rota算如何移動到玩家
        this->length.x=playerPos.x-this->s.getPosition().x;
        this->length.y=playerPos.y-this->s.getPosition().y;
        rota=this->nor(this->length,this->Len(this->length));
        this->s.setRotation(atan2(this->length.y,this->length.x)*180/float(3.1415926) + 180);
        if(rota.x>-0.7f)
            rota.x=-0.7f;
        this->s.move(rota.x*4,rota.y*4);
    }
    else if(this->type==6)
        this->s.move(-18,0);
    else{
        this->length.x=playerPos.x-this->s.getPosition().x;
        this->length.y=playerPos.y-this->s.getPosition().y;
        this->s.setRotation(atan2(this->length.y,this->length.x)*180/float(3.1415926)+180);
        if(this->shootTime <=40.f)
            this->shootTime+=0.5;
        else{
            Enemy::bullet.add(Bullet(this->texture,Vector2f(this->s.getPosition().x-this->s.getGlobalBounds().width/2,this->s.getPosition().y-this->s.getGlobalBounds().height/2),Vector2f(1.f,1.f),1.f,Vector2f(5.f,0.f),this->nor(length,this->Len(length))));
            this->shootTime=0.f;
        }
        this->s.move(-10,0);
    }
    if(this->hurtTime>0)
        this->s.setColor(Color(173,0,0));
    else
        this->s.setColor(Color::White);
    this->hurtTime--;
}

void Enemy::hurt(int damage){
    this->hp-=damage;
    this->s.move(15.f,0);
    this->hurtTime=2;
}

void Enemy::render(RenderTarget *target){
    target->draw(this->s);
    for(size_t i=0;i<this->bullet.Size();i++)
        this->bullet[i].render(target);
}
