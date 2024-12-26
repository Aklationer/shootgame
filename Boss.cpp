#include "Boss.h"

Arr<Bullet> Boss::bullet;
vector<Texture> Boss::texture;

void Boss::Init(){
    Boss::texture.push_back(Texture());
    Boss::texture[0].loadFromFile("texture/Bullet/bossbullet.png");
}

Boss::Boss(Texture *texure,int Hp,int damage){
    this->s.setTexture(*texure);
    this->Hp=Hp;
    this->Maxhp=Hp;
    this->hurtTime=0;
    this->shootTime=30.f;
    this->damage=damage;
    this->s.setScale(0.75,0.75);
    this->s.setPosition(1300,300);

}

Boss::~Boss(){

}

FloatRect Boss::getPos(){
    return this->s.getGlobalBounds();
}

Vector2f Boss::Getpos(){
    return this->s.getPosition();
}

void Boss::hurt(int damage){
    this->Hp-=damage;
    this->hurtTime=3;
}

int Boss::getMaxHp(){
    return this->Maxhp;
}

int Boss::getdamage(){
    return this->damage;
}

int Boss::getHp(){
    return this->Hp;
}

void Boss::set(Vector2f pos){
    this->s.setPosition(pos);
}

void Boss::restart(){
    this->Hp=this->Maxhp;
}

void Boss::move(int a,int b){
    this->s.move(a*7,b*7);
    if(this->hurtTime>0)
        this->s.setColor(Color(173,0,0));
    else
        this->s.setColor(Color::White);
    this->hurtTime--;
    if(this->shootTime>=30.f){
        Boss::bullet.add(Bullet(&Boss::texture[0],Vector2f(this->s.getPosition().x+this->s.getGlobalBounds().width/2,this->s.getPosition().y+this->s.getGlobalBounds().height/2),Vector2f(1,1),2.f,Vector2f(20.f,0),Vector2f(-1,0)));
        this->shootTime=0.f;
    }
    this->shootTime+=0.5f;
}

void Boss::render(RenderTarget *target){
    target->draw(this->s);
    for(size_t i=0;i<Boss::bullet.Size();i++)
        Boss::bullet[i].render(target);
}
