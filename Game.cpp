#include "Game.h"

//Private


//Constructor Destructor
Game::Game() {
    this->InitWindow();
    Tag::InitCrash();
    Boss::Init();
    this->InitVariable();
    this->InitText();
}

Game::~Game(){
    delete this->window;
}

//Function
void Game::InitWindow(){
    this->window = new RenderWindow(VideoMode(1900,986),"Wingman",Style::Close | Style::Titlebar);
    this->window->setPosition(Vector2i(0,0));
    this->window->setFramerateLimit(60);
}

void Game::InitVariable(){

    this->view.setSize(Vector2f(this->window->getSize()));
    this->view.setCenter(this->view.getSize().x/2,this->view.getSize().y/2);
    this->gg=false;
    this->start=false;
    this->win=false;
    this->people=true;
    this->spawntime=0;
    this->index=0;
    this->y=1;
    this->bossTime=false;
    this->spawntime2=0;
    this->spawntime3=0;
    this->supplytime=0;
    this->keytime=0;
    this->boosIndex=0;
    this->point=0;
    this->Bestpoint=0;
    this->shieldTime=0;
    this->iceTime=0;
    this->expbar.setSize(Vector2f(100.f,10.f));
    this->expbar.setFillColor(Color(61,61,61));

    this->shield.setSize(Vector2f(700.f,25.f));
    this->shield.setFillColor(Color(83,138,0));

    this->ice.setSize(Vector2f(700.f,25.f));
    this->ice.setFillColor(Color(133,194,255));

    this->bossHp.setSize(Vector2f(1000.f,25.f));
    this->bossHp.setFillColor(Color(235,0,0));

    this->Bubble.loadFromFile("texture/player/bubble.png");
    this->bubble.setTexture(this->Bubble);
    this->bubble.setOrigin(this->bubble.getGlobalBounds().width/2,this->bubble.getGlobalBounds().height/2);

    this->textures.push_back(Texture());
    this->textures[0].loadFromFile("texture/player/Ship.png");  //player
    this->textures.push_back(Texture());
    this->textures[1].loadFromFile("texture/Bullet/bullet1.png"); //bullet01
    this->textures.push_back(Texture());
    this->textures[2].loadFromFile("texture/Bullet/bullet2.png");  //bullet02
    this->textures.push_back(Texture());
    this->textures[3].loadFromFile("texture/Bullet/bullet3.png");  //bullet02
    this->textures.push_back(Texture());
    this->textures[4].loadFromFile("texture/arms/gun01.png");  //arm
    this->textures.push_back(Texture());
    this->textures[5].loadFromFile("texture/Enemy/enemy1.png"); //enemy
    this->textures.push_back(Texture());
    this->textures[6].loadFromFile("texture/Enemy/enemy2.png"); //enemy2
    this->textures.push_back(Texture());
    this->textures[7].loadFromFile("texture/Enemy/enemy3.png"); //enemy3
    this->textures.push_back(Texture());
    this->textures[8].loadFromFile("texture/player/hpSupply.png");  //first-add
    this->textures.push_back(Texture());
    this->textures[9].loadFromFile("texture/player/ice.png");  //ice
    this->textures.push_back(Texture());
    this->textures[10].loadFromFile("texture/player/shield.png");  //shield
    this->textures.push_back(Texture());
    this->textures[11].loadFromFile("texture/Enemy/boss.png");  //boss
    this->textures.push_back(Texture());
    this->textures[12].loadFromFile("texture/Enemy/boss2.png");  //boss
    this->textures.push_back(Texture());
    this->textures[13].loadFromFile("texture/Enemy/boss3.png");  //boss

    this->boss.push_back(Boss(&this->textures[11],1000,20));
    this->boss.push_back(Boss(&this->textures[12],1500,25));
    this->boss.push_back(Boss(&this->textures[13],2000,35));
      
    this->Bg.push_back(Texture());
    this->Bg[0].loadFromFile("texture/Bg/bg1.png");
    this->Bg.push_back(Texture());
    this->Bg[1].loadFromFile("texture/Bg/bg2.png");
    this->Bg.push_back(Texture());
    this->Bg[2].loadFromFile("texture/Bg/bg3.png");
    this->Bg.push_back(Texture());
    this->Bg[3].loadFromFile("texture/Bg/bg4.png");

    this->rdFile("texture/Right/rd.txt",this->right);
    this->rdFile("texture/Left/rd.txt",this->left);
    this->rdFile("texture/Mid/rd.txt",this->mid);
    this->rdFile("texture/Skill/rd.txt",this->skill);
}

void Game::InitText(){
    this->f.loadFromFile("fonts/PixellettersFull.ttf");

    this->UserInformation.setFont(this->f);
    this->UserInformation.setCharacterSize(25);
    this->UserInformation.setFillColor(Color::White);
    this->UserInformation.setString("");
    
    this->GameOver.setFont(this->f);
    this->GameOver.setCharacterSize(70);
    this->GameOver.setFillColor(Color::Red);
    this->GameOver.setString("Game Over!");

    this->People.setFont(this->f);
    this->People.setCharacterSize(60);
    this->People.setFillColor(Color(255,88,10));
    this->People.setString("NumPad1 : 1 People Play\nNumPad2 : 2 People Play");

    this->WIN.setFont(this->f);
    this->WIN.setCharacterSize(70);
    this->WIN.setFillColor(Color(250,250,0));
    this->WIN.setString(" You Win !");

    this->EnemyHp.setFont(this->f);
    this->EnemyHp.setCharacterSize(15);
    this->EnemyHp.setFillColor(Color::White);

    this->Point.setFont(this->f);
    this->Point.setCharacterSize(40);
    this->Point.setFillColor(Color(210,210,210,160));
    this->Point.setString(" Point : \n BestPoint : ");
    
    this->Hint.setFont(this->f);
    this->Hint.setCharacterSize(40);
    this->Hint.setFillColor(Color(210,210,210,160));
    this->Hint.setString("User1 : \n A: Left\n D: Right\n W: Up\n S: Down\n Space: Shoot\n P: Pause / Start\n Esc: Quit\n Left-Shift: Change Ship\n");
    this->Hint2.setFont(this->f);

    this->Hint2.setCharacterSize(40);
    this->Hint2.setFillColor(Color(210,210,210,160));
    this->Hint2.setString("User2 : \n Left: Left\n Right: Right\n Up: Up\n Down: Down\n Right-Ctrl: Shoot\n P: Pause / Start\n Esc: Quit\n Right-Shift: Change Ship\n");

    this->board.setFont(this->f);
    this->board.setCharacterSize(60);
    this->board.setFillColor(Color(79,156,156));
}

bool Game::run(){
    return this->window->isOpen();
}

void Game::PollEvent(){
    if(this->window->pollEvent(this->evt)){
        if(evt.type == Event :: Closed)
            this->window->close();
        else if(evt.key.code == Keyboard::Key::Escape)
            this->window->close();
    }
    if(Keyboard::isKeyPressed(Keyboard::Key::P) && this->keytime>=10){
        this->start=!this->start;
        this->keytime=0;
    }
    if(!this->people){
        if(Keyboard::isKeyPressed(Keyboard::Key::R)&& (this->gg || this->win)){
            this->restart();
            for(size_t i=0;i<this->player.Size();i++)
                this->player[i].restart();
        }
    }
    if(Keyboard::isKeyPressed(Keyboard::Key::Numpad1) && this->people){ 
        this->player.clear();
        this->player.add(Player(this->textures,this->right,this->left,this->mid,this->skill));
        this->people=false;
    }
    if(Keyboard::isKeyPressed(Keyboard::Key::Numpad2) && this->people){
        this->player.clear();
        this->player.add(Player(this->textures,this->right,this->left,this->mid,this->skill));
        this->player.add(Player(this->textures,this->right,this->left,this->mid,this->skill,Keyboard::Key::Up,Keyboard::Key::Down,Keyboard::Key::Left,Keyboard::Key::Right,Keyboard::Key::RControl,Keyboard::Key::RShift));
        this->people=false;
    }
}

void Game::update(){
    this->PollEvent();
    if(!this->gg && this->start && !this->win && !this->people){
        this->UpdatePlayrBulletSize();
        this->Spawn();
        this->UpdateEnemy();
        this->UpdateTag();
        this->Min+=0.5;
        if(this->pp%15==0){
            this->aa=rand()%3+(-1);
            this->bb=rand()%3+(-1);
            while(this->aa==0 && this->bb==0){
                this->aa=rand()%3+(-1);
                this->bb=rand()%3+(-1);
            }
        }
        if(this->bossTime){
            if(this->boss[this->index].getPos().top+this->boss[this->index].getPos().height<this->boss[this->index].getPos().height/2 && this->bb==-1)
                this->bb=1;
            if(this->boss[this->index].getPos().top+this->boss[this->index].getPos().height>986 && this->bb==1)
                this->bb=-1;
            if(this->boss[this->index].getPos().left+this->boss[this->index].getPos().width>=1900+this->Min &&this->aa==1)
                this->aa=-1;
            if(this->boss[this->index].getPos().left+this->boss[this->index].getPos().width+this->Min<=(1900+this->Min)/2 &&this->aa==-1)
                this->aa=1;
            this->boss[this->index].move(this->aa,this->bb);
        }
        this->view.move(0.5,0);
    }
    if(this->keytime<=10)    //暫停鍵時間控制
        this->keytime++;
    pp++;
}

void Game::UpdatePlayrBulletSize(){
    for(size_t i=0;i<this->player.Size();i++){
        this->player[i].update(this->Min);
        if(this->player[i].gethp()<1){
            this->board.setString("Score :"+to_string(this->point)+"\nR : Restart");
            this->gg=true;
            this->people=true;
            this->player[i].SetSurvive();
            break;
        }
        if(this->shieldTime<=0){
                for(size_t m=0;m<Enemy::bullet.Size();m++){
                    if(this->player[i].getplayer().intersects(Enemy::bullet[m].GetPos())){
                        this->player[i].hurt(rand()%3+1);
                        Enemy::bullet.erase(m);
                }
            }
        }
        for(size_t l=0;l<this->supply.Size();l++){
            if(this->supply[l].move()==true || this->player[i].getplayer().intersects(this->supply[l].getsupply())){
                if(this->supply[l].getType()==8){
                    for(size_t m=0;m<this->player.Size();m++){
                        this->player[m].addHp(3);
                        this->tags.add(Tag(this->f,"+ 3Hp",Color(255,88,10),Vector2f(this->player[m].GetPlayerPos().x-20,this->player[m].GetPlayerPos().y),Vector2f(-1.f,0.f),35,30,3));
                    }
                }
                else if(this->supply[l].getType()==9){
                    for(size_t m=0;m<this->player.Size();m++)
                        this->tags.add(Tag(this->f,"Freeze Nice !",Color(167,255,36),Vector2f(this->player[m].GetPlayerPos().x+20,this->player[m].GetPlayerPos().y),Vector2f(1.f,0.f),35,30,3));
                    this->iceTime=50;
                }
                else{
                     for(size_t m=0;m<this->player.Size();m++)
                        this->tags.add(Tag(this->f,"Shield Nice !",Color(167,255,36),Vector2f(this->player[m].GetPlayerPos().x+20,this->player[m].GetPlayerPos().y),Vector2f(1.f,0.f),35,30,3));
                    this->shieldTime=50;
                }
                this->supply.erase(l);
            }
        }
        for(size_t j=0;j<this->player[i].GetBullet().Size();j++){
            if(this->player[i].GetBullet()[j].GetPos().left >this->window->getSize().x+Min){
                this->player[i].GetBullet().erase(j);
                continue;
            }
            for(size_t k=0;k<this->enemies.Size();k++){
                if(this->enemies[k].getpos().intersects(this->player[i].GetBullet()[j].GetPos())){
                    this->player[i].GetBullet().erase(j);
                    this->enemies[k].hurt(this->player[i].getdamage());
                    this->tags.add(Tag(this->f,"- "+to_string(this->player[i].getdamage()),Color::Red,this->enemies[k].Getpos(),Vector2f(0,-1.f),35,20,2));
                    for(size_t m=0;m<rand()%8+3;m++){
                        this->crash.add(Tag(this->enemies[k].Getpos(),Vector2f(1.f,0.f),rand()%20+10,rand()%20,3.f));
                    }
                    if(this->enemies[k].gethp_hpmax().x<=0){
                        this->point+=this->enemies[k].getExp();
                        this->Point.setString(" Point : "+to_string(this->point)+"\n BestPoint : ");
                        this->tags.add(Tag(this->f,"+ "+to_string(this->enemies[k].getExp()),Color::White,Vector2f(60.f,0.f),Vector2f(1,0),30,20,5));
                        this->tags.add(Tag(this->f,"+ "+to_string(this->enemies[k].getExp())+" EXP",Color(0,173,173),Vector2f(this->player[i].GetPlayerPos().x,this->player[i].GetPlayerPos().y-50),Vector2f(0.f,-1.f),35,35,3));
                        if(this->player[i].addExp(this->enemies[k].getExp()))
                            this->tags.add(Tag(this->f,"Level Up!",Color(1,152,89),Vector2f(this->player[i].GetPlayerPos().x+60,this->player[i].GetPlayerPos().y),Vector2f(1.f,0),35,40,5));
                        this->enemies.erase(k);
                    }
                    break;
                }
            }
        }
    }
    for(size_t i=0;i<this->crash.Size();i++){
        this->crash[i].Move();
        if(this->crash[i].getDuration()<=0)
            this->crash.erase(i);
    }
    for(size_t i=0;i<this->player.Size();i++)
        if(this->player[i].getlevel()%8==0)
            this->bossTime=true;
    if(this->bossTime){
        for(size_t i=0;i<this->player.Size();i++){
            for(size_t j=0;j<this->player[i].GetBullet().Size();j++){
                if(this->boss[this->index].getPos().intersects(this->player[i].GetBullet()[j].GetPos())){
                    this->boss[this->index].hurt(this->player[i].getdamage());
                    this->bossHp.setScale(float(this->boss[this->index].getHp())/this->boss[this->index].getMaxHp(),1);
                    this->crash.add(Tag( this->boss[this->index].Getpos(),Vector2f(1.f,0.f),rand()%20+10,rand()%20,3.f));
                      this->tags.add(Tag(this->f,"- "+to_string(this->player[i].getdamage()),Color::Red,this->boss[0].Getpos(),Vector2f(0,-1.f),35,20,2));
                    this->player[i].GetBullet().erase(j);
                }
            }
            for(size_t j=0;j<Boss::bullet.Size();j++){
                Boss::bullet[j].Move();
                if(this->player[i].getplayer().intersects(Boss::bullet[j].GetPos())){
                     this->tags.add(Tag(this->f,"- "+to_string(this->boss[this->index].getdamage()),Color::Red,this->player[i].GetPlayerPos(),Vector2f(0,-1.f),40,20,3));
                     this->player[i].hurt(this->boss[this->index].getdamage());
                     Boss::bullet.erase(j);
                }
            }
            if(this->player[i].getplayer().intersects(this->boss[this->index].getPos())){
                this->player[i].hurt(2);
            }
        }
        if(this->boss[this->index].getHp()<=0){
            for(size_t i=0;i<this->player.Size();i++){
                this->player[i].up();
            }
            this->index++;
            if(this->index<this->boss.size()){
                this->bossHp.setScale(float(this->boss[this->index].getHp())/this->boss[this->index].getMaxHp(),1);
                this->y=1;
                this->bossTime=false;
                Boss::bullet.clear();
                this->boss[this->index].set(Vector2f(this->window->getSize().x+this->Min-300,500));
            }
            else{
                this->win=true;
                this->bossTime=false;
                this->people=true;
                return;
            }
        }
    }
}

void Game::UpdateEnemy(){
    for(size_t i=0;i<this->enemies.Size()&&!this->gg;i++){
        if(this->iceTime==0)
            this->enemies[i].Move(this->player[this->enemies[i].getPlayerNB()].GetPlayerPos(),this->enemies[i].getEnemyType());
        for(size_t k=0;k<Enemy::bullet.Size();k++){
            Enemy::bullet[k].Move();
            if(Enemy::bullet[k].GetPos().left<this->Min-Enemy::bullet[k].GetPos().width ||Enemy::bullet[k].GetPos().left> this->window->getSize().x+Enemy::bullet[k].GetPos().width+this->Min || Enemy::bullet[k].GetPos().height>this->window->getSize().y+Enemy::bullet[k].GetPos().height){
                Enemy::bullet.erase(k);
            }
        }
        if(this->enemies[i].getpos().left < this->Min-this->enemies[i].getpos().width || this->enemies[i].getpos().top < 0- 0-this->enemies[i].getpos().height || this->enemies[i].getpos().top >this->window->getSize().y+this->enemies[i].getpos().height){
            this->enemies.erase(i);
            continue;
        }
        for(size_t j=0;j<this->player.Size();j++){
            if(this->enemies[i].getpos().intersects(this->player[j].getplayer()) &&this->shieldTime==0){
                this->player[j].hurt(this->enemies[i].getdamage());
                this->tags.add(Tag(this->f,"- "+to_string(this->enemies[i].getdamage()),Color::Red,this->player[j].GetPlayerPos(),Vector2f(0,-1.f),40,20,3));
                this->enemies.erase(i);
                break;
            }
        }         
    }
}

void Game::UpdateTag(){
    for(size_t i=0;i<this->tags.Size();i++){
        this->tags[i].update();
        if(this->tags[i].getDuration() <=0)
            this->tags.erase(i);
    }
}

void Game::UpdateText_expbar(int num){
        this->UserInformation.setPosition(this->player[num].GetPlayerPos().x-30,this->player[num].GetPlayerPos().y-50.f);
        this->UserInformation.setString(this->player[num].updateUserInformation());
        this->expbar.setPosition(this->player[num].GetPlayerPos().x+30,this->player[num].GetPlayerPos().y+90);
        this->expbar.setScale(static_cast<float>(this->player[num].getexp())/this->player[num].getNextExp(),1.f);
}


void Game::render() {
    this->window->clear();
    this->window->setView(this->view);
    this->bossHp.setPosition(450.f+Min,90);
    for(size_t i=0;i<this->Bg.size();i++){
        Sprite temp;
        temp.setTexture(this->Bg[i]);
        temp.setScale(7.f,2.8f);
        temp.setPosition(temp.getGlobalBounds().width*i,temp.getPosition().y);
        this->window->draw(temp);
    }
    if(this->bossTime ){
        this->window->draw(this->bossHp);
        this->boss[this->index].render(this->window);
    }
    if(this->shieldTime>0){
        this->shield.setPosition(500.f+Min,20.f);
        this->window->draw(this->shield);
        this->shield.setScale(this->shieldTime/50.f,1.f);
        if(this->start)
            this->shieldTime-=0.25f;
        for(size_t i=0;i<this->player.Size();i++){
            if(this->player[i].GetSurvive()){
                this->bubble.setPosition(this->player[i].playermid());
                this->window->draw(this->bubble);
            }
        }
    }
    if(this->iceTime>0){
        this->ice.setPosition(500.f+Min,60.f);
        this->window->draw(this->ice);
        this->ice.setScale(this->iceTime/50.f,1.f);
        if(this->start)
            this->iceTime-=0.25;
    } 
    for (size_t i=0; i < this->player.Size(); i++){
        if(this->player[i].GetSurvive()){
            this->player[i].render(this->window);
            this->UpdateText_expbar(i);
            this->window->draw(this->UserInformation);
            this->window->draw(this->expbar);
        }
    }
    for (size_t i=0; i < this->enemies.Size(); i++) {
        this->EnemyHp.setString(to_string(this->enemies[i].gethp_hpmax().x) + " / " + to_string(this->enemies[i].gethp_hpmax().y));
        this->EnemyHp.setPosition(this->enemies[i].getpos().left, this->enemies[i].getpos().top);
        this->enemies[i].render(this->window);
        this->window->draw(this->EnemyHp);
    }
    for(size_t i=0;i<this->crash.Size();i++)
        this->crash[i].render2(this->window);
    for(size_t i=0; i < this->tags.Size();i++){
        this->tags[i].render(this->window);
    }
    for(size_t i=0;i<this->supply.Size();i++){
        this->supply[i].render(this->window);
    }
    if (this->gg){
        this->GameOver.setPosition(this->window->getSize().x/2-this->GameOver.getGlobalBounds().width/2+Min,this->window->getSize().y/2-this->GameOver.getGlobalBounds().height/2);
        this->board.setPosition(this->window->getSize().x/2-this->GameOver.getGlobalBounds().width/2+Min,this->window->getSize().y/2-this->GameOver.getGlobalBounds().height/2+60);
        this->People.setPosition(650+this->Min,200);
        this->window->draw(this->People); 
        this->window->draw(this->GameOver);
        this->window->draw(this->board);
    }
    if(this->win){
        this->WIN.setPosition(this->window->getSize().x/2-this->WIN.getGlobalBounds().width/2+Min,this->window->getSize().y/2-this->WIN.getGlobalBounds().height/2);
        this->board.setPosition(this->window->getSize().x/2-this->WIN.getGlobalBounds().width/2+Min,this->window->getSize().y/2-this->WIN.getGlobalBounds().height/2+60);
        this->People.setPosition(650+this->Min,200);
        this->window->draw(this->People); 
        this->window->draw(this->WIN);
        this->window->draw(this->board);
    }
    if(this->start==false){
        if(this->player.Size()==2){
            this->Hint.setPosition(50.f+Min, 400.f);
            this->Hint2.setPosition(500.f+Min, 400.f);
            this->window->draw(this->Hint);
            this->window->draw(this->Hint2);
        }
        else if(this->player.Size()==1){
            this->Hint.setPosition(50.f+Min, 400.f);
            this->window->draw(this->Hint);
        }
        this->People.setPosition(650+this->Min,200);
        this->window->draw(this->People); 
    }
    this->Point.setPosition(this->Min,10);
    this->window->draw(this->Point);
    this->window->display();
}

void Game::Spawn(){
    if(this->iceTime<=0 && this->bossTime==false){
        if(this->spawntime < 15.f)
            this->spawntime+=0.25f;
        else{
            this->spawntime=0;
            this->enemies.add(Enemy(&this->textures[5],&this->textures[3],this->window->getSize(),5,rand()%this->player.Size(),this->player[rand()%this->player.Size()].getlevel(),this->Min));
        }
        if(this->spawntime2 < 20.f)
            this->spawntime2+=0.25f;
        else{
            this->spawntime2=0;
            this->enemies.add(Enemy(&this->textures[6],&this->textures[3],this->window->getSize(),6,rand()%this->player.Size(),this->player[rand()%this->player.Size()].getlevel(),this->Min));
        }
        if(this->spawntime3 < 40.f)
            this->spawntime3+=0.25f;
        else{
            int y=rand()%3+8;
            this->spawntime3=0;
            this->enemies.add(Enemy(&this->textures[7],&this->textures[3],this->window->getSize(),7,rand()%this->player.Size(),this->player[rand()%this->player.Size()].getlevel(),this->Min));
            this->supply.add(Supply(& this->textures[y],Vector2f(rand()%(this->window->getSize().x/2)+100+this->Min,rand()%(this->window->getSize().y/2)+100),60.f,y));
        }
    }
}

void Game::rdFile(string s,Arr<Texture>& t){
    ifstream in;
    in.open(s);
    string name;
    if(in.is_open()){
        while(getline(in,name)){
            Texture temp;
            temp.loadFromFile(name);
            t.add(temp);
        }
    }
}

void Game::restart(){
    this->gg=false;
    this->win=false;
    this->bossTime=false;
    if(this->point>this->Bestpoint)
        this->Bestpoint=this->point;
    this->point=0;
    this->Point.setString(" Point : \n BestPoint : "+to_string(this->Bestpoint));
    this->boosIndex=0;
    this->Min=0;
    this->index=0;
    this->view.setCenter(this->view.getSize().x/2,this->view.getSize().y/2);
    this->tags.clear();
    this->enemies.clear();
    this->supply.clear();
    for(size_t i=0;i<this->boss.size();i++)
        this->boss[i].restart();
}