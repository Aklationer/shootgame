#include "Player.h"

int Player::PlayerNumber = 1;
//Private

//Constructor and Destructor
Player::Player(vector<Texture>& textures,Arr<Texture>& Right,Arr<Texture>& Left,Arr<Texture>& Mid,Arr<Texture>& Skill,int up,int down,int left ,int right, int shoot,int change){
    this->InitVariable();
    this->s.setTexture(textures[0]);
    this->s.setScale(0.13f,0.1f);

    this->s2.setTexture(textures[4]);
    this->s2.setRotation(90.f);
    this->s2.setOrigin(this->s2.getGlobalBounds().width/2,this->s2.getGlobalBounds().height/2);

    this->Right=&Right;
    this->Left=&Left;
    this->Mid=&Mid;
    this->Skill=&Skill;
    this->right.setTexture((*this->Right)[4]);
    this->left.setTexture((*this->Left)[4]);
    this->mid.setTexture((*this->Mid)[4]);
    this->skill.setTexture((*this->Skill)[2]);
    this->right.setOrigin(this->right.getGlobalBounds().width/2,this->right.getGlobalBounds().height/2);
    this->left.setOrigin(this->left.getGlobalBounds().width/2,this->left.getGlobalBounds().height/2);
    this->mid.setOrigin(this->mid.getGlobalBounds().width/2,this->mid.getGlobalBounds().height/2);
    this->skill.setOrigin(this->skill.getGlobalBounds().width/2,this->skill.getGlobalBounds().height/2);
    this->right.setRotation(90.f);
    this->left.setRotation(90.f);
    this->mid.setRotation(90.f);
    this->skill.setRotation(90.f);
    this->right.setScale(0.72f,0.72f);
    this->left.setScale(0.72f,0.72f);
    this->mid.setScale(0.72f,0.72f);
    this->skill.setScale(0.85f,0.85f);
    

    this->BulletModel.push_back(&textures[1]);
    this->BulletModel.push_back(&textures[2]);
    this->control[0]=up;
    this->control[1]=down;
    this->control[2]=left;
    this->control[3]=right;
    this->control[4]=shoot;
    this->control[5]=change;
    this->change=4;
    this->skillChange=2;
}

Player::~Player(){

}

//Function
void Player::InitVariable(){
    this->survive=true;
    this->changeTime=0;
    this->mode = 0;
    this->level = 1;
    this->exp = 0;
    this->nextexp = static_cast<int>((35 / 3) * ((pow(this->level, 3) - 6 * pow(this->level, 2)) + 16 * this->level - 10));
    this->hp = 10;
    this->maxhp = 10;
    this->damage = 1;
    this->ShootTime =20;
    this->hurtTime=0;
    this->number = Player::PlayerNumber;
    Player::PlayerNumber++;
}

void Player::Move(float min) {
    if (Keyboard::isKeyPressed(Keyboard::Key::C)){
        this->mode++;
        this->mode %= 2;
        if(this->mode)
            this->damage=1;
        else 
            this->damage=2;
    }
    if (Keyboard::isKeyPressed(Keyboard::Key(this->control[0])) &&this->GetPlayerPos().y>=10){
        this->s.move(0.f, -15.f);
        this->dir=Vector2f(0.f,1.f);
    }
    if (Keyboard::isKeyPressed(Keyboard::Key(this->control[1])) &&this->GetPlayerPos().y<=986-this->getplayer().height){
        this->s.move(0.f, 15.f);
        this->dir=Vector2f(0.f,-1.f);
    }
    if (Keyboard::isKeyPressed(Keyboard::Key(this->control[2]))){
        this->s.move(-15.f, 0.f);
        this->dir=Vector2f(1.f,0.f);
    }
    if (Keyboard::isKeyPressed(Keyboard::Key(this->control[3])) &&this->GetPlayerPos().x<=1900-this->getplayer().width+min){
        this->s.move(15.f, 0.f);
        this->dir=Vector2f(-1.f,0.f);
    }
    if (Keyboard::isKeyPressed(Keyboard::Key(this->control[4])) && this->ShootTime >= 20) {
        if (this->mode) {
            this->bullets.add(Bullet(this->BulletModel[1], Vector2f(this->playermid().x + 70, this->playermid().y), Vector2f(0.15f, 0.15f), 3.f, Vector2f(50.f, 0)));
            this->ShootTime = 0;
            this->s2.move(-20, 0);
        }
        else {
            this->bullets.add(Bullet(this->BulletModel[0], Vector2f(this->playermid().x, this->playermid().y + 20), Vector2f(0.05f, 0.05f), 2.f));
            this->bullets.add(Bullet(this->BulletModel[0], Vector2f(this->playermid().x, this->playermid().y - 20), Vector2f(0.05f, 0.05f), 2.f));
            this->ShootTime = 0;
            
        }
    }
    if (Keyboard::isKeyPressed(Keyboard::Key(this->control[5])) &&this->changeTime>=10){
        this->change++;
        this->right.setTexture((*this->Right)[(this->change)%this->Right->Size()]);
        this->left.setTexture((*this->Left)[(this->change)%this->Left->Size()]);
        this->mid.setTexture((*this->Mid)[(this->change)%this->Mid->Size()]);
        this->skill.setTexture((*this->Skill)[(++this->skillChange)%this->Skill->Size()]);
        this->changeTime=0;
    }
    if(this->s.getPosition().x<min)
        this->s.setPosition(0+min,this->s.getPosition().y);
    this->changeTime++;
}

void Player::update(float min){
    this->UpdateArm();
    this->Move(min);
    this->UpdateShoot();
    for (size_t i = 0; i < this->bullets.Size(); i++) {
        this->bullets[i].upate();
    }
    if(this->hurtTime>0){
        if(this->hurtTime%2){
            this->s.setColor(Color(173,0,0));
            this->right.setColor(Color(173,0,0));
            this->left.setColor(Color(173,0,0));
            this->mid.setColor(Color(173,0,0));
        }
        else{
            this->s.setColor(Color::White);
            this->right.setColor(Color::White);
            this->left.setColor(Color::White);
            this->mid.setColor(Color::White);
        }
    }
    else{
        this->s.setColor(Color::White);
        this->right.setColor(Color::White);
        this->left.setColor(Color::White);
        this->mid.setColor(Color::White);
    }
    this->hurtTime--;
}

void Player::render(RenderTarget *target){
    target->draw(this->skill);
    target->draw(this->s2);
    target->draw(this->s);
    for(size_t i=0;i<this->bullets.Size();i++)
        this->bullets[i].render(target);
    target->draw(this->right);
    target->draw(this->left);
    target->draw(this->mid);
    

}

string  Player::updateUserInformation(){
    string s= to_string(this->number)+"P                 "+to_string(this->hp)+" / "+to_string(this->maxhp)+"\n\n\n\n\n\nLv. "+to_string(this->level);
    return s;
}

int& Player::getdamage(){
    return this->damage;
}

int& Player::gethp(){
    return this->hp;
}


int& Player::getexp(){
    return this->exp;
}

int& Player::getNextExp(){
    return this->nextexp;
}

int& Player::getlevel(){
    return this->level;
}

void Player::hurt(int Damege){
    this->hp-=Damege;
    this->hurtTime=12;
}

void Player::addHp(int hp){
    this->hp+=hp;
    if(this->hp>this->maxhp)
        this->hp=this->maxhp;
}

void Player::SetSurvive(){
    this->survive=false;
}

void Player::up(){
    this->level++;
}

bool Player::GetSurvive(){
    return this->survive;
}

bool Player::addExp(int Exp){
    this->exp+=Exp;
    if(this->exp >= this->nextexp){
        this->damage++;
        this->maxhp+=5;
        this->hp=this->maxhp;
        this->exp-=this->nextexp;
        this->level++;
        this->nextexp = static_cast<int>((30 / 3) * ((pow(this->level, 3) - 6 * pow(this->level, 2)) + 16 * this->level - 10));
        return true;
    }
    return false;
}

void Player::UpdateShoot(){
    if(this->ShootTime <= 20)
        this->ShootTime++;
}

void Player::UpdateArm(){
    this->s2.setPosition(this->playermid());
     this->right.setPosition(this->playermid());
    this->left.setPosition(this->playermid());
    this->mid.setPosition(this->playermid());
    this->skill.setPosition(this->playermid());
    this->skill.rotate(15.f);
}

Vector2f Player::playermid(){
    return Vector2f(this->GetPlayerPos().x+this->s.getGlobalBounds().width/2,this->GetPlayerPos().y+this->s.getGlobalBounds().height/2);
}

Arr<Bullet>& Player::GetBullet(){
    return this->bullets;
}

FloatRect Player::getplayer(){
    return this->s.getGlobalBounds();
}

const Vector2f& Player::GetPlayerPos(){
    return this->s.getPosition();
}

void Player::restart(){
    this->s.setPosition(200,300);
    this->hurtTime=0;
    this->survive=true;
    this->mode = 0;
    this->level = 1;
    this->exp = 0;
    this->hp = 10;
    this->maxhp = 10;
    this->damage = 1;
    this->nextexp = static_cast<int>((35 / 3) * ((pow(this->level, 3) - 6 * pow(this->level, 2)) + 16 * this->level - 10));
    this->right.setTexture((*this->Right)[4]);
    this->left.setTexture((*this->Left)[4]);
    this->mid.setTexture((*this->Mid)[4]);
    this->skill.setTexture((*this->Skill)[2]);
}

void Player::back(){
    this->s.move(this->dir.x*10.f,this->dir.y*10.f);
}