#pragma once
#include "Malla.h"
#include "Quesito.h"

class Ficha : public Malla{
private:

	Quesito** q;
	int nQuesitos;
	int n; //numero de caras que forman la revolucion
	float z;
	float x;
	void verticesRevolucion(int m, int i);
	void carasQuesitos(int i, int m, float color[3]);

public:
	Ficha(int nQuesitos, float z, float x);
};