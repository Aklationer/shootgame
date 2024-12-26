#include "Bullet.h"

//Private

//Constructor Destructor
Bullet::Bullet(Texture *texture,Vector2f pos,Vector2f scale,float speed_up,Vector2f speed,Vector2f dir,float duration){
    this->bulletTexture=texture;
    this->s.setTexture(*this->bulletTexture);
    this->s.setPosition(pos);
    this->s.setScale(scale);
    this->Maxspeed=speed;
    this->speed_up=speed_up;
    this->speed.x=0.f;
    this->speed.y=0.f;
    this->dir=dir;
    this->s.setRotation(atan2(this->dir.y,this->dir.x)*180/float(3.1415926) + 180);
}

Bullet::~Bullet(){
    
}

float Bullet::Len(Vector2f length){
    return sqrt(pow(length.x,2)+pow(length.y,2));
}

void Bullet::upate(){
    this->Move();
}

void Bullet::Move(){
    if(this->speed.x<this->Maxspeed.x){
        this->speed.x+=this->speed_up;
        this->speed.y+=this->speed_up;
    }
    this->s.move(this->speed.x*this->dir.x,this->speed.y*this->dir.y);
}

void Bullet::render(RenderTarget *target){
    target->draw(this->s);
}

FloatRect Bullet::GetPos(){
    return this->s.getGlobalBounds();
}



