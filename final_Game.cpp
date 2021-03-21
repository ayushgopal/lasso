#include <simplecpp>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>

using namespace simplecpp;

//movingObject.h
#ifndef _MOVINGOBJECT_INCLUDED_
#define _MOVINGOBJECT_INCLUDED_

#include <simplecpp>
#include <vector>
#include <composite.h>
#include <sprite.h>


using namespace simplecpp;







class MovingObject : public Sprite {
  vector<Sprite*> parts;
  double vx, vy;
  double ax, ay;
  bool paused;
  void initMO(double argvx, double argvy, double argax, double argay, bool argpaused=true) {
    vx=argvx; vy=argvy; ax=argax; ay=argay; paused=argpaused;
  }
 public:
 MovingObject(double argvx, double argvy, double argax, double argay, bool argpaused=true)
    : Sprite() {
    initMO(argvx, argvy, argax, argay, argpaused);
  }
 MovingObject(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : Sprite() {
   double angle_rad = angle_deg*PI/180.0;
   double argvx = speed*cos(angle_rad);
   double argvy = -speed*sin(angle_rad);
   initMO(argvx, argvy, argax, argay, argpaused);
  }
  void set_vx(double argvx) { vx = argvx; }
  void set_vy(double argvy) { vy = argvy; }
  void set_ax(double argax) { ax = argax; }
  void set_ay(double argay) { ay = argay; }
  double getXPos();
  double getYPos();
  void reset_all(double argx, double argy, double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta);

  void pause() { paused = true; }
  void unpause() { paused = false; }
  bool isPaused() { return paused; }

  void addPart(Sprite* p) {
    parts.push_back(p);
  }
  void nextStep(double t);
  void getAttachedTo(MovingObject *m);
};

#endif

//MovingObject.cpp

void MovingObject::nextStep(double t) {
  if(paused) { return; }
  //cerr << "x=" << getXPos() << ",y=" << getYPos() << endl;
  //cerr << "vx=" << vx << ",vy=" << vy << endl;
  //cerr << "ax=" << ax << ",ay=" << ay << endl;

  for(size_t i=0; i<parts.size(); i++){
    parts[i]->move(vx*t, vy*t);
  }
  vx += ax*t;
  vy += ay*t;
} // End MovingObject::nextStep()

double MovingObject::getXPos() {
  return (parts.size() > 0) ? parts[0]->getX() : -1;
}

double MovingObject::getYPos() {
  return (parts.size() > 0) ? parts[0]->getY() : -1;
}

void MovingObject::reset_all(double argx, double argy, double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) {
  for(size_t i=0; i<parts.size(); i++){
    parts[i]->moveTo(argx, argy);
  }
  double angle_rad = angle_deg*PI/180.0;
  double argvx = speed*cos(angle_rad);
  double argvy = -speed*sin(angle_rad);
  vx = argvx; vy = argvy; ax = argax; ay = argay; paused = argpaused;
} // End MovingObject::reset_all()

void MovingObject::getAttachedTo(MovingObject *m) {
  double xpos = m->getXPos();
  double ypos = m->getYPos();
  for(size_t i=0; i<parts.size(); i++){
    parts[i]->moveTo(xpos, ypos);
  }
  initMO(m->vx, m->vy, m->ax, m->ay, m->paused);
}

//coin.h




#ifndef __COIN_H__
#define __COIN_H__


class Coin : public MovingObject {
  double coin_start_x;
  double coin_start_y;
  double release_speed;
  double release_angle_deg;
  double coin_ax;
  double coin_ay;

  // Moving parts
  Circle coin_circle;

 public:
 Coin(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta) {
    release_speed = speed;
    release_angle_deg = angle_deg;
    coin_ax = argax;
    coin_ay = argay;
    initCoin();
  }

  void initCoin();
  void resetCoin();

}; // End class Coin
#endif

// START OF CLASS TOIN
#ifndef __TOIN_H__
#define __TOIN_H__
class Toin : public MovingObject {
  double toin_start_x;
  double toin_start_y;
  double release_speed;
  double release_angle_deg;
  double toin_ax;
  double toin_ay;

  // Moving parts
  Circle toin_circle;

 public:
 Toin(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta) {
    release_speed = speed;
    release_angle_deg = angle_deg;
    toin_ax = argax;
    toin_ay = argay;
    initToin();
  }

  void initToin();
  void resetToin();

}; // End class toin
#endif

//START OF CLASS LOIN
#ifndef __LOIN_H__
#define __LOIN_H__


class Loin : public MovingObject {
  double loin_start_x;
  double loin_start_y;
  double release_speed;
  double release_angle_deg;
  double loin_ax;
  double loin_ay;

  // Moving parts
  Circle loin_circle;

 public:
 Loin(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta) {
    release_speed = speed;
    release_angle_deg = angle_deg;
    loin_ax = argax;
    loin_ay = argay;
    initLoin();
  }

  void initLoin();
  void resetLoin();

};


#endif
//END OF CLASS LOIN

//lasso.h
#ifndef __LASSO_H__
#define __LASSO_H__

//#define WINDOW_X 1200
//#define WINDOW_Y 960
#define WINDOW_X 800
#define WINDOW_Y 600

#define STEP_TIME 0.05

#define PLAY_X_START 100
#define PLAY_Y_START 0
#define PLAY_X_WIDTH (WINDOW_X-PLAY_X_START)
#define PLAY_Y_HEIGHT (WINDOW_Y-100)

#define LASSO_X_OFFSET 100
#define LASSO_Y_HEIGHT 100
#define LASSO_BAND_LENGTH LASSO_X_OFFSET
#define LASSO_THICKNESS 5

#define COIN_GAP 1
#define TOIN_GAP 1
#define LOIN_GAP 1

#define RELEASE_ANGLE_STEP_DEG 5
#define MIN_RELEASE_ANGLE_DEG 0
#define MAX_RELEASE_ANGLE_DEG (360-RELEASE_ANGLE_STEP_DEG)
#define INIT_RELEASE_ANGLE_DEG 45

#define RELEASE_SPEED_STEP 20
#define MIN_RELEASE_SPEED 0
#define MAX_RELEASE_SPEED 200
#define INIT_RELEASE_SPEED 100

#define COIN_SPEED 120
#define COIN_ANGLE_DEG 90
#define TOIN_SPEED 150
#define TOIN_ANGLE_DEG 90
#define LOIN_SPEED 120
#define LOIN_ANGLE_DEG 90

#define LASSO_G 30
#define COIN_G 30
#define TOIN_G 30
#define LOIN_G 30

#define LASSO_SIZE 10
#define LASSO_RADIUS 50
#define COIN_SIZE 7   //SIZE OF DIFFERENT COINS DOWN
#define TOIN_SIZE 5
#define LOIN_SIZE 3

class Lasso : public MovingObject {
  double lasso_start_x;
  double lasso_start_y;
  double release_speed;
  double release_angle_deg;
  double lasso_ax;
  double lasso_ay;

  // Moving parts
  Circle lasso_circle;
  Circle lasso_loop;

  // Non-moving parts
  Line lasso_line;
  Line lasso_band;

  // State info
  bool lasso_looped;
  Coin *the_coin;
  Toin *the_toin;
  Loin *the_loin; //CREATING COIN POINTERS FOR DIFFERENT COINS
  int num_coins;

  void initLasso();
 public:
 Lasso(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta) {
    release_speed = speed;
    release_angle_deg = angle_deg;
    lasso_ax = argax;
    lasso_ay = argay;
    initLasso();
  }

  void draw_lasso_band();
  void yank();
  void loopit();
  void addAngle(double angle_deg);
  void addSpeed(double speed);

  void nextStep(double t);
  void check_for_coin(Coin *coin);
    void check_for_toin(Toin *toin);
       void check_for_loin(Loin *loin);
  int getNumCoins() { return num_coins; }

}; // End class Lasso

#endif

//coin.h

void Coin::initCoin() {
  coin_start_x = (PLAY_X_START+WINDOW_X)/2;
  coin_start_y = PLAY_Y_HEIGHT;
  coin_circle.reset(coin_start_x, coin_start_y, COIN_SIZE);
  coin_circle.setColor(COLOR("green"));
  coin_circle.setFill(true);
  addPart(&coin_circle);
}

void Coin::resetCoin() {
  double coin_speed = COIN_SPEED;
  double coin_angle_deg = COIN_ANGLE_DEG;
  coin_ax = 0;
  coin_ay = COIN_G;
  bool paused = true, rtheta = true;
  reset_all(coin_start_x, coin_start_y, coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
}

//toin.h

void Toin::initToin() {
  toin_start_x = (PLAY_X_START+WINDOW_X)/2-50;
  toin_start_y = PLAY_Y_HEIGHT;
  toin_circle.reset(toin_start_x, toin_start_y, TOIN_SIZE);
  toin_circle.setColor(COLOR("blue"));
  toin_circle.setFill(true);
  addPart(&toin_circle);
}

void Toin::resetToin() {
  double toin_speed = TOIN_SPEED;
  double toin_angle_deg = TOIN_ANGLE_DEG;
  toin_ax = 5;
  toin_ay = TOIN_G;
  bool paused = true, rtheta = true;
  reset_all(toin_start_x, toin_start_y, toin_speed, toin_angle_deg, toin_ax, toin_ay, paused, rtheta);
}
//loin.h
void Loin::initLoin() {
  loin_start_x = (PLAY_X_START+WINDOW_X)/2-30;
  loin_start_y = PLAY_Y_HEIGHT;
  loin_circle.reset(loin_start_x, loin_start_y, LOIN_SIZE);
  loin_circle.setColor(COLOR("black"));
  loin_circle.setFill(true);
  addPart(&loin_circle);
}

void Loin::resetLoin() {
  double loin_speed = LOIN_SPEED;
  double loin_angle_deg = LOIN_ANGLE_DEG;
  loin_ax =7;
  loin_ay = LOIN_G;
  bool paused = true, rtheta = true;
  reset_all(loin_start_x, loin_start_y, loin_speed, loin_angle_deg, loin_ax, loin_ay, paused, rtheta);
}

//lasso.cpp

void Lasso::draw_lasso_band() {
  double len = (release_speed/MAX_RELEASE_SPEED)*LASSO_BAND_LENGTH;
  double arad = release_angle_deg*PI/180.0;
  double xlen = len*cos(arad);
  double ylen = len*sin(arad);
  lasso_band.reset(lasso_start_x, lasso_start_y, (lasso_start_x-xlen), (lasso_start_y+ylen));
  lasso_band.setThickness(LASSO_THICKNESS);
} // End Lasso::draw_lasso_band()

void Lasso::initLasso() {
  lasso_start_x = (PLAY_X_START+LASSO_X_OFFSET);
  lasso_start_y = (PLAY_Y_HEIGHT-LASSO_Y_HEIGHT);
  lasso_circle.reset(lasso_start_x, lasso_start_y, LASSO_SIZE);
  lasso_circle.setColor(COLOR("red"));
  lasso_circle.setFill(true);
  lasso_loop.reset(lasso_start_x, lasso_start_y, LASSO_SIZE/2);
  lasso_loop.setColor(COLOR("brown"));
  lasso_loop.setFill(true);
  addPart(&lasso_circle);
  addPart(&lasso_loop);
  lasso_looped = false;
  the_coin = NULL;
  the_toin = NULL;
  the_loin = NULL;
  num_coins = 0;

  lasso_line.reset(lasso_start_x, lasso_start_y, lasso_start_x, lasso_start_y);
  lasso_line.setColor(COLOR("yellow"));

  lasso_band.setColor(COLOR("grey"));
  draw_lasso_band();

} // End Lasso::initLasso()

void Lasso::yank() {
  bool paused = true, rtheta = true;
  reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
  lasso_loop.reset(lasso_start_x, lasso_start_y, LASSO_SIZE/2);
  lasso_loop.setFill(true);
  lasso_looped = false;


  if(the_toin != NULL && the_coin != NULL && the_loin != NULL )

{
num_coins++;
    the_coin->resetCoin();
    the_coin=NULL;
    num_coins++;
    num_coins++;
    num_coins++;
    num_coins--;
    num_coins--;
    the_toin->resetToin();
    the_toin=NULL;
    the_loin->resetLoin();
    the_loin=NULL;




}
else if(the_toin != NULL && the_coin != NULL  )  //if only coin1 and coin2 is selected

{
num_coins++;
    the_coin->resetCoin();
    the_coin=NULL;
    num_coins++;
    num_coins++;
    num_coins++;

    the_toin->resetToin();
    the_toin=NULL;





}

else if( the_coin != NULL && the_loin != NULL )  //if only coin1 and bomb selected

{
num_coins++;
    the_coin->resetCoin();
    the_coin=NULL;

    num_coins--;
    num_coins--;

    the_loin->resetLoin();
    the_loin=NULL;




}
else if(the_toin != NULL  && the_loin != NULL )  //if only bomb and coin2 selected

{


    num_coins++;
    num_coins++;
    num_coins++;
    num_coins--;
    num_coins--;
    the_toin->resetToin();
    the_toin=NULL;
    the_loin->resetLoin();
    the_loin=NULL;




}












  else if(the_coin != NULL) {
    num_coins++;
    the_coin->resetCoin();
    the_coin=NULL;
  }
  else if(the_toin != NULL) {
    num_coins++;
    num_coins++;
    num_coins++;
    the_toin->resetToin();
    the_toin=NULL;
  }
  else if(the_loin != NULL) {
    num_coins--;
    num_coins--;

    the_loin->resetLoin();
    the_loin=NULL;
  }




} // End Lasso::yank()

void Lasso::loopit() {
  if(lasso_looped) { return; } // Already looped
  lasso_loop.reset(getXPos(), getYPos(), LASSO_RADIUS);
  lasso_loop.setFill(false);
  lasso_looped = true;
} // End Lasso::loopit()

void Lasso::addAngle(double angle_deg) {
  release_angle_deg += angle_deg;
  if(release_angle_deg < MIN_RELEASE_ANGLE_DEG) { release_angle_deg = MIN_RELEASE_ANGLE_DEG; }
  if(release_angle_deg > MAX_RELEASE_ANGLE_DEG) { release_angle_deg = MAX_RELEASE_ANGLE_DEG; }
  bool paused = true, rtheta = true;
  reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
} // End Lasso::addAngle()

void Lasso::addSpeed(double speed) {
  release_speed += speed;
  if(release_speed < MIN_RELEASE_SPEED) { release_speed = MIN_RELEASE_SPEED; }
  if(release_speed > MAX_RELEASE_SPEED) { release_speed = MAX_RELEASE_SPEED; }
  bool paused = true, rtheta = true;
  reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
} // End Lasso::addSpeed()

void Lasso::nextStep(double stepTime) {
  draw_lasso_band();
  MovingObject::nextStep(stepTime);
  if(getYPos() > PLAY_Y_HEIGHT) { yank(); }
  lasso_line.reset(lasso_start_x, lasso_start_y, getXPos(), getYPos());
} // End Lasso::nextStep()

void Lasso::check_for_coin(Coin *coinPtr) {
  double lasso_x = getXPos();
  double lasso_y = getYPos();
  double coin_x = coinPtr->getXPos();
  double coin_y = coinPtr->getYPos();
  double xdiff = (lasso_x - coin_x);
  double ydiff = (lasso_y - coin_y);
  double distance = sqrt((xdiff*xdiff)+(ydiff*ydiff));
  if(distance <= LASSO_RADIUS) {
    the_coin = coinPtr;
    the_coin->getAttachedTo(this);
  }
} // End Lasso::check_for_coin()



void Lasso::check_for_toin(Toin *toinPtr) {
  double lasso_x = getXPos();
  double lasso_y = getYPos();
  double toin_x = toinPtr->getXPos();
  double toin_y = toinPtr->getYPos();
  double xdiff = (lasso_x - toin_x);
  double ydiff = (lasso_y - toin_y);
  double distance = sqrt((xdiff*xdiff)+(ydiff*ydiff));
  if(distance <= LASSO_RADIUS) {
    the_toin = toinPtr;
    the_toin->getAttachedTo(this);
  }
}

void Lasso::check_for_loin(Loin *loinPtr) {
  double lasso_x = getXPos();
  double lasso_y = getYPos();
  double loin_x = loinPtr->getXPos();
  double loin_y = loinPtr->getYPos();
  double xdiff = (lasso_x - loin_x);
  double ydiff = (lasso_y - loin_y);
  double distance = sqrt((xdiff*xdiff)+(ydiff*ydiff));
  if(distance <= LASSO_RADIUS) {
    the_loin = loinPtr;
    the_loin->getAttachedTo(this);
  }
}

 // End Lasso::check_for_coin()


main_program {

ofstream myfile;

string pass="lets_play"; //default password

   int cuser_nm; //check username
   string cpass;//check password
   cout<<"Enter your LDAP ID:";
   cin>>cuser_nm;
   cout<<"Enter the correct password:";
   cin>>cpass;
   if(200000000<= cuser_nm && cuser_nm<=300000000 && cpass==pass)  //you enter the competiton if you type your correct ldap_id and password= "lets play"
   {
     cout<<"WELCOME TO IITB LASSO COMPETITION"<<endl;
     cout<<"ALL THE BEST FOR THE GAME THIS IS YOUR FIRST AND LAST CHANCE"<<endl;

     myfile.open("scorecheck.txt",fstream::app);  //this open the file given you can modify this file and test it on your file.
     string a="";

     cout<<"ENTER YOUR NAME:";
     cin>>a;
     myfile<<"NAME OF THE PLAYER:";
     myfile<<a<<"\n";
  }
  else {cout<<"YOUR PASSWORD IS WRONG BUT YOU CAN STILL PRACTICE"<<endl;}  //if you enter wrong password you enter the practice mode
                                                                           //in practice mode you can play unlimited the game will not record your data

  cout<<"enter the level you want to play in (1/2/3/4)";//choose the correct level
  int a=0;
  cin>>a;
  myfile<<"LEVEL OF THE PLAYER:";
   myfile<<a<<"\n";
  if(a==1){

   initCanvas("Lasso", WINDOW_X, WINDOW_Y);
  int stepCount = 0;
  float stepTime = STEP_TIME;
  float runTime = -1; // sec; -ve means infinite
  float currTime = 0;

  // Draw lasso at start position
  double release_speed = INIT_RELEASE_SPEED; // m/s
  double release_angle_deg = INIT_RELEASE_ANGLE_DEG; // degrees
  double lasso_ax = 0;
  double lasso_ay = LASSO_G;
  bool paused = true;
  bool rtheta = true;
  Lasso lasso(release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);

  Line b1(0, PLAY_Y_HEIGHT, WINDOW_X, PLAY_Y_HEIGHT);
  b1.setColor(COLOR("blue"));
  Line b2(PLAY_X_START, 0, PLAY_X_START, WINDOW_Y);
  b2.setColor(COLOR("blue"));

  string msg("Cmd: _");
  Text charPressed(PLAY_X_START+50, PLAY_Y_HEIGHT+20, msg);
  char coinScoreStr[256];
  sprintf(coinScoreStr, "Coins: %d", lasso.getNumCoins());
  Text coinScore(PLAY_X_START+50, PLAY_Y_HEIGHT+50, coinScoreStr);

  paused = true; rtheta = true;
  double coin_speed = COIN_SPEED;
  double coin_angle_deg = COIN_ANGLE_DEG;
  double coin_ax = 0;
  double coin_ay = COIN_G;
  Coin coin(coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);

  // After every COIN_GAP sec, make the coin jump
  double last_coin_jump_end = 0;

  // When t is pressed, throw lasso
  // If lasso within range, make coin stick
  // When y is pressed, yank lasso
  // When l is pressed, loop lasso
  // When q is pressed, quit

  for(;;) {
    if((runTime > 0) && (currTime > runTime)) { break; }

    XEvent e;
    bool pendingEv = checkEvent(e);
    if(pendingEv) {
      char c = charFromEvent(e);
      msg[msg.length()-1] = c;
      charPressed.setMessage(msg);
      switch(c) {
      case 't':
	lasso.unpause();
	break;
      case 'y':
	lasso.yank();
	break;
      case 'l':
	lasso.loopit();
	lasso.check_for_coin(&coin);
	wait(STEP_TIME*5);
	break;
      case '[':
	if(lasso.isPaused()) { lasso.addAngle(-RELEASE_ANGLE_STEP_DEG);	}
	break;
      case ']':
	if(lasso.isPaused()) { lasso.addAngle(+RELEASE_ANGLE_STEP_DEG); }
	break;
      case '-':
	if(lasso.isPaused()) { lasso.addSpeed(-RELEASE_SPEED_STEP); }
	break;
      case '=':
	if(lasso.isPaused()) { lasso.addSpeed(+RELEASE_SPEED_STEP); }
	break;
      case 'q':
	exit(0);
      default:
	break;
      }
    }

    lasso.nextStep(stepTime);

    coin.nextStep(stepTime);
    if(coin.isPaused()) {
      if((currTime-last_coin_jump_end) >= COIN_GAP) {
	coin.unpause();
      }
    }

    if(coin.getYPos() > PLAY_Y_HEIGHT) {
      coin.resetCoin();
      last_coin_jump_end = currTime;
    }

    sprintf(coinScoreStr, "Coins: %d", lasso.getNumCoins());
    coinScore.setMessage(coinScoreStr);

    stepCount++;
    currTime += stepTime;
    wait(stepTime);
  } // End for(;;)
cout<<"final time is"<<currTime;
  wait(3);
} // End main_program
else if(a==2){




initCanvas("LASSO", WINDOW_X, WINDOW_Y);
   int stepCount = 0;
   float stepTime = STEP_TIME;
   float runTime = -1; // sec; -ve means infinite
   float currTime = 0;

   // Draw lasso at start position
   double release_speed = INIT_RELEASE_SPEED; // m/s
   double release_angle_deg = INIT_RELEASE_ANGLE_DEG; // degrees
   double lasso_ax = 0;
   double lasso_ay = LASSO_G;
   bool paused = true;
   bool rtheta = true;
   Lasso lasso(release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);

   Line b1(0, PLAY_Y_HEIGHT, WINDOW_X, PLAY_Y_HEIGHT);
   b1.setColor(COLOR("blue"));
   Line b2(PLAY_X_START, 0, PLAY_X_START, WINDOW_Y);
   b2.setColor(COLOR("green"));

   string msg("Cmd: _");
   Text charPressed(PLAY_X_START+50, PLAY_Y_HEIGHT+20, msg);
   char coinScoreStr[256];
   sprintf(coinScoreStr, "Coins: %d", lasso.getNumCoins());
   Text coinScore(PLAY_X_START+50, PLAY_Y_HEIGHT+50, coinScoreStr);

   paused = true; rtheta = true;
   double coin_speed = COIN_SPEED;
   double coin_angle_deg =0 ;
   double coin_ax = 0;
   double coin_ay = COIN_G;
   Coin coin(coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);

   double toin_speed = COIN_SPEED;
   double toin_angle_deg =0 ;
   double toin_ax = 0;
   double toin_ay = COIN_G;
   Toin toin(toin_speed, toin_angle_deg, toin_ax, toin_ay, paused, rtheta);




   // After every COIN_GAP sec, make the coin jump
   double last_coin_jump_end = 0;
   double last_toin_jump_end = 0;

   // When t is pressed, throw lasso
   // If lasso within range, make coin stick
   // When y is pressed, yank lasso
   // When l is pressed, loop lasso
   // When q is pressed, quit

   for(;;) {
    if((runTime > 0) && (currTime > runTime)) { break; }


    XEvent e;
    bool pendingEv = checkEvent(e);
    if(pendingEv) {
      char c = charFromEvent(e);
      msg[msg.length()-1] = c;
      charPressed.setMessage(msg);
      switch(c) {
      case 't':
	lasso.unpause();
	break;
      case 'y':
	lasso.yank();
	break;
      case 'l':
	lasso.loopit();
	lasso.check_for_coin(&coin);
	lasso.check_for_toin(&toin);
	wait(STEP_TIME*5);
	break;
      case '[':
	if(lasso.isPaused()) { lasso.addAngle(-RELEASE_ANGLE_STEP_DEG);	}
	break;
      case ']':
	if(lasso.isPaused()) { lasso.addAngle(+RELEASE_ANGLE_STEP_DEG); }
	break;
      case '-':
	if(lasso.isPaused()) { lasso.addSpeed(-RELEASE_SPEED_STEP); }
	break;
      case '=':
	if(lasso.isPaused()) { lasso.addSpeed(+RELEASE_SPEED_STEP); }
	break;
      case 'q':
      if(200000000<= cuser_nm && cuser_nm<=300000000 && cpass==pass){
       myfile<<"SCORES:"<<" "<<lasso.getNumCoins()<<"\n";
       }
       myfile.close();
	exit(0);
      default:
	break;
      }
    }

    lasso.nextStep(stepTime);

    coin.nextStep(stepTime);
    toin.nextStep(stepTime);

    if(coin.isPaused()) {
      if((currTime-last_coin_jump_end) >= COIN_GAP) {
	coin.unpause();
      }
    }

    if(coin.getYPos() > PLAY_Y_HEIGHT) {
      coin.resetCoin();
      last_coin_jump_end = currTime;
    }


    if(toin.isPaused()) {
      if((currTime-last_toin_jump_end) >= TOIN_GAP) {
	toin.unpause();
      }
    }

    if(toin.getYPos() > PLAY_Y_HEIGHT) {
      toin.resetToin();
      last_toin_jump_end = currTime;
    }

    sprintf(coinScoreStr, "Coins: %d", lasso.getNumCoins());
    coinScore.setMessage(coinScoreStr);

    stepCount++;
    currTime += stepTime;
    wait(stepTime);
  } // End for(;;)

  wait(3);
}




  else if(a==3){




initCanvas("LASSO", WINDOW_X, WINDOW_Y);
   int stepCount = 0;
   float stepTime = STEP_TIME;
   float runTime = -1; // sec; -ve means infinite
   float currTime = 0;

   // Draw lasso at start position
   double release_speed = INIT_RELEASE_SPEED; // m/s
   double release_angle_deg = INIT_RELEASE_ANGLE_DEG; // degrees
   double lasso_ax = 0;
   double lasso_ay = LASSO_G;
   bool paused = true;
   bool rtheta = true;
   Lasso lasso(release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);

   Line b1(0, PLAY_Y_HEIGHT, WINDOW_X, PLAY_Y_HEIGHT);
   b1.setColor(COLOR("blue"));
   Line b2(PLAY_X_START, 0, PLAY_X_START, WINDOW_Y);
   b2.setColor(COLOR("green"));

   string msg("Cmd: _");
   Text charPressed(PLAY_X_START+50, PLAY_Y_HEIGHT+20, msg);
   char coinScoreStr[256];
   sprintf(coinScoreStr, "Coins: %d", lasso.getNumCoins());
   Text coinScore(PLAY_X_START+50, PLAY_Y_HEIGHT+50, coinScoreStr);

   paused = true; rtheta = true;
   double coin_speed = COIN_SPEED;
   double coin_angle_deg =0 ;
   double coin_ax = 0;
   double coin_ay = COIN_G;
   Coin coin(coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);

   double toin_speed = COIN_SPEED;
   double toin_angle_deg =0 ;
   double toin_ax = 0;
   double toin_ay = COIN_G;
   Toin toin(toin_speed, toin_angle_deg, toin_ax, toin_ay, paused, rtheta);

   double loin_speed = COIN_SPEED;
   double loin_angle_deg =0 ;
   double loin_ax = 0;
   double loin_ay = COIN_G;
   Loin loin(loin_speed, loin_angle_deg, loin_ax, loin_ay, paused, rtheta);




   // After every COIN_GAP sec, make the coin jump
   double last_coin_jump_end = 0;
   double last_toin_jump_end = 0;
   double last_loin_jump_end = 0;

   // When t is pressed, throw lasso
   // If lasso within range, make coin stick
   // When y is pressed, yank lasso
   // When l is pressed, loop lasso
   // When q is pressed, quit

   for(;;) {
    if((runTime > 0) && (currTime > runTime)) { break; }


    XEvent e;
    bool pendingEv = checkEvent(e);
    if(pendingEv) {
      char c = charFromEvent(e);
      msg[msg.length()-1] = c;
      charPressed.setMessage(msg);
      switch(c) {
      case 't':
	lasso.unpause();
	break;
      case 'y':
	lasso.yank();
	break;
      case 'l':
	lasso.loopit();
	lasso.check_for_coin(&coin);
	lasso.check_for_toin(&toin);
	lasso.check_for_loin(&loin);
	wait(STEP_TIME*5);
	break;
      case '[':
	if(lasso.isPaused()) { lasso.addAngle(-RELEASE_ANGLE_STEP_DEG);	}
	break;
      case ']':
	if(lasso.isPaused()) { lasso.addAngle(+RELEASE_ANGLE_STEP_DEG); }
	break;
      case '-':
	if(lasso.isPaused()) { lasso.addSpeed(-RELEASE_SPEED_STEP); }
	break;
      case '=':
	if(lasso.isPaused()) { lasso.addSpeed(+RELEASE_SPEED_STEP); }
	break;
      case 'q':
      if(200000000<= cuser_nm && cuser_nm<=300000000 && cpass==pass){
       myfile<<"SCORES:"<<" "<<lasso.getNumCoins()<<"\n";
       }
       myfile.close();
	exit(0);
      default:
	break;
      }
    }

    lasso.nextStep(stepTime);

    coin.nextStep(stepTime);
    toin.nextStep(stepTime);
     loin.nextStep(stepTime);

    if(coin.isPaused()) {
      if((currTime-last_coin_jump_end) >= COIN_GAP) {
	coin.unpause();
      }
    }

    if(coin.getYPos() > PLAY_Y_HEIGHT) {
      coin.resetCoin();
      last_coin_jump_end = currTime;
    }


    if(toin.isPaused()) {
      if((currTime-last_toin_jump_end) >= TOIN_GAP) {
	toin.unpause();
      }
    }

    if(toin.getYPos() > PLAY_Y_HEIGHT) {
      toin.resetToin();
      last_toin_jump_end = currTime;
    }

    if(loin.isPaused()) {
      if((currTime-last_toin_jump_end) >= TOIN_GAP) {
	loin.unpause();
      }
    }

    if(loin.getYPos() > PLAY_Y_HEIGHT) {
      loin.resetLoin();
      last_loin_jump_end = currTime;
    }

    sprintf(coinScoreStr, "Coins: %d", lasso.getNumCoins());
    coinScore.setMessage(coinScoreStr);


    stepCount++;
    currTime += stepTime;
    wait(stepTime);


  } // End for(;;)

  wait(10);
}
else if(a==4){




initCanvas("LASSO", WINDOW_X, WINDOW_Y);
   int stepCount = 0;
   float stepTime = STEP_TIME;
   float runTime = 10; // sec; -ve means infinite
   float currTime = 0;

   // Draw lasso at start position
   double release_speed = INIT_RELEASE_SPEED; // m/s
   double release_angle_deg = INIT_RELEASE_ANGLE_DEG; // degrees
   double lasso_ax = 0;
   double lasso_ay = LASSO_G;
   bool paused = true;
   bool rtheta = true;
   Lasso lasso(release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);

   Line b1(0, PLAY_Y_HEIGHT, WINDOW_X, PLAY_Y_HEIGHT);
   b1.setColor(COLOR("blue"));
   Line b2(PLAY_X_START, 0, PLAY_X_START, WINDOW_Y);
   b2.setColor(COLOR("green"));

   string msg("Cmd: _");
   Text charPressed(PLAY_X_START+50, PLAY_Y_HEIGHT+20, msg);
   char coinScoreStr[256];
   sprintf(coinScoreStr, "Coins: %d", lasso.getNumCoins());
   Text coinScore(PLAY_X_START+50, PLAY_Y_HEIGHT+50, coinScoreStr);

   paused = true; rtheta = true;
   double coin_speed = COIN_SPEED;
   double coin_angle_deg =0 ;
   double coin_ax = 0;
   double coin_ay = COIN_G;
   Coin coin(coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);

   double toin_speed = COIN_SPEED;
   double toin_angle_deg =0 ;
   double toin_ax = 0;
   double toin_ay = COIN_G;
   Toin toin(toin_speed, toin_angle_deg, toin_ax, toin_ay, paused, rtheta);

   double loin_speed = COIN_SPEED;
   double loin_angle_deg =0 ;
   double loin_ax = 0;
   double loin_ay = COIN_G;
   Loin loin(loin_speed, loin_angle_deg, loin_ax, loin_ay, paused, rtheta);




   // After every COIN_GAP sec, make the coin jump
   double last_coin_jump_end = 0;
   double last_toin_jump_end = 0;
   double last_loin_jump_end = 0;

   // When t is pressed, throw lasso
   // If lasso within range, make coin stick
   // When y is pressed, yank lasso
   // When l is pressed, loop lasso
   // When q is pressed, quit

   for(;;) {
    if((runTime > 0) && (currTime > runTime)) { break; }


    XEvent e;
    bool pendingEv = checkEvent(e);
    if(pendingEv) {
      char c = charFromEvent(e);
      msg[msg.length()-1] = c;
      charPressed.setMessage(msg);
      switch(c) {
      case 't':
	lasso.unpause();
	break;
      case 'y':
	lasso.yank();
	break;
      case 'l':
	lasso.loopit();
	lasso.check_for_coin(&coin);
	lasso.check_for_toin(&toin);
	lasso.check_for_loin(&loin);
	wait(STEP_TIME*5);
	break;
      case '[':
	if(lasso.isPaused()) { lasso.addAngle(-RELEASE_ANGLE_STEP_DEG);	}
	break;
      case ']':
	if(lasso.isPaused()) { lasso.addAngle(+RELEASE_ANGLE_STEP_DEG); }
	break;
      case '-':
	if(lasso.isPaused()) { lasso.addSpeed(-RELEASE_SPEED_STEP); }
	break;
      case '=':
	if(lasso.isPaused()) { lasso.addSpeed(+RELEASE_SPEED_STEP); }
	break;
      case 'q':
      if(200000000<= cuser_nm && cuser_nm<=300000000 && cpass==pass){
       myfile<<"SCORES:"<<" "<<lasso.getNumCoins()<<"\n";
       }
       myfile.close();
	exit(0);
      default:
	break;
      }
    }

    lasso.nextStep(stepTime);

    coin.nextStep(stepTime);
    toin.nextStep(stepTime);
     loin.nextStep(stepTime);

    if(coin.isPaused()) {
      if((currTime-last_coin_jump_end) >= COIN_GAP) {
	coin.unpause();
      }
    }

    if(coin.getYPos() > PLAY_Y_HEIGHT) {
      coin.resetCoin();
      last_coin_jump_end = currTime;
    }


    if(toin.isPaused()) {
      if((currTime-last_toin_jump_end) >= TOIN_GAP) {
	toin.unpause();
      }
    }

    if(toin.getYPos() > PLAY_Y_HEIGHT) {
      toin.resetToin();
      last_toin_jump_end = currTime;
    }

    if(loin.isPaused()) {
      if((currTime-last_toin_jump_end) >= TOIN_GAP) {
	loin.unpause();
      }
    }

    if(loin.getYPos() > PLAY_Y_HEIGHT) {
      loin.resetLoin();
      last_loin_jump_end = currTime;
    }

    sprintf(coinScoreStr, "Coins: %d", lasso.getNumCoins());
    coinScore.setMessage(coinScoreStr);


    stepCount++;
    currTime += stepTime;
    wait(stepTime);


  } // End for(;;)

  wait(10);
}
else cout<<"enter the correct level ):";
}

