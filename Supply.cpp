#include "Supply.h"

Supply::Supply(Texture* texture,Vector2f pos,float duration,int type){
    this->s.setTexture(*texture);
    this->s.setOrigin(this->s.getGlobalBounds().width/2,this->s.getGlobalBounds().height/2);
    this->s.setPosition(pos);
    if(this->type!=8)
        this->s.setScale(0.8f,0.8f);
    this->duration=duration;
    this->type=type;
}

Supply::~Supply(){

}

FloatRect Supply::getsupply(){
    return this->s.getGlobalBounds();
}

bool Supply::move(){
    if(this->duration>=0){
        this->duration-=0.25;
        this->s.rotate(5.f);
        this->s.move(2.5f,0.f);
        return false;
    }
    return true;
}

int& Supply::getType(){
    return this->type;
}

void Supply::render(RenderTarget *target){
    target->draw(this->s);
}