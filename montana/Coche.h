#include "Malla.h"

class Coche : public Malla{

private:

	float height;
	float width;
	float length;
	float wheelRadius;
	void construirCoche();
	void construirRueda();
	int distancia = 0;

public:
	Coche();
	Coche(float height, float width, float length, float wheelRadius);
	void dibuja();
	void avanza(int d);
	void retrocede(int d);
	PV3D* getC(double t);
	PV3D* getCPrima(double t);
	PV3D* getCSegunda(double t);
	PV3D* multiplicarMatrizPorPunto(GLfloat m[4][4], GLfloat pto[4]);
};