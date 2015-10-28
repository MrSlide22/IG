#pragma once
#include "Malla.h"
#include "Quesito.h"

class Ficha : public Malla{
private:

	Quesito** q;
	int nQuesitos;

public:
	Ficha(int nQuesitos);
	void dibuja();
	void setDisplayModel(int model);
};