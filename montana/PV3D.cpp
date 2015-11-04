#include "PV3D.h"
#include <gl/GL.h>
#include <cmath>

PV3D::PV3D(int pva) {
	pv = pva;
}

PV3D::PV3D(GLfloat xa, GLfloat ya, GLfloat za, int pva) {
	x = xa;
	y = ya;
	z = za;
	pv = pva; //0 = vector, 1 = punto
}

GLfloat PV3D::productoEscalar(PV3D* v) {
	return NULL;
}
PV3D* PV3D::productoVectorial(PV3D* v) {

	GLfloat x = this->getY()*v->getZ() - this->getZ()*v->getY();
	GLfloat y = this->getX()*v->getZ() - this->getZ()*v->getX();
	GLfloat z = this->getX()*v->getY() - this->getY()*v->getX();

	return new PV3D(x, -y, z, 0);
}
GLfloat PV3D::getX() {
	return x;
}
GLfloat PV3D::getY() {
	return y;
}
GLfloat PV3D::getZ() {
	return z;
}

void PV3D::setX(GLfloat xa){
	x = xa;
}

void PV3D::setY(GLfloat ya){
	y = ya;
}

void PV3D::setZ(GLfloat za){
	z = za;
}

PV3D* PV3D::normaliza() {
	GLfloat modulo = sqrt(x*x + y*y + z*z);
	return new PV3D(x/modulo, y/modulo, z/modulo, 0);
}

PV3D* PV3D::clona(){
	return new PV3D(this->getX(), this->getY(), this->getZ(), this->pv);
}