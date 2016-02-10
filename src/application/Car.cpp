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

}

void Car::drawBody() {

    modelviewMatrix.push();
    modelviewMatrix.scale(3,1,1);
    diffuseColor=Vector3(0,0,1);
    drawCube();
    modelviewMatrix.pop();

    modelviewMatrix.push();
    modelviewMatrix.translate(2,2,0);
    drawCube();
    modelviewMatrix.pop();

}

void Car::draw() {
  p3d::modelviewMatrix.push();
modelviewMatrix.translate(0,1,0);
//Question 2
//drawBody();
//Question 3
//drawRim();
//Question 4
  drawWheel();


  p3d::modelviewMatrix.pop();
}


void Car::drawWorld() {

  p3d::modelviewMatrix.push();

  draw(); // tracé de la voiture dans son repère local
  p3d::modelviewMatrix.pop();
}

void Car::move() {
  _acceleration+=-_velocity/50;
  _velocity+=_acceleration;
  _rotateWheel+=_velocity*20;
  _steering-=_steering/10*fabs(_velocity);

  _orientation.rotate(_steering*_velocity/(1.0+fabs(_velocity)),Vector3(0,1,0)); // le /(1.0+fabs(_velocity)) a été déterminé empiriquement

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





