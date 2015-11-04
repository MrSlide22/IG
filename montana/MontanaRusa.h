#pragma once
#include "Malla.h"

class MontanaRusa : public Malla{

private:
	int nP; //nº de lados del poligono que aproxima la circunferencia
	int nQ; //nº de rodajas que forman el tubo
	float radio;
	void construirMontanaRusa();
	PV3D* multiplicarMatrizPorPunto(GLfloat m[4][4], GLfloat pto[4]);
	PV3D* getC(double t);
	PV3D* getCPrima(double t);
	PV3D* getCSegunda(double t);

public:
	MontanaRusa(int nP, int nQ, float radio);
};