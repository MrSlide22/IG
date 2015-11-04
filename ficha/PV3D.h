#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

class PV3D {

private:
	GLfloat x, y, z;
	int pv;

public:
	PV3D(int pva);
	PV3D(GLfloat xa, GLfloat ya, GLfloat za, int pva);
	PV3D* normaliza();
	PV3D* clona();
	GLfloat productoEscalar(PV3D* v);
	PV3D* productoVectorial(PV3D* v);
	GLfloat getX();
	GLfloat getY();
	GLfloat getZ();
	void setX(GLfloat xa);
	void setY(GLfloat ya);
	void setZ(GLfloat za);
};