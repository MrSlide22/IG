#pragma once
#include <cmath>
#include <iostream>
#include "MontanaRusa.h"

MontanaRusa::MontanaRusa(int nP, int nQ, float radio){
	this->nP = nP;
	this->nQ = nQ;
	this->radio = radio;

	this->numCaras = nP*nQ;
	this->numVertices = nP*nQ;
	this->numeroNormales = numCaras;

	this->cara = new Cara*[this->numCaras];
	this->vertice = new PV3D*[this->numVertices];
	this->normal = new PV3D*[this->numeroNormales];

	this->construirMontanaRusa();
}

void MontanaRusa::construirMontanaRusa(){


	PV3D** perfil = new PV3D*[this->nP];
	double inc = 2 * atan(1) * 4/ this->nP;
	double theta = 0;

	PV3D* c = this->getC(theta);
	PV3D* cprima = this->getCPrima(theta);
	PV3D* csegunda = this->getCSegunda(theta);

	PV3D* t = cprima->normaliza();
	PV3D* b = (cprima->productoVectorial(csegunda))->normaliza();
	PV3D* n = b->productoVectorial(t);

	GLfloat m[4][4] = { { n->getX(), n->getY(), n->getZ(), 0 },
						{ b->getX(), b->getY(), b->getZ(), 0 },
						{ t->getX(), t->getY(), t->getZ(), 0 },
						{ c->getX(), c->getY(), c->getZ(), 1 } };

	for (int i = 0; i < nP; i++){
		GLfloat pto[] = { this->radio*cos(2 * atan(1) * 4 - i*inc), this->radio*sin(2 * atan(1) * 4 - i*inc), 0, 1 };
		perfil[i] = multiplicarMatrizPorPunto(m, pto);
	}

	for (int j = 0; j < nP; j++){
		this->vertice[j] = perfil[j]->clona();
	}

	//Generamos los vertices (sin el perfil)
	int alpha = 1;
	for (int i = 1; i < nQ +1; i++){

		alpha = (360 / nQ) * i;
		double theta = alpha*atan(1) * 4 / 180;

		PV3D* c = this->getC(theta);
		PV3D* cprima = this->getCPrima(theta);
		PV3D* csegunda = this->getCSegunda(theta);

		PV3D* t = cprima->normaliza();
		PV3D* b = (cprima->productoVectorial(csegunda))->normaliza();
		PV3D* n = b->productoVectorial(t);

		GLfloat m[4][4] = { { n->getX(), n->getY(), n->getZ(), 0 },
							{ b->getX(), b->getY(), b->getZ(), 0 },
							{ t->getX(), t->getY(), t->getZ(), 0 },
							{ c->getX(), c->getY(), c->getZ(), 1 } };

		for (int j = 0; j < nP; j++){
			int indice = (i*nP) + j;

			GLfloat pto[] = { this->radio*cos(2 * atan(1) * 4 - j*inc), this->radio*sin(2 * atan(1) * 4 - j*inc), 0, 1 };
			this->vertice[indice] = multiplicarMatrizPorPunto(m, pto);
		}
	}
	
	//Construcción de las caras
	int indiceCara = 0;
	for (int i = 0; i < nQ; i++){
		for (int j = 0; j < nP; j++) { //esquina inferior-izquierda de una cara
			//indiceCara = i*(nP-1) + j;
			int indice = i*nP + j;
			VerticeNormal** vn = new VerticeNormal*[4];
			vn[0] = new VerticeNormal(indice, indiceCara);
			vn[1] = new VerticeNormal((indice + nP) % this->numVertices, indiceCara);
			vn[2] = new VerticeNormal((indice + 1 + nP) % this->numVertices, indiceCara);
			vn[3] = new VerticeNormal(indice + 1, indiceCara);
			cara[indiceCara] = new Cara(vn, 4);

			PV3D* v = calculoVectorNormalPorNewell(*cara[indiceCara]); //Newell
			normal[indiceCara] = v;
			indiceCara++;
		} //for
	} //for
}

PV3D* MontanaRusa::getC(double t){
	return new PV3D(3 * cos(t), 3 * sin(2 * t), 3 * sin(t), 1);
}

PV3D* MontanaRusa::getCPrima(double t){
	return new PV3D(-3 * sin(t), 6 * cos(2 * t), 3 * cos(t), 0);
}

PV3D* MontanaRusa::getCSegunda(double t){
	return new PV3D(-3 * cos(t), -12 * sin(2 * t), -3 * sin(t), 0);
}

PV3D* MontanaRusa::multiplicarMatrizPorPunto(GLfloat m[4][4], GLfloat pto[4]){

	GLfloat ret[4] = {};
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			ret[i] += m[j][i] * pto[j];
		}
	}

	return new PV3D(ret[0], ret[1], ret[2], ret[3]);
}