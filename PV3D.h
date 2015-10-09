#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

class PV3D {

private:
	GLfloat x, y, z;
	int pv;

public:
	void normaliza();
	PV3D* clona();
	GLfloat productoEscalar(PV3D* v);
	PV3D* productoVectorial(PV3D* v);
	GLfloat getX();
	GLfloat getY();
	GLfloat getZ();
};