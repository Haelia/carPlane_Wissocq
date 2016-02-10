#include <math.h>
#include "Car.h"
#include "GLTool.h"
#include "GLRender.h"

using namespace p3d;
using namespace std;


// ************************************************************
Car::~Car() {
}

Car::Car() {
  _orientation.setIdentity();
  _position.set(0,0,0);
  _steering=0;
  _rotateWheel=0;
  _acceleration=0;
  _velocity=0;
}

// ******************************************************************
// méthodes à compléter lors du TP
void Car::drawRim() {

    //premier cylindre horizontal
    modelviewMatrix.push();

    modelviewMatrix.translate(-3,0,0);
    modelviewMatrix.rotate(90,0,1,0);
    modelviewMatrix.scale(0.3,0.3,6);
    drawCylinder();
    modelviewMatrix.pop();

    //deuxieme cylindre vertical
    modelviewMatrix.push();
    modelviewMatrix.rotate(90,1,0,0);
    modelviewMatrix.translate(0,0,-3);
    modelviewMatrix.scale(0.3,0.3,6);
    drawCylinder();
    modelviewMatrix.pop();

    //troisieme cylindre
    modelviewMatrix.push();
    modelviewMatrix.rotate(90,1,1,0);
    modelviewMatrix.translate(0,0,-3);
    modelviewMatrix.scale(0.3,0.3,6);
    drawCylinder();
    modelviewMatrix.pop();

    //quatrieme cylindre
    modelviewMatrix.push();
    modelviewMatrix.rotate(90,1,0,0);
    modelviewMatrix.rotate(-45,0,1,0);
    modelviewMatrix.translate(0,0,-3);
    modelviewMatrix.scale(0.3,0.3,6);
    drawCylinder();
    modelviewMatrix.pop();

}

void Car::drawWheel() {
  modelviewMatrix.push();
  diffuseColor=Vector3(0,0,1);
  modelviewMatrix.scale(3.5,3.5,2);
  drawTorus();
  modelviewMatrix.pop();
  modelviewMatrix.push();
  diffuseColor=Vector3(1,0,0);
  drawRim();
  modelviewMatrix.pop();
}

void Car::drawAxle() {
    modelviewMatrix.push();
    modelviewMatrix.translate(0,0,-10);
     modelviewMatrix.scale(0.5,0.5,10);
     diffuseColor=Vector3(0,1,0);
    drawCylinder();
    modelviewMatrix.pop();
    modelviewMatrix.push();
    drawWheel();
    modelviewMatrix.translate(0,0,-10);
    drawWheel();
    modelviewMatrix.pop();

}

void Car::drawBody() {

    modelviewMatrix.push();
    modelviewMatrix.scale(3,1,1);
    diffuseColor=Vector3(1,0,1);
    drawCube();
    modelviewMatrix.pop();

    modelviewMatrix.push();
    modelviewMatrix.translate(2,2,0);
    drawCube();
    modelviewMatrix.pop();

}

void Car::draw() {
  p3d::modelviewMatrix.push();
modelviewMatrix.translate(0,-1,0);

//Question 2
//drawBody();
//Question 3
//drawRim();
//Question 4
  //drawWheel();
//Question 5
//drawAxle();

   drawBody();
   modelviewMatrix.pop();

   //Axe Arrière
   modelviewMatrix.push();
   modelviewMatrix.translate(2,-2,1.5);
   modelviewMatrix.scale(0.2,0.2,0.3);
   modelviewMatrix.rotate(_rotateWheel,0,0,1);
   drawAxle();
   modelviewMatrix.pop();

   //Axe avant
   modelviewMatrix.push();
   modelviewMatrix.translate(-2,-2,1.5);
   modelviewMatrix.scale(0.2,0.2,0.3);
   modelviewMatrix.rotate(_steering,0,1,0);
   modelviewMatrix.rotate(_rotateWheel,0,0,1);

   drawAxle();
  p3d::modelviewMatrix.pop();
}


void Car::drawWorld() {

  p3d::modelviewMatrix.push();
  modelviewMatrix.translate(_position);
  modelviewMatrix.rotate(_orientation);

  draw(); // tracé de la voiture dans son repère local
  p3d::modelviewMatrix.pop();
}

void Car::move() {
  _acceleration+=-_velocity/50;
  _velocity+=_acceleration;
  _rotateWheel+=_velocity*15;
  _steering-=_steering/10*fabs(_velocity);

  _orientation.rotate(_steering*_velocity/(1.0+fabs(_velocity)),Vector3(0,1,0)); // le /(1.0+fabs(_velocity)) a été déterminé empiriquement
  _position= _position+(_orientation*Vector3(-1,0,0)*_velocity);
}


void Car::accelerate() {
  _acceleration=0.05;

}

void Car::decelerate() {
  _acceleration=0;
}

void Car::brake() {
  _acceleration=-0.02;

}

void Car::turnLeft() {
  _steering+=0.5;
  if (_steering>35) _steering=35;
}

void Car::turnRight() {
  _steering-=0.5;
  if (_steering<-35) _steering=-35;
}





