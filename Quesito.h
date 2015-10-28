#pragma once
#include "Malla.h"

class Quesito : public Malla{

private:
	int nQ;
	float z;
	float x;
	int indiceQuesito;
	float* color;
	void construiRevolucion(int m, int nQuesitos);

public:
	/*
	int nQ: numero de caras de la parte curva del quesito
	float z: radio del quesito
	float x: altura del quesito
	int indiceQuesito: posicion que ocupa el quesito dentro del circulo de quesitos (para
	    pintar varios quesitos uno detras de otro. El primer quesito del circulo tendra indice
		0, el segundo 1... y el constructor se encarga de rotarlo en funcion del indice
	float red: componente roja del color del quesito
	float green: componente verde del color del quesito
	float: blue: componente azul del color del quesito
	*/
	Quesito(int nQ, float z, float x, int indiceQuesito, int nQuesitos, float color[]);
};