#pragma once
#include "Malla.h"

class MontanaRusa : public Malla{

private:
	int nP; //nº de lados del poligono que aproxima la circunferencia
	int nQ; //nº de rodajas que forman el tubo
	float radio;
	void construirMontanaRusa();
	PV3D* multiplicarMatrizPorPunto(float m[4][4], float pto[4]);

public:
	MontanaRusa(int nP, int nQ, float radio);

};