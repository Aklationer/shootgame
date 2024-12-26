#include "Tag.h"

Texture Tag::temp;

void Tag::InitCrash(){
    Tag::temp.loadFromFile("texture/Enemy/crash.png");
}
//Private

//Constructor Destructor
Tag::Tag(Font &font,string s,Color color,Vector2f pos,Vector2f dir,int size,int duration,float speed){
    this->text.setFont(font);
    this->text.setString(s);
    this->text.setCharacterSize(size);
    this->text.setFillColor(color);
    this->text.setPosition(pos);
    
    this->direction=dir;
    this->duration=duration;
    this->maxduration=this->duration;
    this->speed=speed;
}

Tag::Tag(Vector2f pos,Vector2f dir,int duration,float speed,float rotation){
    this->s.setOrigin(this->s.getGlobalBounds().width/2,this->s.getGlobalBounds().height/2);
    this->s.setTexture(Tag::temp);
    this->s.setRotation(rotation);
    dir.x+=rand()%18-9;
    dir.y+=rand()%18-9;
    this->direction=this->nor(dir,this->Len(dir));
    this->s.setPosition(pos);
    this->duration=duration;
    this->speed=speed;
}

Tag::~Tag(){

}

//Function
void Tag::update(){
    if(this->duration>0){
        this->duration--;
        if(this->duration > this->maxduration/2)
            this->text.move((this->speed*2)*this->direction.x,(this->speed*2)*this->direction.y);
        else
            this->text.move(this->speed*this->direction.x,this->speed*this->direction.y);
    }
}

int& Tag::getDuration(){
    return this->duration;
}

float Tag::Len(Vector2f length){
    return sqrt(pow(length.x,2)+pow(length.y,2));
}

void Tag::Move(){
    this->s.move(this->speed*this->direction.x,this->speed*this->direction.y);
    this->duration--;
}

Vector2f Tag::nor(Vector2f v,float length){
    return v/length;
}

void Tag::render(RenderTarget *target){
    target->draw(this->text);
}

void Tag::render2(RenderTarget *target){
    target->draw(this->s);
}