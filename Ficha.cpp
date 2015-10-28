#pragma once
#include "Ficha.h"
#include <iostream>

Ficha::Ficha(int nQuesitos){

	this->nQuesitos = nQuesitos;

	int nQ = 360/nQuesitos; //numero de caras que forman la revolucion (360/nQuesitos => uno por grado que tenga la revolucion)
	float colores[6][3] = { { 0, 0, 1 },
							{ 0, 1, 0 },
							{ 0, 1, 1 },
							{ 1, 0, 0 },
							{ 1, 0, 1 },
							{ 1, 1, 0 } };

	q = new Quesito*[nQuesitos];

	for (int i = 0; i < nQuesitos; i++){
		std::cout << i%nQuesitos << std::endl;
		q[i] = new Quesito(nQ, 5, 2.5, i, nQuesitos, colores[i%6]);
	}
}

void Ficha::dibuja(){

	if (this->rotateAngleX != 0 || this->rotateAngleY != 0 || this->rotateAngleZ != 0){
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glRotatef(this->rotateAngleX, 1, 0, 0);
		glRotatef(this->rotateAngleY, 0, 1, 0);
		glRotatef(this->rotateAngleZ, 0, 0, 1);
	}

	for (int i = 0; i < this->nQuesitos; i++){
		q[i]->dibuja();
	}

	if (this->rotateAngleX != 0 || this->rotateAngleY != 0 || this->rotateAngleZ != 0){
		glPopMatrix();
	}
}

void Ficha::setDisplayModel(int mode){
	for (int i = 0; i < this->nQuesitos; i++){
		q[i]->setDisplayModel(mode);
	}
}